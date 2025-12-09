#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

float a = 1, b = 3;
float lambda = 2.0 / (-9 - 6);
float eps = 10e-7;

float phi(float x) {
    return x - lambda * (pow(x, 3) - 6 * pow(x, 2) + 3 * x + 11);
}

int main() {
    float x0 = (a + b) / 2;
    float x1 = phi(x0);

    while (abs(x0 - x1) > eps) {
        x0 = x1;
        x1 = phi(x0);
    }

    cout << fixed << setprecision(6) << x1 << endl;
}
