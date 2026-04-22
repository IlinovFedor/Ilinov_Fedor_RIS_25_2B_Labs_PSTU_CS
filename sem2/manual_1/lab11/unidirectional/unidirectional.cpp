#include "unidirectional.h"
#include "../errors.h"
#include <iostream>
#include <fstream>

#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_UNI_CPP
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_UNI_CPP

template<class T>
void UniList<T>::pushBack(T& data) {
    auto node = new UniNode<T>;
    node->data = data;
    if (size == 0) {
        head = node;
        tail = node;
        size++;
        return;
    }

    tail->next = node;
    tail = node;
    size++;
}

template<class T>
void UniList<T>::popBack() {
    if (size == 0)
        return;

    if (size == 1) {
        delete head;
        head = nullptr;
        tail = nullptr;
        size--;
        return;
    }

    auto node = head;
    while (node->next != tail)
        node = node->next;

    delete tail;
    tail = node;
    tail->next = nullptr;
    size--;
}

template<class T>
void UniList<T>::pushFront(T & data) {
    auto node = new UniNode<T>;
    node->data = data;
    if (size == 0) {
        head = node;
        tail = node;
        size++;
        return;
    }

    node->next = head;
    head = node;
    size++;
}

template<class T>
void UniList<T>::popFront() {
    if (size == 0)
        return;

    auto del = head;
    head = head->next;

    if (head == nullptr)
        tail = nullptr;

    delete del;
    size--;
}

template<class T>
UniResult<T> UniList<T>::insert(int idx, T & data) {
    UniResult<T> res;
    if (idx == 0) {
        pushFront(data);
        return res;
    }
    if (idx == size) {
        pushBack(data);
        return res;
    }
    if (!(0 < idx && idx < size)) {
        res.error = outOfRange;
        return res;
    }

    auto node = head;
    for (int i = 0; i < idx - 1; i++)
        node = node->next;

    auto newNode = new UniNode<T>;
    newNode->data = data;
    newNode->next = node->next;
    node->next = newNode;

    res.node = newNode;
    size++;
    return res;
}

template<class T>
UniResult<T> UniList<T>::remove(int idx) {
    UniResult<T> res;
    if (!(0 <= idx && idx < size)) {
        res.error = outOfRange;
        return res;
    }
    if (idx == 0) {
        popFront();
        return res;
    }
    if (idx == size - 1) {
        popBack();
        return res;
    }

    auto node = head;
    for (int i = 0; i < idx - 1; i++)
        node = node->next;

    auto del = node->next;
    node->next = del->next;
    delete del;
    size--;
    return res;
}

template<class T>
UniResult<T> UniList<T>::get(int idx) {
    UniResult<T> res;
    if (!(0 <= idx && idx < size)) {
        res.error = outOfRange;
        return res;
    }

    auto node = head;
    for (int i = 0; i < idx; i++) {
        node = node->next;
    }

    res.node = node;
    return res;
}

template<class T>
int UniList<T>::find(T & data) {
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
void UniList<T>::print(std::ostream& stream) {
    if (size == 0) {
        stream << "empty\n";
        return;
    }
    auto node = head;
    while (node != nullptr) {
        stream << node->data << ' ';
        node = node->next;
    }
    stream << '\n';
}

template<class T>
void UniList<T>::clear() {
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


#ifndef UNI_EXPORT
int mainUni() {
    using namespace std;
    int n, m, k;
    UniList<string> list;
    cout << "Size:\n";
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        list.pushBack(s);
    }
    list.print(cout);

    cout << "Delete:\n";
    cin >> m;
    list.remove(m - 1);
    list.print(cout);
    cout << "Key:\n";
    string key;
    cin >> key;
    int idx = list.find(key);
    cout << "Index: " << idx << '\n';
    cout << "Amount:\n";
    cin >> k;


    cout << "First " << k << " words:\n";
    for (int i = 0; i < k; i++) {
        string s;
        cin >> s;
        list.insert(idx, s);
        idx++;
        list.print(cout);
    }

    idx++;
    cout << "Second " << k << " words:\n";
    for (int i = 0; i < k; i++) {
        string s;
        cin >> s;
        list.insert(idx, s);
        idx++;
        list.print(cout);
    }

    fstream file("file.txt", ios::in | ios::out);
    list.print(file);
    file.seekp(0);

    list.clear();
    list.print(cout);
    for (int i = 0; i < n - 1 + 2 * k; i++) {
        string s;
        file >> s;
        list.pushBack(s);
    }
    file.close();
    list.print(cout);
    list.clear();

    return 0;
}
#endif

#endif