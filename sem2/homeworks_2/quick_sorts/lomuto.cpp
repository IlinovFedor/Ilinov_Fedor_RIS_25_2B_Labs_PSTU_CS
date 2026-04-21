#include <iostream>

using namespace std;

int partition(int a[], int l, int r) {
    int i = l;
    int j = r;
    while (i < j) {
        if (a[i] > a[j]) {
            int tmp = a[j];
            a[j] = a[i];
            a[i] = a[j - 1];
            a[j - 1] = tmp;
            j--;
            i--;
        }
        i++;
    }
    return j;
}

void lomutoSort(int a[], int l, int r) {
    if (r - l > 0) {
        int p = partition(a, l, r);
        cout << "\t[ ";
        for (int i = l; i <= p; i++) cout << a[i] << ' ';
        cout << "][ ";
        for (int i = p + 1; i <= r; i++) cout << a[i] << ' ';
        cout << "]\n";
        lomutoSort(a, l, p - 1);
        lomutoSort(a, p + 1, r);
    }
}