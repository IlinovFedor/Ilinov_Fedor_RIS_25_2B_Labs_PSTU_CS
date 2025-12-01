#include <iostream>

using namespace std;

int n;

int main() {
    cin >> n;

    for (int i = 1; i <= (n + 1) / 2; i++) {
        for (int j = 1; j <= (n - (2 * i - 1)) / 2; j++) {
            cout << ' ';
        }
        for (int j = 1; j <= (2 * i - 1); j++) {
            cout << '*';
        }
        cout << '\n';
    }
}