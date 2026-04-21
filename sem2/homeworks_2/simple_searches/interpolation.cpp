#include <iostream>

template<typename T>
int interpolation(const T a[], const int &n, const T &key) {
    std::cout <<
            "=====================================================interpolation=======================================================\n";

    int l = 0;
    int r = n - 1;

    while (l <= r && key >= a[l] && key <= a[r]) {
        if (a[l] == a[r]) {
            if (a[l] == key) return l;
            return -1;
        }

        int m = l + (double) (r - l) * (key - a[l]) / (a[r] - a[l]);

        std::cout << "l = " << l << " m = " << m << " r = " << r << "\n";

        if (a[m] == key) {
            std::cout << "found at index = " << m << "\n";
            std::cout <<
                    "=====================================================interpolation=======================================================\n\n";
            return m;
        }

        if (a[m] < key)
            l = m + 1;
        else
            r = m - 1;
    }

    std::cout << "not found\n";
    std::cout <<
            "=====================================================interpolation=======================================================\n\n";
    return -1;
}
