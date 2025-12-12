#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double a = 1, b = 2;
double x0 = (a + b) / 2, x1;
double eps = 10e-7;
int i = 1;

double f(double x) {
    return x - 2 + sin(1 / x);
}

double pr(double x) {
    return 1 - cos(1 / x) / (x * x);
}

int main() {
    x1 = x0 - f(x0) / pr(x0);

    while (abs(x0 - x1) > eps) {
        x0 = x1;
        x1 = x0 - f(x0) / pr(x0);
        cout << fixed << setprecision(6) << "Step: " << i << " Value: " << x1 << '\n';
        i++;
    }

    cout << fixed << setprecision(6) << x1 << endl;
}
