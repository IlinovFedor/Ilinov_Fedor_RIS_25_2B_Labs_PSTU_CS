#include <iostream>

using namespace std;

const int tableSize = 8;
bool m[tableSize][tableSize];
int attempt = 0;

void print() {
    for (int i = 0; i < tableSize; i++) {
        for (int j = 0; j < tableSize; j++) {
            cout << (m[i][j] ? "Q " : ". ");
        }
        cout << '\n';
    }
}

bool isOk(int r, int c) {
    for (int i = 0; i < r; i++)
        if (m[i][c])
            return false;

    for (int i = 1; r - i >= 0 && c - i >= 0; i++)
        if (m[r - i][c - i])
            return false;

    for (int i = 1; r - i >= 0 && c + i < tableSize; i++)
        if (m[r - i][c + i])
            return false;

    return true;
}

void f(int r) {
    print();
    string(s);
    getline(cin, s);
    if (r == tableSize || attempt > 0) {
        cout << "Solution " << ++attempt << "\n\n";
        cout << '\n';
        exit(0);
    } else {
        for (int i = 0; i < tableSize; i++) {
            if (isOk(r, i)) {
                m[r][i] = true;
                f(r + 1);
                m[r][i] = false;
            }
        }
    }
    return;
}

int main() {
    f(0);
}
