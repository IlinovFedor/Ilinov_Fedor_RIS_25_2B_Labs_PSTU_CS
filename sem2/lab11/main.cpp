#include <iostream>
#include "bidirectional.cpp"
#include "unidirectional.cpp"

using namespace std;

int main() {
    BiList list;

    for (int i = 0; i < 5; i++) {
        char* s = new char[STRING_SIZE];
        cin >> s;
        list.pushFront(s);
    }
    list.print();

    char* s = new char[STRING_SIZE];
    cin >> s;
    list.insert(2, s);
    s = new char[STRING_SIZE];
    cin >> s;
    list.insert(2, s);
    list.print();
    list.clear();
    list.remove(5);
    list.print();
    auto tmp = new char[STRING_SIZE];
    tmp[0] = 'a';
    cout << list.find(tmp) << '\n';
    cout << list.get(1) << '\n';
    list.print();
}