#include <iostream>
#include <cmath>
#include <iomanip>
#include "timer.h"

using namespace std;

double a = 1, b = 2;
double lambda = 2 / (1 - cos(1) + 1 - cos(1 / 2) / 4);
double eps = 10e-15;
int i = 1;

double phi(double x) {
    return x - lambda * (x - 2 + sin(1 / x));
}

int main() {
    TIMER(
        double x0 = (a + b) / 2;
        double x1 = phi(x0);

        while (abs(x0 - x1) > eps) {
            x0 = x1;
            x1 = phi(x0);
            cout << fixed << setprecision(4) << "Step: " << i << " Value: " << x1 << '\n';
            i++;
        }

        cout << fixed << setprecision(4) << x1 << '\n';
    )
}
