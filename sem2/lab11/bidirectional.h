#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_BI_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_BI_H
#include <iosfwd>
#include "errors.h"


template<class T>
struct BiNode {
    BiNode* prev = nullptr;
    T data;
    BiNode* next = nullptr;
};

template<class T>
struct BiResult {
    BiNode<T>* node = nullptr;
    int error = ok;
};

template<class T>
struct BiList {
    BiNode<T> * head = nullptr;
    BiNode<T> * tail = nullptr;
    int size = 0;

    void pushBack(T&);
    void popBack();

    void pushFront(T&);
    void popFront();

    BiResult<T> insert(int, T&);
    BiResult<T> remove(int);
    BiResult<T> get(int);
    int find(T&);

    void print(std::ostream&);
    void clear();
};

#include "bidirectional.cpp"
#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_BI_H