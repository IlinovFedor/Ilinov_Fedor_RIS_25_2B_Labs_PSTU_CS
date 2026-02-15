#include <iostream>

using namespace std;

int a, s = 0, p = 0;

int main() {
    cin >> a;

    for (int i = 1; i <= a; i++) {
        p = 1;
        for (int j = i; j <= 2 * i; j++) {
            p *= j;
        }
        s += p;
    }

    cout << s;
}