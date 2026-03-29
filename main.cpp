#include <iostream>

using namespace std;

class base {
public:
    void print() {
        cout << "base\n";
    }
};

class dir : public base {
public:
    void print() {
        cout << "dir\n";
    }
};

int main() {
    base b;
    dir d;

    b.print();
    d.print();
}
