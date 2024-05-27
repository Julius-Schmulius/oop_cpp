#include <iostream>
#include <string>
#include <sstream>

class Node {
public:
    std::string key;
    Node* left;
    Node* right;
    Node(std::string key) : key(key), left(nullptr), right(nullptr) {} //constructor : initialization list
};

void insert(Node*& root, std::string key) {
    if (root == nullptr) {
        root = new Node(key);
    } else if (key < root->key) {
        insert(root->left, key);
    } else if (key > root->key) {
        insert(root->right, key);
    }
}

void list(Node* root) { //in order traversal
    if (root != nullptr) {
        list(root->left); //recursive call to left subtree
        std::cout << root->key << "\n";
        list(root->right); //recursive call to right subtree
    }
}

void freeTree(Node*& root) {
    if (root != nullptr) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
        root = nullptr;
    }
}

int main() {
    Node* root = nullptr;
    std::string line;
    std::cout << "Input will be sorted character wise by ASCII values. Enter '.' to stop." << std::endl;
    while (true) {
        std::cout << "Enter a word: ";
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string word;
        iss >> word; //extract first word from the line
        if (word.empty()) continue;
        if (word == ".") break;
        insert(root, word);
    }
    list(root);
    freeTree(root);
    return 0;
}
