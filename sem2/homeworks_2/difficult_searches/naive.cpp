#include <string>
#include <iostream>

int naive(const std::string &s, const std::string &k) {
    std::cout << "naive\n";
    int cnt = 0;
    for (int i = 0; i <= s.length() - k.length(); i++) {
        bool f = true;
        for (int j = i; j < i + k.length() && f; j++) {
            if (s[j] != k[j - i]) f = false;
            cnt++;
        }
        if (f) {
            std::cout << "\tsteps: " << cnt << '\n';
            std::cout << "\tfound on index = " << i << '\n';
            return i;
        }
    }
    std::cout << "\tnothing was found\n";
    std::cout << "\tsteps: " << cnt << '\n';
    return -1;
}
