#include <string>
#include <iostream>

int boyerMoor(const std::string &s, const std::string &k) {
    std::cout << "boyer-moor\n";
    int table[256];
    for (auto &i: table) i = (int) k.length();
    for (int i = 0; i < (int)k.length() - 1; i++)
        table[(unsigned char) k[i]] = (int)k.length() - i - 1;

    for (int i = 0; i < 256; i++)
        if (table[i] != (int) k.length())
            std::cout << '\t' << (char) i << ": " << table[i] << '\n';
    std::cout << '\t' << "others symbols: " << k.length() << "\n\n";
    std::cout << '\t' << s << '\n';
    std::cout << '\t' << k << '\n';

    int i = (int)k.length() - 1;
    while (i < (int)s.length()) {
        int j = (int)k.length() - 1;
        while (0 <= j && k[j] == s[i - ((int)k.length() - 1 - j)])
            j--;
        if (j == -1) {
            std::cout << "\tfound on index = " << i - (int)k.length() + 1 << '\n';
            return i - (int)k.length() + 1;
        }
        int bad_char_pos = i - ((int)k.length() - 1 - j);
        i += table[(unsigned char)s[bad_char_pos]];

        std::cout << '\t';
        for (int x = 0; x < i - (int)k.length() + 1; x++) std::cout << ' ';
        std::cout << k << '\n';
    }
    return -1;
}