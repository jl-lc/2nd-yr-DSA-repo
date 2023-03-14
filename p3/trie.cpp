#include <iostream>
#include "trie.hpp"

TrieNode::TrieNode(TrieNode *trienode): end{false}, parent{trienode} {
    for (int i{}; i < ALPHABET; ++i) {
        children[i] = nullptr;
    }
}
TrieNode::~TrieNode() {}

bool TrieNode::getend() {
    return end;
}
void TrieNode::setend(bool end) {
    this->end = end;
}
TrieNode *TrieNode::getparent() {
    return parent;
}
void TrieNode::setparent(TrieNode *parent) {
    this->parent = parent;
}



Trie::Trie(): words{} {
    root = new TrieNode(nullptr);
}
Trie::~Trie() {
    words = 0;
    clear(root);
}

TrieNode *Trie::getroot() {
    return root;
}
void Trie::setroot(TrieNode* root) {
    this->root = root;
}
unsigned int Trie::getwords() {
    return words;
}
void Trie::setwords(unsigned int words) {
    this->words = words;
}
bool Trie::insert(string string) {
    bool exist{true};
    TrieNode* current = root;
    for (char c : string) {
        unsigned int index = c - 'A';
        if (current->children[index] == nullptr) {
            current->children[index] = new TrieNode(current);
            exist = false;
        }
        current = current->children[index];
    }
    if (exist && current->getend()) {
        return false;
    } else {    
        current->setend(true);
        words++;
        return true;
    }
}

TrieNode *Trie::search(string string, bool helper) {
    TrieNode* current = root;
    for (char c : string) {
        unsigned int index = c - 'A';
        if (current->children[index] == nullptr) {
            return nullptr;
        }
        current = current->children[index];
    }
    if (helper) {
        return current;
    } else {
        if (current->getend()) {
            return current;
        } else {
            return nullptr;
        }
    }
}

unsigned int Trie::prefix(TrieNode* trienode) {
    unsigned int N{};
    for (unsigned int i{}; i < ALPHABET; i++) {
        if (trienode->children[i] != nullptr) {
            N += prefix(trienode->children[i]);
        }
    }
    if (trienode->getend()) {
        ++N;
    }
    return N;
}

void Trie::clear(TrieNode*& trienode) {
    for (unsigned int i{}; i < ALPHABET; i++) {
        if (trienode->children[i] != nullptr) {
            clear(trienode->children[i]);
        }
    }
    delete trienode;
    trienode = nullptr;
    return;
}

void Trie::erase(TrieNode* trienode) {
    for (unsigned int i{}; i < ALPHABET; i++) {
        if (trienode->children[i] != nullptr) {
            trienode->setend(false);
            --words;
            return;
        }
    }
    TrieNode* parent = trienode->getparent();
    TrieNode* current = trienode;
    while (parent != nullptr && !parent->getend()) {
        for (unsigned int i{}; i < ALPHABET; i++) {
            if (parent->children[i] != nullptr && parent->children[i] != current) {
                for (int i{}; i < ALPHABET; i++) {
                    if (parent->children[i] == current) {
                        parent->children[i] = nullptr;
                    }
                }
                clear(current);
                --words;
                return;
            }
        }
        current = parent;
        parent = parent->getparent();
    }
    if (parent == nullptr) {
        clear(root);
        setroot(new TrieNode(nullptr));
        words = 0;
        return;
    } else {
        for (int i{}; i < ALPHABET; i++) {
            if (parent->children[i] == current) {
                parent->children[i] = nullptr;
            }
        }
        clear(current);
        --words;
        return;
    }
}

void Trie::print(TrieNode* trienode, vector<string>& allwords, string string) {
    TrieNode* current = trienode;
    if (current->getend()) {
        allwords.push_back(string);
    }
    for (unsigned int i{}; i < ALPHABET; i++) {
        if (current->children[i] != nullptr) {
            print(trienode->children[i], allwords, string + char(i + 'A'));
        }
    }
}

void Trie::spellcheck(string word) {
    TrieNode* input = search(word, false);
    if (input != nullptr) {
        cout << "correct" << endl;
    } else {
        input = search(word, true);
        while (input == nullptr) {
            word.pop_back();
            input = search(word, true);
        }
        if (word != "") {
            vector<string> str;
            print(input, str, "");
            for (int i{}; i < str.size(); ++i) {
                cout << word + str[i] << " ";
            }
        }
        cout << endl;
    }
}



IllegalException::IllegalException(): msg{"illegal argument"} {}
IllegalException::~IllegalException() {}

string IllegalException::what() {
    return msg;
}