#include <iostream>
#include "naive.cpp"
#include "boyer_moor.cpp"
#include "knuth_morris_pratt.cpp"

int main() {
    std::string s, k;
    std::getline(std::cin, s);
    std::getline(std::cin, k);

    naive(s, k);
    boyerMoor(s, k);
    knuthMorrisPratt(s, k);
}
/*
abcafdfabcabd
abcabd

ABC ABCDAB ABCDABCDABDE
ABCDABD

abcaabcabcabcabcxabcaabcabcabcabcxabcaabcabcabcabcx
abcabcx
 */