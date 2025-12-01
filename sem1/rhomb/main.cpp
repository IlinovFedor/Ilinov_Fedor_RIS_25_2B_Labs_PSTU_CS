#include <iostream>

using namespace std;

int n;

int main() {
    cin >> n;

    for (int i = 1; i <= (n + 1) / 2; i++) {
        if (i <= (n + 1) / 2) {
            for (int j = 1; j <= (n - (2 * i - 1)) / 2; j++) {
                cout << ' ';
            }
            for (int j = 1; j <= 2 * i - 1; j++) {
                if (j == 1 || j == 2 * i - 1) cout << '*';
                else cout << ' ';
            }
            cout << '\n';
        }
    }

    for (int i = 1; i < (n + 1) / 2; i++) {
        for (int j = 1; j <= i; j++) {
            cout << ' ';
        }

        for (int j = 1; j <= n - 2 * i; j++) {
            if (j == 1 || j == n - 2 * i) cout << '*';
            else cout << ' ';
        }
        cout << '\n';
    }

}
