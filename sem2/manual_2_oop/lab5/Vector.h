//
// Created by localuser on 4/8/26.
//

#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_VECTOR_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_VECTOR_H
#include "Person.h"


class Vector {
    Object **beg;
    int size;
    int cur;
public:
    Vector();
    Vector(int);
    ~Vector();
    void add(Object *);
    friend std::ostream &operator<<(std::ostream &out, const Vector &);
};


#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_VECTOR_H
