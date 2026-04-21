#include <iostream>

using namespace std;

int a, sm;

int fib(int n) {
    if (n < 3)
        return 1;
    return fib(n - 1) + fib(n - 2);
}

int main() {
    cin >> a;
    cout << fib(a);

    for (int i = 1; i <= a; i++) {
        sm += fib(i);
    }

    cout << '\n' << sm;
}