#include <iostream>
#include <fstream>
using namespace std;

ifstream f1("F1");
ofstream f2("F2");
string ans;
int ansCnt = 0;

string words[1000];
int amounts[1000];
int cnt;

int countA(string& word) {
    int cntA = 0;
    for (int i = 0; i < word.size(); i++) {
        if (int(word[i]) == -48 && (int(word[i + 1]) == -112 || int(word[i + 1]) == -80))
            cntA++;
    }
    return cntA;
}

void saveWord(string& word, int cntA) {
    if (cntA > ansCnt) {
        ansCnt = cntA;
        ans = word;
    }
    words[cnt] = word;
    cnt++;
    word = "";
}

void parseLine(string& str) {
    cnt = 0;
    string word;

    for (int i = 0; i < str.size(); i++) {
        if (!(32 <= str[i] && str[i] <= 64)) {
            word += str[i];
        } else if (!word.empty()) {
            saveWord(word, countA(word));
        }
    }
    if (!word.empty())
        saveWord(word, countA(word));
}

void countAmounts() {
    for (int i = 0; i < cnt; i++) {
        amounts[i] = 1;
        for (int j = i + 1; j < cnt; j++) {
            if (!words[i].empty() && words[i] == words[j]) {
                amounts[i]++;
                words[j] = "";
            }
        }
    }
}

bool hasWordTwice() {
    for (int i = 0; i < cnt; i++)
        if (amounts[i] == 2) return true;
    return false;
}

int main() {
    string str;
    while (getline(f1, str)) {
        parseLine(str);
        countAmounts();
        if (hasWordTwice())
            f2 << str << '\n';
    }
    f2 << '\n' << ans;
}