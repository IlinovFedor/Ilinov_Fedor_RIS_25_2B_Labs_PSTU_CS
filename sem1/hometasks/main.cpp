#include <iostream>

using namespace std;

int n, s = 0, p = 0;

int main() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        p = 1;
        for (int j = i; j <= 2 * i; j++) {
            p *= j;
        }
        s += p;
    }

    cout << s;
}