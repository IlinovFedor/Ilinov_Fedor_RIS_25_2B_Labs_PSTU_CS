#include <fstream>
#include <iostream>

using namespace std;

ifstream f1("F1");
ofstream f2("F2");
string str;

string ans = "";
int ansCnt;

int main() {
    while (getline(f1, str)) {
        string word;
        string words[1000];
        int amounts[1000] = {};
        int cntA = 0;

        int cnt = 0;
        for (int i = 0; i < str.size(); i++) {
            if (!(32 <= str[i] && str[i] <= 64)) {
                word += str[i];
                if (int(str[i]) == -48 && (int(str[i + 1]) == -112 || int(str[i + 1]) == -80))
                    cntA++;
            }
            else if (!word.empty()) {
                if (cntA > ansCnt) {
                    ansCnt = cntA;
                    ans = word;
                    cout << word << "A\n";
                }
                words[cnt] = word;
                cnt++;
                word = "";
                cntA = 0;
            }
        }

        for (int i = 0; i < cnt; i++) {
            amounts[i] = 1;
            for (int j = i + 1; j < cnt; j++) {
                if (i != j && !words[i].empty() && words[i] == words[j]) {
                    amounts[i]++;
                    words[j] = "";
                }
            }
        }

        bool f = true;
        for (int i = 0; i < cnt && f; i++) {
            if (amounts[i] == 2) {
                f2 << str << '\n';
                f = false;
            }
        }
    }
    f2 << '\n' << ans;
}