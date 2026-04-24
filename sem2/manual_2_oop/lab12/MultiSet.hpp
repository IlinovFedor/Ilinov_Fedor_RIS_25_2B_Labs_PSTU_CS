#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_MultiSet_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_MultiSet_H
#include "bidirectional.hpp"

template<class T>
class MultiSet : BiList<T> {
public:
    using value_type = T;

    MultiSet() : BiList<T>() {
    };

    MultiSet(const MultiSet &other) : BiList<T>() {
        for (auto &i: other)
            this->push_back(i);
    };

    MultiSet &operator=(const MultiSet &other) {
        this->clear();
        for (Iterator<T> i = other.begin(); i != other.end(); ++i)
                this->push_back(*i);
        return *this;
    };

    bool empty() const {
        return !this->length;
    };

    size_t size() const {
        return BiList<T>::size();
    };

    void insert(const T &value) {
        int idx = 0;
        for (Iterator<T> i = this->begin(); i != this->end(); ++i, idx++) {
            if (*i < value) {
                this->insert_on_index(idx, value);
                return;
            }
        }
        this->push_back(value);
    }

    void erase(const T &v) {
        int i = this->find(v);
        while (i != -1) {
            this->pop(i);
            i = this->find(v);
        }
    };

    Iterator<T> begin() const {
        return BiList<T>::begin();
    }

    Iterator<T> end() const {
        return BiList<T>::end();
    }

    T top() {
        return *BiList<T>::begin();
    }
};


#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_MultiSet_H
