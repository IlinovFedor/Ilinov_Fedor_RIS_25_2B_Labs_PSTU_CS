#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_QUEUE_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_QUEUE_H
#include <iosfwd>
#include "errors.h"


template<class T>
struct QueueNode {
    T data;
    QueueNode* next = nullptr;
};

template<class T>
struct QueueResult {
    QueueNode<T>* node = nullptr;
    int error = ok;
};

template<class T>
struct Queue {
    QueueNode<T> * head = nullptr;
    QueueNode<T> * tail = nullptr;
    int size = 0;

    void pushBack(T&);
    void popFront();
    QueueResult<T> insert(int, T&);
    QueueResult<T> peek();

    void print(std::ostream&);
    void clear();
};

#include "queue.cpp"
#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_QUEUE_H