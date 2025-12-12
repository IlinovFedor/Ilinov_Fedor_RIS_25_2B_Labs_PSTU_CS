#include <iostream>
#include <cmath>
#include <iomanip>
#include "timer.h"

using namespace std;

double f(double x) {
    return x - 2 + sin(1 / x);
}

double a = 1, b = 2, c = (a + b) / 2;
double eps = 10e-15;
int i = 1;

int main() {
    TIMER(
    while (abs(a - b) > eps) {
        c = (b + a) / 2;
        if (f(a) * f(c) < 0) {
            b = c;
        } else {
            a = c;
        }
        cout << fixed << setprecision(4) << "Step: " << i
        << " Value: " << b << '\n';
        i++;
    }

    cout << fixed << setprecision(4) << b << '\n';
    )
}
