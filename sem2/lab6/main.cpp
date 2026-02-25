#include <iostream>

using namespace std;

string s, l[100];
int idx = -1;
int i = 0;
bool f = false;

void func() {
    for (int i = 0; i < idx + 1; i++) {
        for (int j = 0; j < idx; j++) {
            if (l[j] < l[j + 1]) {
                string tmp = l[j];
                l[j] = l[j + 1];
                l[j + 1] = tmp;
            }
        }
    }
}

int main() {
    getline(cin, s);

    while (i < s.length()) {
        if (s[i] == ' ') {
            f = false;
        }
        if (!f && '0' <= s[i] && s[i] <= '9') {
            f = true;
            idx++;
        }
        if (f)
            l[idx] += s[i];
        i++;
    }
    func();

    for (int i = 0; i < idx + 1; i++) cout << '\"' << l[i] << "\"\n";
}
