#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_CHAIN_MAP_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_CHAIN_MAP_H
#define UNI_EXPORT
#include "Human.h"
#include "../../manual_1/lab11/unidirectional/unidirectional.h"

struct ChainMap {
    UniList<Human>** arr = nullptr;
    int size = 0;

    void createTable(int s);
    void clearTable();

    void show();
    int findIndex(const std::string&) ;

    void add(const Human&);
    void pop(const std::string&);

private:
    int hashFunction(const std::string& s);
    int findIndexByKey(UniList<Human>*, const std::string&);
    void deleteByDate(UniList<Human>*, const std::string&);
    void printListHuman(UniList<Human>*);
};

extern int collision_count;

#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_CHAIN_MAP_H
