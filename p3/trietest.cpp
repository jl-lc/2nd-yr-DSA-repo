#include <iostream>
#include <fstream>
#include "trie.hpp"

void success() {
    cout << "success" << endl;
}
void failure() {
    cout << "failure" << endl;
}

int main() {
    Trie trie;
    string cmd, word;

    while (std::cin >> cmd) {
        if (cmd == "load") {
            ifstream fin("corpus.txt");
            while (fin >> word) {
                trie.insert(word);
            }
            success();

        } else if (cmd == "i") {
            cin >> word;
            try {
                for (char c : word) {
                    if (c < 'A' || c > 'Z') {
                        throw IllegalException();
                    }
                }

                trie.insert(word) ? success() : failure();

            } catch (IllegalException ex) {
                cout << ex.what() << endl;
            }

        } else if (cmd == "c") {
            cin >> word;
            try {
                for (char c : word) {
                    if (c < 'A' || c > 'Z') {
                        throw IllegalException();
                    }
                }

                TrieNode *prefix = trie.search(word, true);
                if (prefix == nullptr) {
                    cout << "not found" << endl;
                } else {
                    cout << "count is " << to_string(trie.prefix(prefix)) << endl;
                }

            } catch (IllegalException ex) {
                cout << ex.what() << endl;
            }

        } else if (cmd == "e") {
            cin >> word;
            try {
                for (char c : word) {
                    if (c < 'A' || c > 'Z') {
                        throw IllegalException();
                    }
                }

                TrieNode *erase = trie.search(word, false);
                if (erase == nullptr) {
                    failure();
                } else {
                    trie.erase(erase);
                    success();
                }

            } catch (IllegalException ex) {
                cout << ex.what() << endl;
            }

        } else if (cmd == "p") {
            vector<string> str;
            trie.print(trie.getroot(), str, "");
            for (int i{}; i < str.size(); ++i) {
                cout << str[i] << " ";
                if (i == str.size() - 1) {
                    cout << endl;
                }
            }

        } else if (cmd == "spellcheck") {
            cin >> word;
            trie.spellcheck(word);
            
        } else if (cmd == "empty") {
            string empty = trie.getwords() == 0 ? "empty 1" : "empty 0";
            cout << empty << endl;

        } else if (cmd == "clear") {
            trie.setwords(0);
            TrieNode* root = trie.getroot();
            trie.clear(root);
            trie.setroot(new TrieNode(nullptr));
            success();

        } else if (cmd == "size") {
            cout << "number of words is " << to_string(trie.getwords()) << endl;

        } else if (cmd == "exit") {
            break;
        }
    }
    return 0;
}