#include <iostream>
#include "Pair.h"

using namespace std;

void addConst(Pair &p, int a) {
}

int main() {
    Pair pair1;
    cout << "Pair 1?\n";
    cin >> pair1;
    cout << ++pair1;
    cout << pair1;
    Pair pair2;
    cout << "Pair 2?\n";
    cin >> pair2;
    cout << pair2;
    cout << "Sum: " << pair1 + pair2 << '\n';
    int i;
    cout << "Integer? ";
    cin >> i;
    cout << "Pair 1 + integer: " << pair1 + i;
    double d;
    cout << "Double? ";
    cin >> d;
    cout << "Pair 2 + double: " << pair2 + d;
}
