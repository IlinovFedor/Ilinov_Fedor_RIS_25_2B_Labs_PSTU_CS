#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_BI_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_BI_H
#include <iosfwd>

template<class T>
class BiList;
template<class T>
std::ostream &operator<<(std::ostream &, BiList<T>);
template<class T>
std::istream &operator>>(std::istream &, BiList<T> &);
template<class T>
class Iterator;

template<class T>
class BiNode {
    friend BiList<T>;
    friend Iterator<T>;
    BiNode *prev;
    BiNode *next;
    T data;

    BiNode() { prev = nullptr, next = nullptr, data = T(); }
};

template<class T>
class Iterator {
    BiNode<T> *node;

public:
    Iterator() { node = nullptr; }
    Iterator(BiNode<T> *p) { node = p; }
    Iterator(const Iterator &it) { node = it.node; }
    bool operator==(const Iterator &it) { return node == it.node; }
    bool operator!=(const Iterator &it) { return node != it.node; };

    Iterator<T> &operator++();
    Iterator<T> &operator--();
    Iterator<T> &operator+(int);
    Iterator<T> &operator-(int);

    T& operator*() { return node->data; }
    T value() { return node->data; }
    void setValue(T i) { node->data = i; }
};

template<class T>
class BiList {
    BiNode<T> *head;
    BiNode<T> *tail;
    int size;

public:
    BiList<T>();
    BiList<T>(int);
    BiList<T>(BiList<T> &);
    ~BiList<T>() { clear(); }

    void pushBack(T);
    void popBack();
    void pushFront(T);
    void popFront();
    void insert(int, T);
    void remove(int);
    int find(T &);
    void clear();

    T &operator[](int);
    const T &operator[](int) const;
    BiList<T> &operator=(const BiList &);
    int operator()() { return size; }
    BiList<T> operator*(BiList &);

    friend std::ostream &operator<< <>(std::ostream &, BiList<T>);
    friend std::istream &operator>> <>(std::istream &, BiList<T> &);

    Iterator<T> begin() { return Iterator(head); }
    Iterator<T> end() { return Iterator(tail ? tail->next : nullptr); }
};
#include "bidirectional.cpp"
#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_BI_H
