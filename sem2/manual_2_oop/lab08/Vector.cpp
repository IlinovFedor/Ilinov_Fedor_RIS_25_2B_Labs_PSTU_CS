#include "Vector.h"

#include <iostream>

Vector::Vector() {
    beg = 0;
    size = 0;
    cur = 0;
}

Vector::~Vector() {
    if (beg != 0)delete [] beg;
    beg = 0;
}

Vector::Vector(int n) {
    beg = new Object *[n];
    cur = 0;
    size = n;
}

void Vector::add(Object *p) {
    if (cur >= size) {
        int newSize = (size == 0) ? 1 : size * 2;

        Object **newArr = new Object *[newSize];

        for (int i = 0; i < cur; ++i)
            newArr[i] = beg[i];

        delete[] beg;

        beg = newArr;
        size = newSize;
    }

    beg[cur++] = p;
}

void Vector::remove(int idx) {
    for (int i = idx + 1; i < cur; i++)
        beg[i - 1] = beg[i];
    beg[cur--] = nullptr;
}

std::ostream &operator<<(std::ostream &out, const Vector &v) {
    if (v.size == 0)
        std::cout << "Empty\n";
    Object **p = v.beg;
    for (int i = 0; i < v.cur; i++) {
        p[i]->show();
        std::cout << '\n';
    }

    return out;
}

void Vector::handleEvent(const Event &e) {
    if (e.what == evMessage) {
        Object **p = beg;
        for (int i = 0; i < cur; i++) {
            (*p)->handleEvent(e);
            p++;
        }
    }
}
