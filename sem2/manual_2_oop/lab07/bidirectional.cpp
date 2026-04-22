#include "bidirectional.h"
#include <iostream>
#include <fstream>

template<class T>
void BiList<T>::pushBack(T data) {
    auto node = new BiNode<T>;
    node->data = data;
    if (size == 0) {
        head = node;
        tail = node;
        size++;
        return;
    }

    node->prev = tail;
    tail->next = node;
    tail = node;
    size++;
}

template<class T>
void BiList<T>::popBack() {
    if (size == 0)
        return;

    auto del = tail;
    tail = tail->prev;

    if (tail != nullptr)
        tail->next = nullptr;
    else
        head = nullptr;

    delete del;
    size--;
}


template<class T>
void BiList<T>::pushFront(T data) {
    auto node = new BiNode<T>;
    node->data = data;
    if (size == 0) {
        head = node;
        tail = node;
        size++;
        return;
    }

    node->next = head;
    head->prev = node;
    head = node;
    size++;

    
}


template<class T>
void BiList<T>::popFront() {
    if (size == 0)
        return;

    auto del = head;
    head = head->next;

    if (head != nullptr)
        head->prev = nullptr;
    else
        tail = nullptr;

    delete del;
    size--;

    
}


template<class T>
void BiList<T>::insert(int idx, T data) {
    if (idx == size) {
        pushBack(data);
        return;
    }
    if (idx == 0) {
        pushFront(data);
        return;;
    }

    if (!(0 < idx && idx < size)) {
        return;
    }

    auto node = head;
    for (int i = 0; i < idx; i++) {
        node = node->next;
    }

    auto newNode = new BiNode<T>;
    newNode->data = data;

    node->prev->next = newNode;
    newNode->prev = node->prev;

    node->prev = newNode;
    newNode->next = node;

    size++;

    
}


template<class T>
void BiList<T>::remove(int idx) {
    if (!(0 <= idx && idx < size)) {
        return;
    }
    if (idx == 0) {
        popFront();
        return;
    }
    if (idx == size - 1) {
        popBack();
        return;
    }

    auto node = head;
    for (int i = 0; i < idx; i++) {
        node = node->next;
    }

    node->next->prev = node->prev;
    node->prev->next = node->next;

    delete node;
    size--;
}


template<class T>
int BiList<T>::find(T &data) {
    auto node = head;
    int i = 0;
    while (node != nullptr) {
        if (node->data == data) {
            return i;
        }
        i++;
        node = node->next;
    }

    return -1;
}

template<class T>
void BiList<T>::clear() {
    auto node = head;
    while (node != nullptr) {
        auto tmp = node->next;
        delete node;
        node = tmp;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;

    
}


template<class T>
T &BiList<T>::operator[](int idx) {
    if (!(0 <= idx && idx < size)) {
        exit(1);
    }

    auto node = head;
    for (int i = 0; i < idx; i++) {
        node = node->next;
    }

    return node->data;
}

template<class T>
const T &BiList<T>::operator[](int idx) const {
    if (!(0 <= idx && idx < size)) {
        exit(1);
    }

    auto node = head;
    for (int i = 0; i < idx; i++) {
        node = node->next;
    }

    return node->data;
}

template<class T>
BiList<T> &BiList<T>::operator=(const BiList<T> &l) {
    if (this == &l)
        return *this;

    this->clear();
    for (int i = 0; i < l.size; i++) {
        this->pushBack(l[i]);
    }
    
    
    return *this;
}

template<class T>
BiList<T> BiList<T>::operator*(BiList &l) {
    BiList res;
    int range = std::min(l.size, this->size);
    for (int i = 0; i < range; i++) {
        res.pushBack((*this)[i] * l[i]);
    }
    return res;
}

template<class T>
BiList<T>::BiList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<class T>
BiList<T>::BiList(int s) {
    head = nullptr;
    tail = nullptr;
    size = 0;
    for (int i = 0; i < s; i++)
        pushBack(T());

    
}

template<class T>
BiList<T>::BiList(BiList<T> &l) {
    head = nullptr;
    tail = nullptr;
    size = 0;
    for (int i = 0; i < l.size; i++) {
        pushBack(l[i]);
    }
}

template<class T>
std::ostream &operator<<(std::ostream &stream, BiList<T> l) {
    for (int i = 0; i < l(); i++)
        stream << l[i] << '\t';
    return stream;
}

template<class T>
std::istream &operator>>(std::istream &stream, BiList<T> &l) {
    l.clear();
    std::cout << "Size? ";
    int s;
    stream >> s;
    std::cout << "Elements? ";
    for (int i = 0; i < s; i++) {
        T a;
        stream >> a;
        l.pushBack(a);
    }
    return stream;
}

template<class T>
Iterator<T> & Iterator<T>::operator+(int a) {
    for (int i = 0; i < a; i++)
        node = node->next;
    return *this;
}

template<class T>
Iterator<T> & Iterator<T>::operator-(int a) {
    for (int i = 0; i < a; i++)
        node = node->prev;
    return *this;
}

template<class T>
Iterator<T> &Iterator<T>::operator--() {
    node = node->prev;
    return *this;
}

template<class T>
Iterator<T> &Iterator<T>::operator++() {
    node = node->next;
    return *this;
}
