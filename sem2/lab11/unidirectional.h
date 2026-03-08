#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_UNI_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_UNI_H
#include <iosfwd>
#include "errors.h"


template<class T>
struct UniNode {
    T data;
    UniNode* next = nullptr;
};

template<class T>
struct UniResult {
    UniNode<T>* node = nullptr;
    int error = ok;
};

template<class T>
struct UniList {
    UniNode<T> * head = nullptr;
    UniNode<T> * tail = nullptr;
    int size = 0;

    void pushBack(T&);
    void popBack();

    void pushFront(T&);
    void popFront();

    UniResult<T> insert(int, T&);
    UniResult<T> remove(int);
    UniResult<T> get(int);
    int find(T&);

    void print(std::ostream&);
    void clear();
};

#include "unidirectional.cpp"
#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_UNI_H