#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

float f(float x) {
    return x - 2 + sin(1 / x);
}

float a = 1, b = 2, c = (a + b) / 2;
float e = 10e-6;

int main() {
    while (abs(a - b) > e) {
        c = (b + a) / 2;
        if (f(a) * f(c) < 0) {
            b = c;
        } else {
            a = c;
        }
    }

    cout << setprecision(7) << b;
}
