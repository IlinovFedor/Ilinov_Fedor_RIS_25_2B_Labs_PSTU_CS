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

    T &operator*() { return node->data; }
    T value() { return node->data; }
    void setValue(T i) { node->data = i; }
};

template<class T>
class BiList {
    BiNode<T> *head;
    BiNode<T> *tail;
    int length = 0;

public:
    using value_type = T;

    BiList<T>();

    BiList<T>(int);

    BiList<T>(const BiList<T> &);

    ~BiList<T>() { clear(); }

    void push_back(T);

    void popBack();

    void pushFront(T);

    void popFront();

    void insert(int, T);

    void pop(int);

    int find(const T &);

    void clear();

    size_t size() const;

    void remove(const T &a);

    T &operator[](int);

    const T &operator[](int) const;

    BiList<T> &operator=(const BiList &);

    int operator()() const;

    BiList<T> operator*(BiList &);

    Iterator<T> begin() const { return Iterator(head); }
    Iterator<T> end() const { return Iterator(tail ? tail->next : nullptr); }

    T front();

    T back();
};

#include "bidirectional.hpp"
#include <iostream>
#include <fstream>

template<class T>
void BiList<T>::push_back(T data) {
    auto node = new BiNode<T>;
    node->data = data;
    if (length == 0) {
        head = node;
        tail = node;
        length++;
        return;
    }

    node->prev = tail;
    tail->next = node;
    tail = node;
    length++;
}

template<class T>
void BiList<T>::popBack() {
    if (length == 0)
        return;

    auto del = tail;
    tail = tail->prev;

    if (tail != nullptr)
        tail->next = nullptr;
    else
        head = nullptr;

    delete del;
    length--;
}


template<class T>
void BiList<T>::pushFront(T data) {
    auto node = new BiNode<T>;
    node->data = data;
    if (length == 0) {
        head = node;
        tail = node;
        length++;
        return;
    }

    node->next = head;
    head->prev = node;
    head = node;
    length++;
}


template<class T>
void BiList<T>::popFront() {
    if (length == 0)
        return;

    auto del = head;
    head = head->next;

    if (head != nullptr)
        head->prev = nullptr;
    else
        tail = nullptr;

    delete del;
    length--;
}


template<class T>
void BiList<T>::insert(int idx, T data) {
    if (idx == length) {
        push_back(data);
        return;
    }
    if (idx == 0) {
        pushFront(data);
        return;;
    }

    if (!(0 < idx && idx < length)) {
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

    length++;
}


template<class T>
void BiList<T>::pop(int idx) {
    if (!(0 <= idx && idx < length)) {
        return;
    }
    if (idx == 0) {
        popFront();
        return;
    }
    if (idx == length - 1) {
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
    length--;
}


template<class T>
int BiList<T>::find(const T &data) {
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
    length = 0;
}

template<class T>
size_t BiList<T>::size() const {
    return length;
}

template<class T>
void BiList<T>::remove(const T &a) {
    while (find(a) != -1)
        pop(find(a));
}


template<class T>
T &BiList<T>::operator[](int idx) {
    if (!(0 <= idx && idx < length)) {
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
    if (!(0 <= idx && idx < length)) {
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
    for (int i = 0; i < l.size(); i++) {
        this->push_back(l[i]);
    }


    return *this;
}

template<class T>
BiList<T> BiList<T>::operator*(BiList &l) {
    BiList res;
    int range = std::min(l.size(), this->size());
    for (int i = 0; i < range; i++) {
        res.push_back((*this)[i] * l[i]);
    }
    return res;
}

template<class T>
T BiList<T>::front() {
    return head->data;
}

template<class T>
T BiList<T>::back() {
    return tail->data;
}

template<class T>
BiList<T>::BiList() {
    head = nullptr;
    tail = nullptr;
    length = 0;
}

template<class T>
BiList<T>::BiList(int s) {
    head = nullptr;
    tail = nullptr;
    length = 0;
    for (int i = 0; i < s; i++)
        push_back(T());
}

template<class T>
BiList<T>::BiList(const BiList<T> &l) {
    head = nullptr;
    tail = nullptr;
    length = 0;
    for (int i = 0; i < l.size(); i++) {
        push_back(l[i]);
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
        l.push_back(a);
    }
    return stream;
}

template<class T>
Iterator<T> &Iterator<T>::operator+(int a) {
    for (int i = 0; i < a; i++)
        node = node->next;
    return *this;
}

template<class T>
Iterator<T> &Iterator<T>::operator-(int a) {
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


#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_BI_H
