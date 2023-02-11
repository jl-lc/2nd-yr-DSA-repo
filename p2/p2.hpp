#include <iostream>
#include <vector>

class Process {
    public:
        Process(unsigned int pid, unsigned int address);
        ~Process();

        unsigned int getpid();
        unsigned int getaddress();
    
    private:
        unsigned int pid;
        unsigned int address;
};

class Hashtable {
    public:
        Hashtable(unsigned int size, unsigned int pagesize, bool open);
        ~Hashtable();

        int hashprimary(unsigned int pid);
        int hashsecondary(unsigned int pid);
        int search(unsigned int pid, bool helper, bool insert);
        void insert(unsigned int pid);
        void write(unsigned int pid, int addr, signed int x);
        void read(unsigned int pid, int addr);
        void del(unsigned int pid);
        void print(int m);

        bool notfull();

    private:
        std::vector<std::vector<Process>> table;
        std::vector<int> orderedmem;
        int *mem;
        int size;
        int occupied;
        int pagesize;
        bool open;
};