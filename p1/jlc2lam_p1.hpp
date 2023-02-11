#include <iostream>

class Node {
	public:
		Node(double val, std::string name);
		~Node();

		Node *getnext();
		void setnext(Node *p_new_next);
		std::string getnodename();
		double getvalue();
		void setvalue(double val);

	private:
		Node *p_next;
		std::string nodename{};
		double value{};
};

class List {
	public:
		List(unsigned int N);
		~List();

		Node *gethead();
		void sethead(Node *newhead);
		void insert(Node *p_new_node);
		bool atcapacity();
		bool existname(std::string name);
		Node *getnode(std::string name);
        void removenode(std::string x);

	private:
		Node *head;
        unsigned int curNode;
		unsigned int maxNode;
};

