#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_PRIORITYQUEUE_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_PRIORITYQUEUE_H
#include "bidirectional.hpp"

template<class T>
class PriorityQueue : private BiList<T>{
public:
    PriorityQueue() : BiList<T>(){};
    PriorityQueue(const PriorityQueue& other) : BiList<T>(other){};

    PriorityQueue& operator=(const PriorityQueue& other) {
        BiList<T>::operator=(other);
        return *this;
    };

    bool empty() const {
        return !BiList<T>::size();
    };
    size_t size() const {
        return BiList<T>::size();
    };

    T top() {
        T mx = BiList<T>::front();
        for (auto& i : *this)
            if (i > mx) mx = i;
        return mx;
    };

    void push(const T& value) {
        BiList<T>::push_back(value);
    };

    void pop() {
        BiList<T>::remove(top());
    };
};


#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_PRIORITYQUEUE_H
