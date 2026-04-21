#include <string>
#include <iostream>

int boyerMoor(const std::string &s, const std::string &k) {
    std::cout << "boyer-moor\n";
    int cnt = 0;
    for (int i = 0; i < s.size() - k.size(); i++) {
        bool f = true;
        for (int j = i; j < i + k.size() && f; j++) {
            if (s[j] != k[j - i]) f = false;
            cnt++;
        }
        if (f) {
            std::cout << "\tfound on index = " << i << '\n';
            std::cout << "\tsteps: " << cnt << '\n';
            std::cout << "\tboyer-moor\n";
            return i;
        }
    }
    std::cout << "\tnothing was found\n";
    std::cout << "\tsteps: " << cnt << '\n';
    std::cout << "boyer-moor\n";
    return -1;
}
