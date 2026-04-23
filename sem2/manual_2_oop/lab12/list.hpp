#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_List_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_List_H
#include <set>

template<class T>
class List {
    std::multiset<T> data;
public:

    using value_type = T;
    List() {};
    List(const List& other) {
        for (auto& i : other)
            data.insert(i);
    };

    List& operator=(const List& other) {
        data = other.data;
        return *this;
    };

    bool empty() const {
        return !data.size();
    };
    size_t size() const {
        return data.size();
    };

    void insert(const T& value) {
        data.insert(value);
    };

    void erase(const T& v) {
        data.erase(v);
    };

    typename std::multiset<T>::const_iterator begin() const {
        return data.begin();
    }

    typename std::multiset<T>::const_iterator end() const {
        return data.end();
    }
};


#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_List_H
