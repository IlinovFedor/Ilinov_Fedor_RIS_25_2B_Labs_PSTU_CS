#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_BI_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_BI_H
#include <iosfwd>

class BiList;
class Iterator;

class BiNode {
    friend BiList;
    friend Iterator;
    BiNode *prev;
    BiNode *next;
    int data;

    BiNode() { prev = nullptr, next = nullptr, data = 0; }
};

class Iterator {
    BiNode *node;

public:
    Iterator() { node = nullptr; }
    Iterator(BiNode *p) { node = p; }
    Iterator(const Iterator &it) { node = it.node; }
    bool operator==(const Iterator &it) { return node == it.node; }
    bool operator!=(const Iterator &it) { return node != it.node; };

    Iterator &operator++();
    Iterator &operator--();
    Iterator &operator+(int);
    Iterator &operator-(int);

    int& operator*() { return node->data; }
    int value() { return node->data; }
    void setValue(int i) { node->data = i; }
};

class BiList {
    const int max_size = 100;
    BiNode *head;
    BiNode *tail;
    int size;

public:
    BiList();
    BiList(int);
    BiList(BiList &);
    ~BiList() { clear(); }

    void pushBack(int);
    void popBack();
    void pushFront(int);
    void popFront();
    void insert(int, int);
    void remove(int);
    int find(int &);
    void clear();

    int &operator[](int);
    BiList &operator=(BiList &);
    int operator()() { return size; }
    BiList operator*(BiList &);

    friend std::ostream &operator<<(std::ostream &, BiList);
    friend std::istream &operator>>(std::istream &, BiList &);

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(tail->next); }
};

#endif ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_BI_H
