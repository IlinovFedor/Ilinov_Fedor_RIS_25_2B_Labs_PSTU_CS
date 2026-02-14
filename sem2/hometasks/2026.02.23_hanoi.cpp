#include <iostream>

using namespace std;

int sizes[3];
int towers[3][65];
int height, maxWidth;
int centerFirst, centerSecond, centerThird;
string s;

void replace(int x, int y) {
    towers[y][sizes[y]] = towers[x][sizes[x] - 1];
    sizes[y]++;
    towers[x][sizes[x] - 1] = 0;
    sizes[x]--;
}

bool isGood(int x, int y) {
    bool isY = false, isX = false;
    bool f1 = towers[0][y] != 0;
    bool f2 = towers[1][y] != 0;
    bool f3 =  towers[2][y] != 0;
    if (f1 || f2 || f3)
        isY = true;

    f1 = centerFirst - towers[0][y] < x && x < centerFirst + towers[0][y];
    f2 = centerSecond - towers[1][y] < x && x < centerSecond + towers[1][y];
    f3 = centerThird - towers[2][y] < x && x < centerThird + towers[2][y];
    if (f1 || f2 || f3)
        isX = true;

    return isY && isX;
}

void print() {
    getline(cin, s);

    static int step = 0;
    cout << "Step: " << step << '\n';
    step++;

    for (int i = 0; i < height + 1; i++) {
        for (int j = 0; j < 3 * (maxWidth + 1); j++) {
            int y = height - i, x = j;
            bool f1 = j == centerFirst;
            bool f2 =  j == centerSecond;
            bool f3 =  j == centerThird;

            if (isGood(x, y)) cout << '#';
            else if (f1 || f2 || f3) cout << '|';
            else cout << ' ';
        }
        cout << '\n';
    }
}

void hanoi(int n, int from, int to, int tmp) {
    if (n > 0) {
        hanoi(n - 1, from, tmp, to);
        replace(from, to);
        print();
        hanoi(n - 1, tmp, to, from);
    }
    return;
}

int main() {
    cout << "Size: ";
    cin >> sizes[0];
    for (int i = 0; i < sizes[0]; i++)
        towers[0][i] = sizes[0] - i;

    height = sizes[0];
    maxWidth = 2 * height - 1;
    centerFirst = maxWidth / 2;
    centerSecond = maxWidth + maxWidth / 2 + 1;
    centerThird = 2 * maxWidth + maxWidth / 2 + 2;

    print();
    hanoi(height, 0, 2, 1);
}
