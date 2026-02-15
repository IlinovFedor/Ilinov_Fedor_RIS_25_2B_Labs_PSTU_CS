#include <iostream>

using namespace std;

/*
3 4 5 6 7 8 1 2 3 4 9 10 11 12 2 6 10 1 5 9 3 7 11 4 8 12
1	2	3	4
5	6	7	8
9	10	11	12
*/

int rows, cols;

int main() {
    cin >> rows >> cols;
    int l[2 * rows * cols];
    int m[rows][cols];
    for (int& i : l) cin >> i;

    for (int i = 0; i < rows * cols; i += cols) {
        int j = rows * cols;
        while (l[i] != l[j]) {
            j++;
        }
        int pos = (j - rows * cols) % rows;
        for (int j = i; j < i + cols; j++) {
            m[pos][j - i] = l[j];
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << m[i][j] << '\t';
        }
        cout << '\n';
    }
}