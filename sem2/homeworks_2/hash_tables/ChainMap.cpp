#include "ChainMap.h"

#include <cmath>
#include <iostream>

void ChainMap::createTable(int s) {
    size = s;
    arr = new UniList<Human>*[size];
    for (int i = 0; i < size; ++i)
        arr[i] = new UniList<Human>();
}

void ChainMap::clearTable() {
    if (arr == nullptr)
        return;
    for (int i = 0; i < size; ++i) {
        if (arr[i] != nullptr) {
            arr[i]->clear();
            delete arr[i];
            arr[i] = nullptr;
        }
    }
    delete[] arr;
    arr = nullptr;
    size = 0;
}

int ChainMap::hashFunction(const std::string &s) {
    if (size == 0)
        return 0;
    Human temp;
    int k = temp.dateToNumber(s);
    double pi = std::acos(-1.0);
    double a = pi - std::floor(pi);
    double frac = k * a - std::floor(k * a);
    double c = size * frac;
    return c;
}

int ChainMap::findIndexByKey(UniList<Human>* list, const std::string &key) {
    if (list == nullptr)
        return -1;
    auto node = list->head;
    for (int i = 0; node != nullptr; i++) {
        if (node->data.getBirthday() == key)
            return i;
        node = node->next;
    }
    return -1;
}

void ChainMap::deleteByDate(UniList<Human>* list, const std::string &key) {
    if (list == nullptr || list->head == nullptr) {
        std::cout << "List is empty\n";
        return;
    }
    auto node = list->head;
    int ind = 0;
    while (node != nullptr) {
        if (node->data.getBirthday() == key)
            break;
        node = node->next;
        ++ind;
    }
    if (node == nullptr) {
        std::cout << "Element with date \"" << key << "\" not found\n";
        return;
    }
    list->remove(ind);
}

void ChainMap::printListHuman(UniList<Human>* list) {
    if (list == nullptr)
        return;
    auto node = list->head;
    while (node != nullptr) {
        std::cout << node->data << '\n';
        node = node->next;
    }
}

void ChainMap::show() {
    for (int i = 0; i < size; i++) {
        std::cout << "Bucket index: " << i << '\n';
        printListHuman(arr[i]);
    }
}

int ChainMap::findIndex(const std::string &to_find) {
    int hash = hashFunction(to_find);
    return hash;
}

void ChainMap::add(const Human &to_add) {
    int ind = hashFunction(to_add.getBirthday());
    if (arr[ind] == nullptr)
        return;
    collision_count += arr[ind]->size;
    Human tmp = to_add;
    arr[ind]->pushBack(tmp);
}

void ChainMap::pop(const std::string &to_delete) {
    int ind = findIndex(to_delete);
    if (ind < 0 || ind >= size)
        return;
    int index_list = findIndexByKey(arr[ind], to_delete);
    if (index_list != -1)
        deleteByDate(arr[ind], to_delete);
}
