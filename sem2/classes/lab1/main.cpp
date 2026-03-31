#include <iostream>
#include "Pair.h"

using namespace std;

Pair makePair(int i, double d) {
    Pair p;
    p.init(d, i);
    return p;
}

int main() {
    cout << "привет\n";
    Pair f;
    f.read();
    f.show();
    cout << "a^b = " << f.power() << '\n';
    cout << "a[3] = " << f.element(3) << '\n';
    cout << "a.init(3, 2);\n";
    f.init(3, 2);
    f.show();
}