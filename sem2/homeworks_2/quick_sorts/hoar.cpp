#include <iostream>
using namespace std;

template<class T>
int partition(T* a, int l, int r) {
    T v = a[(l + r) / 2];
    int i = l;
    int j = r;
    bool f = true;
    while (i <= j && f) {
        while (a[i] < v) i++;
        while (a[j] > v) j--;
        if (i >= j) {
            f = false;
            continue;
        }

        T tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
        i++;
        j--;
    }
    return j;
}

template<class T>
void hoarSort(T* a, int l, int r) {
    if (l < r) {
        int q = partition(a, l, r);
        cout << "\t[ ";
        for (int i = l; i <= q; i++) cout << a[i] << ' ';
        cout << "][ ";
        for (int i = q + 1; i <= r; i++) cout << a[i] << ' ';
        cout << "]\n";
        hoarSort(a, l, q);
        hoarSort(a, q + 1, r);
    }
}