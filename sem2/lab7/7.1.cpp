#include <iostream>

using namespace std;

void print(int size, int* a) {
    for (int i = 0; i < size; i++) {
        cout << a[i] << ' ';
    }
    cout << "\n\n";
}

void print(int rows, int cols, int** a) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void func(int& rows, int** a) {
    int tmp = 0;

    for (int i = 0; i < rows; i++) {
        if (i & 1) {
            delete[] a[i];
            a[i] = nullptr;
        } else {
            a[tmp] = a[i];
            tmp++;
        }
    }

    rows = tmp;
}

void func(int& n, int* l) {
    int a, b;
    bool f = true;
    for (int i = 0; i < n; i++) {
        if (l[i] == 0 && f) {
            a = i;
            f = false;
        } else if (l[i] == 0) {
            b = i;
        }
    }

    int pos = a + 1;
    for (int i = b; i < n; i++) {
        l[pos] = l[i];
        pos++;
    }
    n = n - (b - a - 1);
}

int main() {
    srand(time(NULL));
    int size = 10, rows = 5, cols = 5;


    int* a = new int[size];
    for (int i = 0; i < size; i++)
        cin >> a[i];

    int** m = new int*[rows];
    for (int i = 0; i < rows; i++) {
        m[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m[i][j] = rand() % 10;
        }
    }


    print(size, a);
    func(size, a);
    print(size, a);

    print(rows, cols, m);
    func(rows, m);
    print(rows, cols, m);

    for (int i = 0; i < rows; i++) {
        delete[] m[i];
        m[i] = nullptr;
    }
    delete[] a;
}