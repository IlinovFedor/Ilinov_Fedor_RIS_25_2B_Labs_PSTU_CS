#include <iostream>

using namespace std;

int n;

void slow(int n) {
    for (int i = 1; i <= n; i++) {
        cout << "* ";
    }
    cout << '\n';
    for (int i = 1; i <= n - 2; i++) {
        cout << "* ";
        for (int j = 1; j <= n - 2; j++) {
            cout << "  ";
        }
        cout << "* \n";
    }
    for (int i = 1; i <= n; i++) {
        cout << "* ";
    }
    cout << '\n';
}

void fast(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j == 1 || j == n || i == 1 || i == n) {
                cout << "* ";
            } else {
                cout << "  ";
            }
        }
        cout << '\n';
    }
    cout << '\n';
}

int main() {
    cin >> n;
    slow(n);
    fast(n);
}
