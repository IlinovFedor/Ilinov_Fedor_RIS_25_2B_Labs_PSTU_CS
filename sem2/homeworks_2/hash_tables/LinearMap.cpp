#include "LinearMap.h"

#include <cmath>
#include <iostream>

int collision_count = 0;

void LinearMap::createTable(int s) {
    size = s;
    arr = new Human[size];
    for (int i = 0; i < size; ++i)
        arr[i] = Human{"", "", ""};
}

void LinearMap::clearTable() {
    delete[] arr;
    arr = nullptr;
    size = 0;
}

int LinearMap::hashFunction(const std::string &s) {
    if (size == 0)
        return 0;
    Human temp;
    int k = temp.dateToNumber(s);
    double a = M_PI - std::floor(M_PI);
    double frac = k * a - std::floor(k * a);
    double c = size * frac;
    return c;
}

void LinearMap::show() {
    for (int i = 0; i < size; i++) {
        std::cout << i << ' ';
        if (arr[i].getName().empty())
            std::cout << "empty\n";
        else
            std::cout << arr[i] << '\n';
    }
}

int LinearMap::findIndex(const std::string &s) {
    int hash = hashFunction(s);
    int i = hash;

    while (i < size && arr[i].getBirthday() != s)
        i++;

    if (i >= size) {
        i = 0;
        while (i < hash && arr[i].getBirthday() != s)
            i++;
        if (i >= hash)
            return -1;
        return i;
    }
    return i;
}

void LinearMap::add(const Human &s) {
    int i = hashFunction(s.getBirthday());
    int hash = i;

    if (arr[i].getName().empty()) {
        arr[i] = s;
        return;
    }

    while (i < size) {
        if (arr[i].getName().empty()) {
            arr[i] = s;
            return;
        }
        i++;
        collision_count++;
    }
    if (i >= size) {
        i = 0;
        while (i < hash) {
            if (arr[i].getName().empty()) {
                arr[i] = s;
                return;
            }
            i++;
            collision_count++;
        }
        if (i >= hash) {
            std::cout << "Table is full, element can't be added.\n";
        }
    }
}

void LinearMap::pop(const std::string &s) {
    int i = findIndex(s);
    if (i != -1)
        arr[i] = Human("", "", "");
}
