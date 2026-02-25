#include <iostream>

using namespace std;

int n;

int main() {
    cin >> n;
    int a[n];
    for (int &i: a) cin >> i;

    for (int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        for (int &i: a) cout << i << ' ';
        cout << '\n';
        for (int j = 0; j < n - 1; j++) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

// 6 8 8 5 4 8 2
// 6 6 5 4 3 2 1
