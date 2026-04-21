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
        cout << "\tstep = " << step << ' ';
        for (int x = 0; x < n; x++) cout << a[x] << ' ';
        cout << '\n';
    }
}
