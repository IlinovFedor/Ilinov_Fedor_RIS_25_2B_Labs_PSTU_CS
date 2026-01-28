#include <iostream>

using namespace std;

int n;

int main() {
    cin >> n;
    int a[n];
    for (int &i: a) cin >> i;

    for (int i = 0; i < n / 2; i++) {
        int tmp = a[i];
        a[i] = a[n - 1 - i];
        a[n - 1 - i] = tmp;
    }
    for (int &i: a) cout << i << ' ';
    cout << '\n';
}

// 6 8 8 5 4 8 2
// 6 6 5 4 3 2 1
