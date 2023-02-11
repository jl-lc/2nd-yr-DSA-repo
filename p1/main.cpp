#include <iostream>
#include "jlc2lam_p1.hpp"

//helper functions
void success() {
    std::cout << "success" << std::endl;
    return;
}
void failure() {
    std::cout << "failure" << std::endl;
    return;
}

int main() {
    std::string cmd{};
    List list(0);
    unsigned int N{};
    while (std::cin >> cmd) {
        if (cmd == "CRT") {
            std::cin >> N;

            List list_temp(N);
            list = list_temp;
            success();

        } else if (cmd == "DEF") {
            std::string name{};
            double val{};
            std::cin >> name;
            std::cin >> val;

            if (list.gethead() == nullptr) {
                Node *p_node{new Node {val, name}};
                list.insert(p_node);
                success();
            } else if (list.atcapacity() || list.existname(name)) {
                failure();
            } else {
                Node *p_node{new Node {val, name}};
                list.insert(p_node);
                success();
            }

        } else if (cmd == "ADD") {
            std::string x{};
            std::string y{};
            std::string z{};
            std::cin >> x;
            std::cin >> y;
            std::cin >> z;

            double x_value{};
            double y_value{};
            
            if (list.existname(x) && list.existname(y) && list.existname(z)) {
                if (list.getnode(x) == nullptr) {
                    x_value = list.gethead()->getvalue();
                } else {
                    x_value = list.getnode(x)->getnext()->getvalue();
                }

                if (list.getnode(y) == nullptr) {
                    y_value = list.gethead()->getvalue();
                } else {
                    y_value = list.getnode(y)->getnext()->getvalue();
                }

                if (list.getnode(z) == nullptr) {
                    list.gethead()->setvalue(x_value + y_value);
                    success();
                } else {
                    list.getnode(z)->getnext()->setvalue(x_value + y_value);
                    success();
                }

            } else {
                failure();
            }

        } else if (cmd == "SUB") {
            std::string x{};
            std::string y{};
            std::string z{};
            std::cin >> x;
            std::cin >> y;
            std::cin >> z;

            double x_value{};
            double y_value{};

            if (list.existname(x) && list.existname(y) && list.existname(z)) {
                if (list.getnode(x) == nullptr) {
                    x_value = list.gethead()->getvalue();
                } else {
                    x_value = list.getnode(x)->getnext()->getvalue();
                }

                if (list.getnode(y) == nullptr) {
                    y_value = list.gethead()->getvalue();
                } else {
                    y_value = list.getnode(y)->getnext()->getvalue();
                }

                if (list.getnode(z) == nullptr) {
                    list.gethead()->setvalue(x_value - y_value);
                    success();
                } else {
                    list.getnode(z)->getnext()->setvalue(x_value - y_value);
                    success();
                }

            } else {
                failure();
            }

        } else if (cmd == "REM") {
            std::string x{};
            std::cin >> x;

            if (list.existname(x)) {
                list.removenode(x);
                success();
            } else {
                failure();
            }

        } else if (cmd == "PRT") {
            std::string x{};
            std::cin >> x;

            if (list.existname(x)) {
                if (list.getnode(x) == nullptr) {
                    std::cout << list.gethead()->getvalue() << std::endl;
                } else {
                    std::cout << list.getnode(x)->getnext()->getvalue() << std::endl;
                }
            } else {
                std::cout << "variable " << x << " not found" << std::endl;
            }

        } else if (cmd == "END") {
            break;
        }
    }
    return 0;
}