#include <iostream>
#include <vector>

using namespace std;

const int ALPHABET = 26;

class TrieNode {
    public:
        TrieNode(TrieNode *trienode);
        ~TrieNode();

        bool getend();
        void setend(bool end);
        TrieNode *getparent();
        void setparent(TrieNode *parent);

        TrieNode *children[ALPHABET];

    private:
        bool end;
        TrieNode *parent;
};

class Trie {
    public:
        Trie();
        ~Trie();

        TrieNode *getroot();
        void setroot(TrieNode* root);
        unsigned int getwords();
        void setwords(unsigned int words);
        
        bool insert(string string);
        TrieNode *search(string string, bool helper);
        unsigned int prefix(TrieNode* trienode);
        void clear(TrieNode*& trienode);
        void erase(TrieNode* trienode);
        void print(TrieNode* trienode, vector<string>& allwords, string string);
        void spellcheck(string word);

    private:
        TrieNode *root;
        unsigned int words;
};

class IllegalException {
    public:
        IllegalException();
        ~IllegalException();

        string what();

    private:
        string msg;
};