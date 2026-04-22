#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_VECTOR_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_VECTOR_H
#include "Print.h"


class Vector {
protected:
    Object **beg;
    int size;
    int cur;
public:
    Vector();
    Vector(int);

    virtual ~Vector();
    void add(Object *);
    void remove(int);
    friend std::ostream &operator<<(std::ostream &out, const Vector &);
    virtual void handleEvent(const Event &e);
};


#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_VECTOR_H
