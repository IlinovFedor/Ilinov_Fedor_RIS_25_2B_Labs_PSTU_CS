#include "bidirectional.h"
#include <iostream>
#include <fstream>

void BiList::pushBack(int data) {
    auto node = new BiNode;
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


void BiList::popBack() {
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


void BiList::pushFront(int data) {
    auto node = new BiNode;
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


void BiList::popFront() {
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


void BiList::insert(int idx, int data) {
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

    auto newNode = new BiNode;
    newNode->data = data;

    node->prev->next = newNode;
    newNode->prev = node->prev;

    node->prev = newNode;
    newNode->next = node;

    size++;

    
}


void BiList::remove(int idx) {
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


int BiList::find(int &data) {
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

void BiList::clear() {
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


int &BiList::operator[](int idx) {
    if (!(0 <= idx && idx < size)) {
        exit(1);
    }

    auto node = head;
    for (int i = 0; i < idx; i++) {
        node = node->next;
    }

    return node->data;
}

BiList &BiList::operator=(BiList &l) {
    if (this == &l)
        return *this;

    this->clear();
    for (int i = 0; i < l.size; i++) {
        this->pushBack(l[i]);
    }
    
    
    return *this;
}

BiList BiList::operator*(BiList &l) {
    BiList res;
    int range = std::min(l.size, this->size);
    for (int i = 0; i < range; i++) {
        res.pushBack((*this)[i] * l[i]);
    }
    return res;
}

BiList::BiList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

BiList::BiList(int s) : BiList() {
    for (int i = 0; i < s; i++)
        pushBack(0);

    
}

BiList::BiList(BiList &l) : BiList() {
    for (int i = 0; i < l.size; i++) {
        pushBack(l[i]);
    }
}

std::ostream &operator<<(std::ostream &stream, BiList l) {
    for (int i = 0; i < l(); i++)
        stream << l[i] << '\t';
    stream << '\n';
    return stream;
}

std::istream &operator>>(std::istream &stream, BiList &l) {
    std::cout << "Size? ";
    int s;
    stream >> s;
    std::cout << "Elements? ";
    for (int i = 0; i < s; i++) {
        int a;
        stream >> a;
        l.pushBack(a);
    }
    return stream;
}

Iterator & Iterator::operator+(int a) {
    for (int i = 0; i < a; i++)
        node = node->next;
    return *this;
}

Iterator & Iterator::operator-(int a) {
    for (int i = 0; i < a; i++)
        node = node->prev;
    return *this;
}

Iterator &Iterator::operator--() {
    node = node->prev;
    return *this;
}

Iterator &Iterator::operator++() {
    node = node->next;
    return *this;
}