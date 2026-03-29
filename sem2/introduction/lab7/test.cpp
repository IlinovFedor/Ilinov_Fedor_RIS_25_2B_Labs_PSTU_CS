#include <cmath>
#include <iostream>
#include <cstdarg>
using namespace std;

void func(int *, int);

int main() {
    void func(int *a, int n)
    {
        if (n < 0)
            return;
        cout << a[n] << ' ';
        func(a, n - 1);
    }
    int a[] = {1, 2, 3, 4, 5, 6};
    func(a, 6 - 1);
}
