#include <iostream>

using namespace std;

int n;

int main() {
    cin >> n;

    for (int i = 0; i < (n + 1) / 2; i++) {
        for (int j = 0; j < i; j++) {
            cout << ' ';
        }
        for (int j = 0; j < n - 2 * i; j++) {
            cout << '*';
        }
        cout << '\n';
    }
}