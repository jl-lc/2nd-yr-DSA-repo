# ECE 250 C++ Algo Projects Repo
Repository containing completed C++ projects of interest in ECE 250 course

---
## P1 - Linked List Calculator
This calculator takes in user commands and adds and stubtracts variables stored in the linked list using a linked list class. Utilized OOP.

_see jlc2lam_design_p1.pdf in p1 folder for in-depth description of the functions, design choices, and time complexity analysis._

---
## P2 - Hashing and Virtual Memory
A virtual memory emulator with hash table data structure. The hash table resolves collisions using an option between open addressing with double hashing and separate chaining. Memory will be represented by an array of integers of size N. Pages are contiguous blocks of memory within this array of size P. The size of the hash table then is 𝑚 = 𝑁/𝑃. For this project, N and P are chosen in such a way that m is an integer power of 2 and N is an integer multiple of P. You may assume that virtual pointers for all processes begin at virtual address 0 and end at P-1. When all 𝑚 blocks are allocated, the hash table is said to be “full”.
### Primary hash function
ℎ1(𝑘) = 𝑘 𝑚𝑜𝑑 𝑚, where k is the key and m is the size of the hash table.
### Secondary hash function
The secondary hash function is ℎ2(𝑘) = ⌊𝑘/𝑚⌋ 𝑚𝑜𝑑 𝑚. Since ℎ2(𝑘) must be an odd number, add 1 to the resulting value if this value is even. Therefore, the hash values will be given by ℎ(𝑘, 𝑖) = (ℎ1(𝑘) + 𝑖 ∗ ℎ2(𝑘)) 𝑚𝑜𝑑 𝑚, where 𝑖 is an index variable from 0 to m-1.

_see jlc2lam_design_p2.pdf in p2 folder for in-depth description of the functions, design choices, and time complexity analysis._

---
## P3 - Trie ADT Spellcheck
A trie data structure spellchecker implementation vaild only with the 26 uppercase English letters. Functions include inserting words, erasing words, printing words etc. into the trie, as well as spellcheck.

_see jlc2lam_design_p3.pdf in p3 folder for in-depth description of the functions, design choices, and time complexity analysis._
