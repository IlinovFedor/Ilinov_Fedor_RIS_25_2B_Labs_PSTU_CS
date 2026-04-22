#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_LINEAR_MAP_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_LINEAR_MAP_H

#include "Human.h"

struct LinearMap {
    Human* arr = nullptr;
    int size = 0;

    void createTable(int s);
    void clearTable();

    void show();
    int findIndex(const std::string&);

    void add(const Human&);
    void pop(const std::string&);

private:
    int hashFunction(const std::string& s);
};

extern int collision_count;

#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_LINEAR_MAP_H
