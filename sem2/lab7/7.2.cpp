#include <cmath>
#include <iostream>
#include <cstdarg>

using namespace std;


double dist(int n, ...) {
    va_list args;
    double a[100][2];

    va_start(args, n);
    for (int i = 0; i < n; i++) {
        a[i][0] =  va_arg(args, double);
        a[i][1] =  va_arg(args, double);
    }
    va_end(args);

    double ans = sqrt(pow(a[0][0] - a[n - 1][0], 2)
        + pow(a[0][1] - a[n - 1][1], 2));
    for (int i = 0; i < n - 1; i++) {
        double tmp = sqrt(pow(a[i][0] - a[i + 1][0], 2)
            + pow(a[i][1] - a[i + 1][1], 2));
        if (ans < tmp) {
            ans = tmp;
        }
    }

    return ans;
}

double square(int n, ...) {
    va_list args;
    double a[3][2];

    va_start(args, n);
    for (int i = 0; i < n; i++) {
        a[i][0] =  va_arg(args, double);
        a[i][1] =  va_arg(args, double);
    }
    va_end(args);

    return abs((a[0][0] - a[2][0]) * (a[1][1] - a[2][1])
        - (a[0][1] - a[2][1]) * (a[1][0] - a[2][0])) / 2.0;
}

double square1(int n, ...) {
    va_list args;
    double a[100][2];

    va_start(args, n);
    for (int i = 0; i < n; i++) {
        a[i][0] =  va_arg(args, double);
        a[i][1] =  va_arg(args, double);
    }
    va_end(args);

    double maxDiagonal = -1;
    int p1 = 0, p2 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double tmp = dist(2, a[i][0], a[i][1], a[j][0], a[j][1]);
            if (tmp > maxDiagonal) {
                maxDiagonal = tmp;
                p1 = i;
                p2 = j;
            }
        }
    }

    double maxSquare = -1;
    for (int i = 0; i < n; i++) {
        double tmp = square(3, a[p1][0], a[p1][1], a[p2][0], a[p2][1], a[i][0], a[i][1]);
        if (maxSquare < tmp)
            maxSquare = tmp;
    }

    return maxSquare;
}



int main() {
    cout << square1(5,
        0.5, 2.0,
        1.25, 3.0,
        2.5, 2.5,
        2.5, 1.5,
        1.0, 1.0) << endl;
}

    // cout << square(3,
    //     2.5, 2.5,
    //     0.5, 2.0,
    //     2.5, 1.5) << endl;
    // cout << dist(5,
    //     0.5, 2.0,
    //     1.25, 3.0,
    //     2.5, 2.5,
    //     2.5, 1.5,
    //     1.0, 1.0) << endl;
/*
*cout << square(3, 2.5, 2.5, 0.5, 2, 2.5, 1.5) << endl;
    cout << square1(5, 0.5, 2.0, 1.25, 3.0, 2.5, 2.5, 2.5, 1.5, 1.0, 1.0);
/*
(4.1,5.5)
(2.8,2.4)
(3.4,8.3)
(1,4.1)
(7.5,2.1)
*/