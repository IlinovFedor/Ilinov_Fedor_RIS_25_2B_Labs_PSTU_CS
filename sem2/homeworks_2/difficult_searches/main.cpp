#include <iostream>
#include "naive.cpp"

int main() {
    std::string s, k;
    std::getline(std::cin, s);
    std::getline(std::cin, k);
    std::cout << naive(s, k);
}
/*

abcaabcabcabcabcxabcaabcabcabcabcxabcaabcabcabcabcx
abcabcx

 */