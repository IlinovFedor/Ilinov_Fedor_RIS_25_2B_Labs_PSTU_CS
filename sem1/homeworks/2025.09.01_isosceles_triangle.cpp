#include <iostream>

using namespace std;

int a;

int main() {
    cin >> a;

    for (int i = 1; i <= (a + 1) / 2; i++) {
        for (int j = 1; j <= (a - (2 * i - 1)) / 2; j++) {
            cout << ' ';
        }
        for (int j = 1; j <= (2 * i - 1); j++) {
            cout << '*';
        }
        cout << '\n';
    }
}