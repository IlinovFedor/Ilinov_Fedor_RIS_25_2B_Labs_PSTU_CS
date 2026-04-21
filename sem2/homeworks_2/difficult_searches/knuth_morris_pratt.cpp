#include <string>
#include <iostream>

void pref(const std::string &s, int *d) {
    d[0] = 0;
    int j = 0, i = 1;
    while (i < s.length()) {
        if (s[i] == s[j]) d[i++] = ++j;
        else if (!j) d[i++] = 0;
        else j = d[j - 1];
    }
    for (int i = 0; i < s.length(); i++) {
        std::cout << '\t' << (char) s[i] << ": " << d[i] << '\n';
    }
}

int knuthMorrisPratt(const std::string &s, const std::string &k) {
    std::cout << "knuth-morris-pratt\n";
    int d[k.length()];
    pref(k, d);

    int i = 0, j = 0, prev = -1;
    while (i < s.length()) {
        if (k[j] == s[i]) {
            i++;
            j++;
        }
        if (j == k.length()) {
            std::cout << "\tfound on index = " << i - (int) k.length() << '\n';
            return i - (int) k.length();
        }
        if (i < s.length() && k[j] != s[i])
            if (!j) i++;
            else j = d[j - 1];

        if (prev != i - j) {
            std::cout << '\t';
            for (int x = 0; x < i - j; x++)std::cout << ' ';
            std::cout << k << '\n';
        }
        prev = i - j;
    }
    return -1;
}
