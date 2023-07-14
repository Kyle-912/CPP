#include "AVL.h"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

Node::Node(string name, int id) {
    this->name = name;
    this->id = id;
    this->height = 1;
    this->left = nullptr;
    this->right = nullptr;
}

int getHeight(Node* node) { //for those damn seg faults
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int getBalance(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

Node* leftRotation(Node* node) {
    Node* newParent = node->right;
    Node* adoptedChild = newParent->left;

    newParent->left = node;
    node->right = adoptedChild;

    if (getHeight(node->left) > getHeight(node->right)) {
        node->height = getHeight(node->left) + 1;
    } else {
        node->height = getHeight(node->right) + 1;
    }
    if (getHeight(newParent->left) > getHeight(newParent->right)) {
        newParent->height = getHeight(newParent->left) + 1;
    } else {
        newParent->height = getHeight(newParent->right) + 1;
    }
    return newParent;
}

Node* rightRotation(Node* node) {
    Node* newParent = node->left;
    Node* adoptedChild = newParent->right;

    newParent->right = node;
    node->left = adoptedChild;

    if (getHeight(node->left) > getHeight(node->right)) {
        node->height = getHeight(node->left) + 1;
    } else {
        node->height = getHeight(node->right) + 1;
    }
    if (getHeight(newParent->left) > getHeight(newParent->right)) {
        newParent->height = getHeight(newParent->left) + 1;
    } else {
        newParent->height = getHeight(newParent->right) + 1;
    }
    return newParent;
}

Node* AVL::insertHelper(Node* node, string name, int id) {
    if (node == nullptr) {
        cout << "successful" << endl;
        return new Node (name, id);
    } else if (id < node->id) {
        node->left = insertHelper(node->left, name, id);
    } else if (id > node->id) {
        node->right = insertHelper(node->right, name, id);
    } else {
        cout << "unsuccessful" << endl;
        return node;
    }
    if (getHeight(node->left) > getHeight(node->right)) {
        node->height = getHeight(node->left) + 1;
    } else {
        node->height = getHeight(node->right) + 1;
    }
    int balance = getBalance(node);
    if (balance > 1 && id < node->left->id) {
        return rightRotation(node);
    }
    if (balance < -1 && id > node->right->id) {
        return leftRotation(node);
    }
    if (balance > 1 && id > node->left->id) {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }
    if (balance < -1 && id < node->right->id) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }
    return node;
}

void AVL::searchHelper(Node* root, int id) {
    if (root == nullptr) {
        cout << "unsuccessful" << endl;
    } else if (root->id == id) {
        cout << root->name << endl;
    } else if (id < root->id) {
        searchHelper(root->left, id);
    } else if (id > root->id) {
        searchHelper(root->right, id);
    } else {
        cout << "unsuccessful" << endl;
    }
}

void AVL::searchHelper(Node* root, string name, vector<int>* ids) {
    if (root != nullptr) {
        if (root->name == name) {
            ids->push_back(root->id);
        }
        if (root->left != nullptr) {
            searchHelper(root->left, name, ids);
        }
        if (root->right != nullptr) {
            searchHelper(root->right, name, ids);
        }
    }
}

void AVL::printInorderHelper(Node *root, vector<string>* names) {
    if (root != nullptr) {
        if (root->left != nullptr) {
            printInorderHelper(root->left, names);
        }
        names->push_back(root->name);
        if (root->right != nullptr) {
            printInorderHelper(root->right, names);
        }
    }
}

void AVL::printPreorderHelper(Node *root, vector<string>* names) {
    if (root != nullptr) {
        names->push_back(root->name);
        if (root->left != nullptr) {
            printPreorderHelper(root->left, names);
        }
        if (root->right != nullptr) {
            printPreorderHelper(root->right, names);
        }
    }
}

void AVL::printPostorderHelper(Node *root, vector<string>* names) {
    if (root != nullptr) {
        if (root->left != nullptr) {
        printPostorderHelper(root->left, names);
        }
        if (root->right != nullptr) {
        printPostorderHelper(root->right, names);
        }
        names->push_back(root->name);
    }
}

void AVL::printLevelCountHelper(Node *root) {
    cout << getHeight(root) << endl;
}

void updateHeight(Node* root) {
    if (root->left) {
        root->left->height -= 1;
        updateHeight(root->left);
    }
    if (root->right) {
        root->right->height -= 1;
        updateHeight(root->right);
    }
}

void AVL::removeHelper(Node *root, int id) {
    if (root != nullptr) {
        if (root->id == id) {
            if (root->left == nullptr && root->right == nullptr) {
                destructHelper(root);
            } else if (root->left != nullptr && root->right != nullptr) {
                Node* iosParent = root->right;
                while (iosParent->left != nullptr) {
                    while (iosParent->left->left != nullptr) {
                        iosParent = iosParent->left;
                    }
                }
                if (iosParent->left) {
                    root->id = iosParent->left->id;
                    root->name = iosParent->left->name;
                    Node* temp = iosParent->left->right;
                    delete iosParent->left;
                    iosParent->left = temp;
                    iosParent->left->height -= 1;
                    updateHeight(iosParent->left);
                } else {
                    root->id = iosParent->id;
                    root->name = iosParent->name;
                    root->right = iosParent->right;
                    delete iosParent;
                    root->right->height -= 1;
                    updateHeight(root->right);
                }
            } else if (root->left != nullptr && root->right == nullptr){
                root->id = root->left->id;
                root->name = root->left->name;
                delete root->left;
                root->left = nullptr;
            } else {
                root->id = root->right->id;
                root->name = root->right->name;
                delete root->right;
                root->right = nullptr;
            }
            cout << "successful" << endl;
        } else if (root->left->id == id) {
            if (root->left->left == nullptr && root->left->right == nullptr) {
                delete root->left;
                root->left = nullptr;
            } else if (root->left->left != nullptr && root->left->right != nullptr) {
                Node* iosParent = root->left->right;
                while (iosParent->left != nullptr) {
                    while (iosParent->left->left != nullptr) {
                        iosParent = iosParent->left;
                    }
                }
                if (iosParent->left) {
                    root->left->id = iosParent->left->id;
                    root->left->name = iosParent->left->name;
                    Node* temp = iosParent->left->right;
                    delete iosParent->left;
                    iosParent->left = temp;
                    iosParent->left->height -= 1;
                    updateHeight(iosParent->left);
                } else {
                    root->left->id = iosParent->id;
                    root->left->name = iosParent->name;
                    root->left->right = iosParent->right;
                    delete iosParent;
                    root->left->right->height -= 1;
                    updateHeight(root->left->right);
                }
            } else if (root->left->left != nullptr && root->left->right == nullptr){
                root->left->id = root->left->left->id;
                root->left->name = root->left->left->name;
                Node* temp = root->left->left;
                root->left->left = root->left->left->left;
                root->left->right = root->left->left->right;
                delete temp;
                updateHeight(root->left);
            } else {
                root->left->id = root->left->right->id;
                root->left->name = root->left->right->name;
                Node* temp = root->left->right;
                root->left->left = root->left->right->left;
                root->left->right = root->left->right->right;
                delete temp;
                updateHeight(root->right);
            }
            cout << "successful" << endl;
        } else if (root->right->id == id) {
            if (root->right->left == nullptr && root->right->right == nullptr) {
                delete root->right;
                root->right = nullptr;
            } else if (root->right->left != nullptr && root->right->right != nullptr) {
                Node* iosParent = root->right->right;
                while (iosParent->left != nullptr) {
                    while (iosParent->left->left != nullptr) {
                        iosParent = iosParent->left;
                    }
                }
                if (iosParent->left) {
                    root->right->id = iosParent->left->id;
                    root->right->name = iosParent->left->name;
                    Node* temp = iosParent->left->right;
                    delete iosParent->left;
                    iosParent->left = temp;
                    iosParent->left->height -= 1;
                    updateHeight(iosParent->left);
                } else {
                    root->right->id = iosParent->id;
                    root->right->name = iosParent->name;
                    root->right->right = iosParent->right;
                    delete iosParent;
                    root->right->right->height -= 1;
                    updateHeight(root->right->right);
                }
            } else if (root->right->left != nullptr && root->right->right == nullptr){
                root->right->id = root->right->left->id;
                root->right->name = root->right->left->name;
                Node* temp = root->right->left;
                root->right->left = root->right->left->left;
                root->right->right = root->right->left->right;
                delete temp;
                updateHeight(root->left);
            } else {
                root->right->id = root->right->right->id;
                root->right->name = root->right->right->name;
                Node* temp = root->right->right;
                root->right->left = root->right->right->left;
                root->right->right = root->right->right->right;
                delete temp;
                updateHeight(root->right);
            }
            cout << "successful" << endl;
        } else if (id < root->id) {
            removeHelper(root->left, id);
        } else if (id > root->id) {
            removeHelper(root->right, id);
        } else {
            cout << "unsuccessful" << endl;
        }
    } else {
        cout << "unsuccessful" << endl;
    }
}

void removeInorderVector(Node* root, vector<int>* ids) {
    if (root->left != nullptr) {
        removeInorderVector(root->left, ids);
    }
    ids->push_back(root->id);
    if (root->right != nullptr) {
        removeInorderVector(root->right, ids);
    }
}

void AVL::removeInorderHelper(Node *root, int n) {
    vector<int> ids;
    vector<int>* idsptr = &ids;
    removeInorderVector(root, idsptr);
    removeHelper(root, ids[n]);
}

void AVL::destructHelper(Node* root) {
    if (root->left)
        destructHelper(root->left);
    if (root->right)
        destructHelper(root->right);
    delete root;
}