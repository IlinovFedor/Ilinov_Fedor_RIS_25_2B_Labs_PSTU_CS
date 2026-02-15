#include <iostream>

using namespace std;

int a;

int fib(int n) {
    if (n < 3)
        return 1;
    return fib(n - 1) + fib(n - 2);

}

int main() {
    cin >> a;
    cout << fib(a);
}