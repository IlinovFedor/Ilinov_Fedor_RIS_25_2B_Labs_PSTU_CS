#include <iostream>

template<typename T>
int linear(const T a[], const int &n, const T &key) {
    std::cout << "=====================================================linear search======================================================\n";
    for (int i = 0; i < n; i++) {
        std::cout << "idx = " << i << " a[idx] = " << a[i] << " key = " << key << '\n';
        if (a[i] == key) {
            std::cout << "found on index = " << i << '\n';
            std::cout << "=====================================================linear search======================================================\n\n";
            return i;
        }
    }
    std::cout << "nothing was found\n";
    std::cout << "=====================================================linear search======================================================\n\n";
    return -1;
}
