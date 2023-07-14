#pragma once
#include <string>
#include <vector>

using namespace std;

class Node {
public:
    int id;
    int height;
    string name;
    Node* left;
    Node* right;
    Node() : id(0), height(0) , name(""), left(nullptr), right(nullptr) {}
    Node(string name, int id);
};

class AVL {
private:
    Node* insertHelper(Node* node, string name, int id);
    void removeHelper(Node* root, int id);
    void searchHelper(Node* root, int id);
    void searchHelper(Node* root, string name, vector<int>* ids);
    void printInorderHelper(Node* root, vector<string>* names);
    void printPreorderHelper(Node* root, vector<string>* names);
    void printPostorderHelper(Node* root, vector<string>* names);
    void printLevelCountHelper(Node* root);
    void removeInorderHelper(Node* root, int n);
    void destructHelper(Node* root);
public:
    Node* root;
    void insert(string name, int id) {this->root = insertHelper(this->root, name, id);}
    AVL() : root() {}
    void remove(int id) {removeHelper(root, id);}
    void search(int id) {searchHelper(root, id);}
    void search(string name, vector<int>* ids) {searchHelper(root, name, ids);}
    void printInorder(vector<string>* names) {printInorderHelper(root, names);}
    void printPreorder(vector<string>* names) {printPreorderHelper(root, names);}
    void printPostorder(vector<string>* names) {printPostorderHelper(root, names);}
    void printLevelCount() {printLevelCountHelper(root);}
    void removeInorder(int n) {removeInorderHelper(root, n);}
    void destruct() {destructHelper(root);}
};