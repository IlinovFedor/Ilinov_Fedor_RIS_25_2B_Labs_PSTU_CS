#include <iostream>

using namespace std;

int n, k;

char** f(char** l) {
    char** tmp = new char*[n - k];
    for (int i = 0; i < n - k; i++)
        tmp[i] = new char[100];

    for (int i = k; i < n; i++) {
        for (int j = 0; j < 100; j++) {
            tmp[i - k][j] = l[i][j];
        }
    }

    for (int i = 0; i < n; i++)
        delete[] l[i];

    delete[] l;
    return tmp;
}

int main() {
    cin >> n >> k;
    char** l = new char*[n];
    for (int i = 0; i < n; i++)
        l[i] = new char[100];

    for (int i = 0; i < n; i++) {
        cin >> l[i];
    }

    l = f(l);

    for (int i = 0; i < n - k; i++) {
        cout << l[i] << ' ';
        delete[] l[i];
    }

    delete[] l;
}