//
// Created by localuser on 4/8/26.
//

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
    if (cur < size) {
        beg[cur] = p;
        cur++;
    }
}

std::ostream &operator<<(std::ostream &out, const Vector &v) {
    if (v.size == 0)
        std::cout << "Empty\n";
    Object **p = v.beg;
    for (int i = 0; i < v.cur; i++)
        p[i]->show();

    return out;
}
