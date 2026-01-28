#include <iostream>

using namespace std;

int n;

int main() {
    cin >> n;
    int a[n];
    for (int &i: a) cin >> i;

    for (int i = 1; i < n; i++) {
        int tmp = a[i];
        for (int j = i - 1; j >= 0; j--) {
            if (a[j] > tmp) {
                a[j + 1] = a[j];
                a[j] = tmp;
            }
        }
    }

    for (int &i: a) cout << i << ' ';
}

// 6 8 8 5 4 8 2
// 6 6 5 4 3 2 1
