#include <iostream>

using namespace std;

int a;

int main() {
    cin >> a;
    int a[a];
    for (int &i: a) cin >> i;

    for (int i = 0; i < a / 2; i++) {
        int tmp = a[i];
        a[i] = a[a - 1 - i];
        a[a - 1 - i] = tmp;
    }
    for (int &i: a) cout << i << ' ';
    cout << '\n';
}

// 6 8 8 5 4 8 2
// 6 6 5 4 3 2 1
