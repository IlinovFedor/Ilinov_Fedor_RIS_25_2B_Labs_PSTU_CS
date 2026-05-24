#ifndef QTGRAPHVISUALIZATION_BST_H
#define QTGRAPHVISUALIZATION_BST_H

#include <vector>

struct Node {
    double key;
    Node *left = nullptr;
    Node *right = nullptr;
    explicit Node(double k) : key(k) {}
};

class BST {
    Node *root = nullptr;

    Node *insertRec(Node *node, double key);
    Node *removeRec(Node *node, double key);
    Node *findMinNode(Node *node) const;
    Node *searchRec(Node *node, double key) const;
    void inorderRec(Node *node, std::vector<double> &result) const;
    void preorderRec(Node *node, std::vector<double> &result) const;
    void postorderRec(Node *node, std::vector<double> &result) const;
    Node *balanceRec(const std::vector<double> &keys, int l, int r);
    void clearRec(Node *node);

public:
    BST() = default;
    ~BST();

    void insert(double key);
    void remove(double key);
    Node *search(double key) const;
    Node *findMin() const;
    std::vector<double> inOrder() const;
    std::vector<double> preOrder() const;
    std::vector<double> postOrder() const;
    void balance();
    void clear();
    Node *getRoot() const { return root; }
};

#endif
