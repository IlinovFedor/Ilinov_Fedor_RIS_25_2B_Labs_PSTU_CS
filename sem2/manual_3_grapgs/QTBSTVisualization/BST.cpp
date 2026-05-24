#include "BST.h"

BST::~BST() {
    clear();
}

void BST::clear() {
    clearRec(root);
    root = nullptr;
}

void BST::clearRec(Node *node) {
    if (!node) return;
    clearRec(node->left);
    clearRec(node->right);
    delete node;
}

void BST::insert(double key) {
    root = insertRec(root, key);
}

Node *BST::insertRec(Node *node, double key) {
    if (!node) return new Node(key);
    if (key < node->key)
        node->left = insertRec(node->left, key);
    else if (key > node->key)
        node->right = insertRec(node->right, key);
    return node;
}

void BST::remove(double key) {
    root = removeRec(root, key);
}

Node *BST::removeRec(Node *node, double key) {
    if (!node) return nullptr;
    if (key < node->key)
        node->left = removeRec(node->left, key);
    else if (key > node->key)
        node->right = removeRec(node->right, key);
    else {
        if (!node->left) {
            Node *temp = node->right;
            delete node;
            return temp;
        }
        if (!node->right) {
            Node *temp = node->left;
            delete node;
            return temp;
        }
        Node *temp = findMinNode(node->right);
        node->key = temp->key;
        node->right = removeRec(node->right, temp->key);
    }
    return node;
}

Node *BST::findMinNode(Node *node) const {
    while (node && node->left)
        node = node->left;
    return node;
}

Node *BST::search(double key) const {
    return searchRec(root, key);
}

Node *BST::searchRec(Node *node, double key) const {
    if (!node || node->key == key) return node;
    if (key < node->key)
        return searchRec(node->left, key);
    return searchRec(node->right, key);
}

Node *BST::findMin() const {
    return findMinNode(root);
}

std::vector<double> BST::inOrder() const {
    std::vector<double> result;
    inorderRec(root, result);
    return result;
}

void BST::inorderRec(Node *node, std::vector<double> &result) const {
    if (!node) return;
    inorderRec(node->left, result);
    result.push_back(node->key);
    inorderRec(node->right, result);
}

std::vector<double> BST::preOrder() const {
    std::vector<double> result;
    preorderRec(root, result);
    return result;
}

void BST::preorderRec(Node *node, std::vector<double> &result) const {
    if (!node) return;
    result.push_back(node->key);
    preorderRec(node->left, result);
    preorderRec(node->right, result);
}

std::vector<double> BST::postOrder() const {
    std::vector<double> result;
    postorderRec(root, result);
    return result;
}

void BST::postorderRec(Node *node, std::vector<double> &result) const {
    if (!node) return;
    postorderRec(node->left, result);
    postorderRec(node->right, result);
    result.push_back(node->key);
}

void BST::balance() {
    std::vector<double> keys = inOrder();
    clear();
    root = balanceRec(keys, 0, static_cast<int>(keys.size()) - 1);
}

Node *BST::balanceRec(const std::vector<double> &keys, int l, int r) {
    if (l > r) return nullptr;
    int mid = (l + r) / 2;
    auto *node = new Node(keys[mid]);
    node->left = balanceRec(keys, l, mid - 1);
    node->right = balanceRec(keys, mid + 1, r);
    return node;
}
