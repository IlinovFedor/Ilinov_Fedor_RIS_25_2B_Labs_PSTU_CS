#include <iostream>
#include "bidirectional.h"
#include "errors.h"

using namespace std;

int main() {
    try {
        BiList list(101);
    } catch (const exception &e) {
        cout << e.what() << '\n';
    }

    BiList a(3), b(2);

    try {
        cout << a[3] << '\n';
    } catch (const exception &e) {
        cout << e.what() << '\n';
    }

    try {
        BiList c = a * b;
        cout << c;
    } catch (const exception &e) {
        cout << e.what() << '\n';
    }

    try {
        Iterator it = a.begin();
        it + 10;
        cout << it.value() << '\n';
    } catch (const exception &e) {
        cout << e.what() << '\n';
    }

    return 0;
}
