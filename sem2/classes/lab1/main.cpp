#include <iostream>
#include "Pair.h"

using namespace std;

int main() {
    Pair f;
    f.read();
    f.show();
    cout << "a^b = " << f.power() << '\n';
    cout << "a[3] = " << f.element(3) << '\n';
    cout << "a.init(3, 2);\n";
    f.init(3, 2);
    f.show();
}