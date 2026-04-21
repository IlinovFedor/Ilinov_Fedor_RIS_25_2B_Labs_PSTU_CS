#include "../bidirectional.h"
#include "../errors.h"
#include <iostream>
#include <fstream>

template<class T>
void BiList<T>::pushBack(T& data) {
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
void BiList<T>::pushFront(T & data) {
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
BiResult<T> BiList<T>::insert(int idx, T & data) {
    BiResult<T> res;
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
    for (int i = 0; i < idx; i++) {
        node = node->next;
    }

    auto newNode = new BiNode<T>;
    newNode->data = data;

    node->prev->next = newNode;
    newNode->prev = node->prev;

    node->prev = newNode;
    newNode->next = node;

    res.node = newNode;
    size++;
    return res;
}

template<class T>
BiResult<T> BiList<T>::remove(int idx) {
    BiResult<T> res;
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
    for (int i = 0; i < idx; i++) {
        node = node->next;
    }

    node->next->prev = node->prev;
    node->prev->next = node->next;

    delete node;
    size--;
    return res;
}

template<class T>
BiResult<T> BiList<T>::get(int idx) {
    BiResult<T> res;
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
int BiList<T>::find(T & data) {
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
void BiList<T>::print(std::ostream& stream) {
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

int mainBi() {
    using namespace std;
    int n, m, k;
    BiList<string> list;
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
