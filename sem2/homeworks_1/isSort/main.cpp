#include <iostream>

using namespace std;

int n;

int main() {
    cin >> n;
    int a[n];
    for (int &i: a) cin >> i;

    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            cout << "Doesn't sorted";
            return 0;
        }
    }
    cout << "Sorted";
}

// 6 8 8 5 4 8 2
// 6 6 5 4 3 2 1
