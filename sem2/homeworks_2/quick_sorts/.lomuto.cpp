#include <iostream>

using namespace std;

int partition(int a[], int l, int r) {
    int p = a[r];
    int n = l;
    for (int i = l; i < r; i++) {
        if (a[i] <= p) {
            int tmp = a[n];
            a[n] = a[i];
            a[i] = tmp;
            n++;
        }
    }
    int tmp = a[n];
    a[n] = a[r];
    a[r] = tmp;
    return n;
}

void lomutoSort(int a[], int l, int r) {
    if (r - l < 1)
        return;
    int p = partition(a, l, r);
    lomutoSort(a, l, p - 1);
    lomutoSort(a, p + 1, r);
}

int main() {
    int a[] = {56, 55, 12, 78, 42, 93, 16, 55};
    //int a[] = {3, 7, 8, 5, 2, 1, 9, 5, 4};
    lomutoSort(a, 0, 7);
    for (auto i : a) cout << i << ' ';
}