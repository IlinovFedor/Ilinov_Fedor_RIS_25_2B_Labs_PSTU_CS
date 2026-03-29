#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double a = 0.1, b = 1, k = 10, e = 0.001;
int n = 20;

double fac(int a) {
    double ans = 1;
    for (int i = 2; i <= a; i++)
        ans *= i;
    return ans;
}

double f(double x) {
    return (pow(M_E, x) - pow(M_E, -x)) / 2;
}

int main() {
    for (double x = a; x <= b; x += (b - a) / k) {
        double sn = 0, se1 = x, se2 = 0;
        for (int i = 0; i < n; i++) {
            sn += pow(x, 2 * i + 1) / fac(2 * i + 1);
        }

        int i = 1;
        while (abs(se1 - se2) >= e) {
            se2 = se1;
            se1 += pow(x, 2 * i + 1) / fac(2 * i + 1);
            i++;
        }

        cout << fixed << setprecision(6) << "X = " << x << "\tSN = " << sn << "\tSE = " << se2 << "\tY " << f(x) << '\n';
    }
}