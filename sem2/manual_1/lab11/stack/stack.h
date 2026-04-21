#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_STACK_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_STACK_H
#include <iosfwd>
#include "../errors.h"


template<class T>
struct StackNode {
    T data;
    StackNode* next = nullptr;
};

template<class T>
struct StackResult {
    StackNode<T>* node = nullptr;
    int error = ok;
};

template<class T>
struct Stack {
    StackNode<T> * head = nullptr;
    int size = 0;

    void push(T&);
    void pop();
    StackResult<T> peek();

    void print(std::ostream&);
    void clear();
};

#include "stack.cpp"
#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_STACK_H