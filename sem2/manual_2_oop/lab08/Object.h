#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_OBJECT_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_OBJECT_H
#include "Event.h"


class Object {
public:
    virtual void show() = 0;
    virtual void input() = 0;
    virtual void handleEvent(const Event &e)=0;
    virtual const std::string getName() = 0;
};


#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_OBJECT_H
