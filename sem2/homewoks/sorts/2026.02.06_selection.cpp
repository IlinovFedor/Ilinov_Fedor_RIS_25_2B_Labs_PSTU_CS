#include <iostream>

using namespace std;

int n;

int main() {
    cin >> n;
    int a[n];
    for (int &i: a) cin >> i;

    for (int i = 0; i < n - 1; i++) {
        string s;
        getline(cin, s);
        for (int &i: a) cout << i << ' ';
        cout << '\n';
        int idx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[idx]) {
                idx = j;
            }
        }
        int tmp = a[i];
        a[i] = a[idx];
        a[idx] = tmp;
    }
    for (int &i: a) cout << i << ' ';
}

// 6 8 8 5 4 8 2
// 6 6 5 4 3 2 1
