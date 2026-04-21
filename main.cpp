#include <iostream>
using namespace std;

int a;

int f(int n) {
    if (n == -1) return 3;
    if (n == 0) return 2;
    return f(n - 1) + f(n - 2);
}

int main() {
    int n;
    cin >> n;
    if (n & 1) {
        cout << f(n);
        return 0;
    }
    cout << -f(n);
}
/*
3 5
1 1 1 1 1
1 0 1 0 1
1 1 1 1 1

3 5
1 1 1 0 1
1 0 1 0 1
1 0 1 0 1
*/