#include <iostream>

template<typename T>
int binary(const T a[], const int &n, const T &key) {
    std::cout <<
            "========================================================binary==========================================================\n";
    int l = 0, r = n - 1, m = (l + r) / 2;
    std::cout << "left = " << l << " mid = " << m << " right = " << r << " key = " << key << '\n';

    while (l <= r) {
        if (key < a[m]) {
            r = m - 1;
            m = (l + r) / 2;
            std::cout << "key < a[m], so " << "left = " << l << " mid = " << m << " right = " << r << " key = " << key <<
                    '\n';
        } else if (key > a[m]) {
            l = m + 1;
            m = (l + r) / 2;
            std::cout << "key > a[m], so " << "left = " << l << " mid = " << m << " right = " << r << " key = " << key <<
                    '\n';
        } else {
            std::cout << "found on index = " << m << '\n';
            std::cout <<
                    "========================================================binary==========================================================\n\n";
            return m;
        }
    }

    std::cout << "nothing was found\n";
    std::cout <<
            "========================================================binary==========================================================\n\n";
    return -1;
}
