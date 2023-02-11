#include <iostream>
#include "jlc2lam_p1.hpp"

//Node defs
Node::Node(double val, std::string name):p_next{nullptr}, value(val), nodename{name} {}
Node::~Node() {}
Node *Node::getnext() {
    return p_next;
}
void Node::setnext(Node *p_new_next) {
    p_next = p_new_next;
}
std::string Node::getnodename() {
    return nodename;
}
double Node::getvalue() {
    return value;
}
void Node::setvalue(double val) {
    value = val;
}

//List defs
List::List(unsigned int N):head{nullptr}, maxNode{N}, curNode{0} {}
List::~List() {
    Node *p_temp{head};
    Node *p_temp_next{};
    while (p_temp != nullptr) {
        p_temp_next = p_temp->getnext();
        delete p_temp;
        p_temp = p_temp_next;
    }
    delete p_temp_next;
    delete p_temp;
}
Node *List::gethead() {
    return head;
}
void List::sethead(Node *newhead) {
    head = newhead;
}
void List::insert(Node *p_new_node) {
    if (head == nullptr) {
        head = p_new_node;
        curNode++;
    } else if (curNode < maxNode) {
        Node *p_temp{head};
        while ((p_temp->getnext()) != nullptr) {
            p_temp = p_temp->getnext();
        }
        p_temp->setnext(p_new_node);
        p_temp = nullptr;
        curNode++;
    } else {
        delete p_new_node;
        p_new_node = nullptr;
    }
}
bool List::atcapacity() {
    if (curNode == maxNode) {
        return true;
    }
    return false;
}
bool List::existname(std::string name) {
    if (head == nullptr) {
        return false;
    }
    Node *p_temp{head};
    if (p_temp->getnodename() == name) {
        return true;
    }
    while ((p_temp->getnext()) != nullptr) {
        p_temp = p_temp->getnext();
        if (p_temp->getnodename() == name) {
            return true;
        }
    }
    return false;
}
Node *List::getnode(std::string name) {
    Node *p_temp{head};
    if (p_temp->getnodename() == name) {
        return nullptr;
    }
    while ((p_temp->getnext()) != nullptr) {
        if (p_temp->getnext()->getnodename() == name) {
            return p_temp;
        }
        p_temp = p_temp->getnext();
    }
    return nullptr;
}
void List::removenode(std::string x) {
    Node *p_temp{nullptr};
    if (getnode(x) == nullptr) {
        p_temp = head;
        sethead(p_temp->getnext());
        delete p_temp;
        p_temp = nullptr;
        curNode--;
    } else {
        p_temp = getnode(x)->getnext();
        getnode(x)->setnext(p_temp->getnext());
        delete p_temp;
        p_temp = nullptr;
        curNode--;
    }
}