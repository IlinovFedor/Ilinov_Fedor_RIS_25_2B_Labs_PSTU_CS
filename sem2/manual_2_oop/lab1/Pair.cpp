#include "Pair.h"
#include <iostream>

void Pair::init(double a, int b) {
    first = a;
    second = b;
}

void Pair::read() {
    std::cout << "First? ";
    std::cin >> first;
    std::cout << "Second? ";
    std::cin >> second;

}

void Pair::show() {
    std::cout << "First: " << first << "\nSecond: " << second << '\n';
}

double Pair::power() {
    double ans = first;
    for (int i = 1; i < second; i++) ans *= first;
    return ans;
}

double Pair::element(int a) {
    Pair tmp;
    tmp.init(second, a);
    return first * tmp.power();
}


