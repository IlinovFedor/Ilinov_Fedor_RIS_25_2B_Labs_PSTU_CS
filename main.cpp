#include <fstream>
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

ofstream f("test.txt");

int main() {
    f << 1;
    for (int i = 0; i < 4094; i++) f << '\n';
    f << 1;
}

