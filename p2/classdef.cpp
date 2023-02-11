#include <iostream>
#include <vector>
#include "p2.hpp"

void success() {
    std::cout << "success" << std::endl;
}
void failure() {
    std::cout << "failure" << std::endl;
}

Process::Process(unsigned int pid, unsigned int address) {
    this->pid = pid;
    this->address = address;
}
Process::~Process() {}

unsigned int Process::getpid() {
    return pid;
}
unsigned int Process::getaddress() {
    return address;
}


Hashtable::Hashtable(unsigned int size, unsigned int pagesize, bool open):table(size), orderedmem(size), occupied{} {
    this->size = size;
    this->pagesize = pagesize;
    this->open = open;
    this->mem = new int[size * pagesize];
    for (int i{}; i < size; i++) {
        this->orderedmem[i] = i * pagesize;
    }
}
Hashtable::~Hashtable() {
    delete[] mem;
}

int Hashtable::hashprimary(unsigned int pid) {
    return pid % size;
}
int Hashtable::hashsecondary(unsigned int pid) {
    int temp{(pid / size) % size};
    return temp % 2 == 1 ? temp : ++temp;
}

int Hashtable::search(unsigned int pid, bool helper, bool insert) {
    int index{hashprimary(pid)};
    if (open) {
        //double hashing search
        for (int i{0}; i < size; ++i) {
            index = (hashprimary(pid) + i * hashsecondary(pid)) % size;
            if (!table[index].empty()) {
                if (pid == table[index][0].getpid()) {
                    return index;
                }
            //helper function for insert
            } else if (insert) {
                return index;
            }
        }
        //not found
        return -1;
    } else {
        if (table[index].empty()) {
            if (insert) {
                return index;
            }
            return -1;
        }
        //traverse through vector of table[index]
        for (int k{}; k < table[index].size(); k++) {
            //found matching pid
            if (pid == table[index][k].getpid()) {
                //helper function for other functions
                if (helper) {
                    return k;
                }
                return index;
            }
        }
        //helper function for insert
        if (insert) {
            return index;
        }
        //not found
        return -1;
    }
}
void Hashtable::insert(unsigned int pid) {
    int temp{search(pid, false, false)};
    if (temp == -1 && notfull()) {
        int index{search(pid, false, true)};
        // if PID not found and hashtable not full
        int address{orderedmem[orderedmem.size() - 1]};
        orderedmem.pop_back();
        
        table[index].push_back(Process(pid, address));
        ++occupied;
        success();
        return;
    } else {
        failure();
        return;
    }
}
void Hashtable::write(unsigned int pid, int addr, signed int x) {
    //if PID is found and inside virtual address space
    int k{search(pid, true, false)};
    if (k != -1 && addr < pagesize) {
        int index{};
        if (open) {
            mem[table[k][0].getaddress() + addr] = x;
            success();
            return;
        } else {
            index = hashprimary(pid);
            mem[table[index][k].getaddress() + addr] = x;
            success();
            return;
        }
    } else {
        failure();
        return;
    }
}
void Hashtable::read(unsigned int pid, int addr) {
    //if PID is found and inside virtual address space
    int k{search(pid, true, false)};
    if (k != -1 && addr < pagesize) {
        int index{hashprimary(pid)};
        if (open) {     
            std::cout << std::to_string(addr) + " " + std::to_string(mem[table[k][0].getaddress() + addr]) << std::endl;
            return;
        } else {
            std::cout << std::to_string(addr) + " " + std::to_string(mem[table[index][k].getaddress() + addr]) << std::endl;
            return;
        }
    } else {
        failure();
        return;
    }
}
void Hashtable::del(unsigned int pid) {
    int k{search(pid, true, false)};
    if (k != -1) {
        if (open) {
            orderedmem.push_back(table[k][0].getaddress());
            table[k].erase(table[k].begin());
            --occupied;
            success();
            return;
        } else {
            int index = hashprimary(pid);
            orderedmem.push_back(table[index][k].getaddress());
            table[index].erase(table[index].begin() + k);
            --occupied;
            success();
            return;
        }

    } else {
        //pid not found
        failure();
        return;
    }
}
void Hashtable::print(int m) {
    if (table[m].size() == 0) {
        std::cout << "chain is empty" << std::endl;
        return;
    } 
    //sort descending and place in temparray
    int temparray[table[m].size()]{};
    for (int k{}; k < table[m].size(); k++) {
        for (int i{}; i <= k; i++) {
            if (table[m][k].getpid() >= temparray[i]) {
                for (int j{k}; j > i; j--) {
                    temparray[j] = temparray[j-1];
                }
                temparray[i] = table[m][k].getpid();
                break;
            }
        }
    }
    //print temparray;
    for (int k{}; k < table[m].size()-1; k++) {
        std::cout << std::to_string(temparray[k]) + " ";
    }
    std::cout << std::to_string(temparray[table[m].size()-1]) << std::endl;
    return;
}

bool Hashtable::notfull() {
    return size > occupied ? true : false;
}