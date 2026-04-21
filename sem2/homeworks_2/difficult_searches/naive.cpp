#include <string>
#include <iostream>

int naive(const std::string &s, const std::string &k) {
    std::cout << "naive\n";
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
            std::cout << "\tnaive\n";
            return i;
        }
    }
    std::cout << "\tnothing was found\n";
    std::cout << "\tsteps: " << cnt << '\n';
    std::cout << "naive\n";
    return -1;
}
