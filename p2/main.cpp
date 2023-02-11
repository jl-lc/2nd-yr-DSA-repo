#include <iostream>
#include <vector>
#include "p2.hpp"

int main() {
    std::string cmd{};
    std::string hashcollision{};
    std::cin >> hashcollision;
    bool open = hashcollision == "OPEN" ? true : false;

    unsigned int N{};
    unsigned int P{};
    unsigned int PID{};
    unsigned int ADDR{};
    signed int x{};
    int m{};

    while (cmd != "M") {
        std::cin >> cmd;
    }
    std::cin >> N;
    std::cin >> P;
    Hashtable hashtable(N/P, P, open);
    std::cout << "success" << std::endl;

    while (std::cin >> cmd) {
        if (cmd == "INSERT") {
            std::cin >> PID;
            hashtable.insert(PID);

        } else if (cmd == "SEARCH") {
            std::cin >> PID;

            int temp{hashtable.search(PID, false, false)};
            std::string out = temp == -1 ? 
            "not found" : "found " + std::to_string(PID) + " in " + std::to_string(temp);
            std::cout << out << std::endl;

        } else if (cmd == "WRITE") {
            std::cin >> PID;
            std::cin >> ADDR;
            std::cin >> x;
            hashtable.write(PID, ADDR, x);

        } else if (cmd == "READ") {
            std::cin >> PID;
            std::cin >> ADDR;
            hashtable.read(PID, ADDR);

        } else if (cmd == "DELETE") {
            std::cin >> PID;
            hashtable.del(PID);

        } else if (cmd == "PRINT") {
            std::cin >> m;
            hashtable.print(m);

        } else if (cmd == "END") {
            break;

        }
    }
    return 0;
}