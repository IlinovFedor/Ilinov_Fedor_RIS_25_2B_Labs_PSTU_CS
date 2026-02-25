#include <iostream>

using namespace std;

int main() {
    int a;
    cin >> a;
    switch (a) {
        case 1:
            cout << "first\n";
            break;
        case 2:
            cout << "second\n";
        case 3:
            cout << "third\n";
        default:
            cout << "default\n";
    }
}