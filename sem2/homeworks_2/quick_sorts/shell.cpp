#include <iostream>

using namespace std;

void shellSort(int a[], int n) {
    for (int step = n / 2; step > 0; step /= 2) {
        for (int i = step; i < n; i++) {
            int tmp = a[i];
            int j;
            for (j = i; j - step >= 0 && a[j - step] > tmp; j -= step)
                a[j] = a[j - step];
            a[j] = tmp;
        }
    }
}

int main() {
    int a[] = {56, 43, 12, 78, 42, 93, 16, 55};
    //int a[] = {3, 7, 8, 5, 2, 1, 9, 5, 4};
    shellSort(a, 8);
    for (auto i : a) cout << i << ' ';
}