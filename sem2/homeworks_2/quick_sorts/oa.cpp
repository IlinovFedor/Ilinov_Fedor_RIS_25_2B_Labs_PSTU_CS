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

void quickSort(int a[], int l, int r) {
    if (r - l > 0) {
        int p = partition(a, l, r);
        quickSort(a, l, p - 1);
        quickSort(a, p + 1, r);
    }
}

int main() {
    int a[] = {56, 55, 12, 78, 42, 93, 16, 55};
    //int a[] = {3, 7, 8, 5, 2, 1, 9, 5, 4};
    quickSort(a, 0, 7);
    for (auto i : a) cout << i << ' ';

}