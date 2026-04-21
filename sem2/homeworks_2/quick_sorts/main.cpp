#include <iostream>
#include "hoar.cpp"
#include "lomuto.cpp"
#include "shell.cpp"


int main() {
    int n;
    std::cin >> n;
    int a[n], h[n], l[n], s[n];
    for (auto &i: a) std::cin >> i;
    std::copy(a, a + n, h);
    std::copy(a, a + n, l);
    std::copy(a, a + n, s);

    cout << "hoar sort\n";
    hoarSort(h, 0, n - 1);
    cout << '\t';
    for (auto &i: h) std::cout << i << ' ';
    std::cout << '\n';

    cout << "lomuto sort\n";
    lomutoSort(l, 0, n - 1);
    cout << '\t';
    for (auto &i: l) std::cout << i << ' ';
    std::cout << '\n';

    cout << "shell sort\n";
    shellSort(s, n);
    cout << '\t';
    for (auto &i: s) std::cout << i << ' ';
    std::cout << '\n';
}
