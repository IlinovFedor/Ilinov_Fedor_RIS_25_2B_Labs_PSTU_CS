#include <iostream>

using namespace std;

int main() {
    int n, idx = 0, cnt = 1;
    cin >> n;
    int a[n];
    for (int &i: a) cin >> i;

    int val = a[0];

    for (int i = 1; i < n; i++) {
        if (a[i] > val) {
            val = a[i];
            cnt = 1;
            idx = i;
        } else if (a[i] == val) {
            cnt++;
        }
    }

    cout << "max: " << val;
    cout << "\npos: " << idx + 1;
    cout << "\ncnt: " << cnt;
}

// 6 8 8 5 4 8 2
// 6 6 5 4 3 2 1
