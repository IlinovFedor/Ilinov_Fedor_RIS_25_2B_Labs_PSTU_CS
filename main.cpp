#include <iostream>

using namespace std;

struct Bar {
    int  b;   // 4
    char a;   // 1
    char c;   // 1
};


struct Foo {
    char a;   // 1
    int  b;   // 4
    char c;   // 1
};

int main() {
    cout << "sizeof(Bar): " << sizeof(Bar);
    cout << "\nsizeof(Foo): " << sizeof(Foo);
}

