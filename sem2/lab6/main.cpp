#include <iostream>

using namespace std;

string s, l[100];
string tmp;
int i;
int n;
char c;

void sort() {
    for (int i = 0; i < n - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < n; j++) {
            if (l[j] > l[idx]) {
                idx = j;
            }
        }
        string tmp = l[i];
        l[i] = l[idx];
        l[idx] = tmp;
    }
}

int main() {
    getline(cin, s);

    while (i < s.size()) {
        c = s[i];
        bool f = '0' <= c && c <= '9';
        if (f) {
            while (i != s.size() && c != ' ') {
                tmp += c;
                i++;
                c = s[i];
            }
            l[n] = tmp;
            n++;
            tmp = "";
        }
        i++;
    }
    sort();

    for (i = 0; i < n; i++) cout << l[i] << ' ';
}