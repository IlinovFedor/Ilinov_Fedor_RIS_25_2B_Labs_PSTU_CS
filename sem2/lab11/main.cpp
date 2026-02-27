#include <fstream>
#include <iostream>
#include "bidirectional.cpp"
#include "unidirectional.cpp"

using namespace std;

int n, m, k;

int main() {
    UniList list;
    cout << "Size:\n";
    cin >> n;
    for (int i = 0; i < n; i++) {
        char* s = new char[STRING_SIZE];
        cin >> s;
        list.pushBack(s);
    }
    list.print(cout);

    cout << "Delete:\n";
    cin >> m;
    list.remove(m - 1);
    list.print(cout);
    cout << "Key:\n";
    char* key = new char[STRING_SIZE];
    cin >> key;
    int idx = list.find(key);
    cout << "Index: " << idx << '\n';
    cout << "Amount:\n";
    cin >> k;


    cout << "First " << k << " words:\n";
    for (int i = 0; i < k; i++) {
        char* s = new char[STRING_SIZE];
        cin >> s;
        list.insert(idx, s);
        idx++;
        list.print(cout);
    }

    idx++;
    cout << "Second " << k << " words:\n";
    for (int i = 0; i < k; i++) {
        char* s = new char[STRING_SIZE];
        cin >> s;
        list.insert(idx, s);
        idx++;
        list.print(cout);
    }

    fstream file("file.txt", ios::in | ios::out);
    list.print(file);
    file.seekp(0);

    list.clear();
    list.print(cout);
    for (int i = 0; i < n - 1 + 2 * k; i++) {
        char* s = new char[STRING_SIZE];
        file >> s;
        list.pushBack(s);
    }
    file.close();
    list.print(cout);
}