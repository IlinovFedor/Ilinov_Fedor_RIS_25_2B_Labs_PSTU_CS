#include "Pair.h"
#include <iostream>

Pair::Pair(double a, int b) {
    first = b;
    second = a;
}

Pair::Pair(const Pair &f) {
    second = f.second;
    first = f.first;
}

Pair::Pair() {
    second = 0;
    first = 0;
}

Pair::~Pair() {
    second = 0;
    first = 0;
}

double Pair::getDouble() const {
    return second;
}

void Pair::setDouble(double a) {
    second = a;
}

int Pair::getInt() const {
    return first;
}

void Pair::setInt(int a) {
    first = a;
}

Pair &Pair::operator=(Pair const &p) {
    second = p.second;
    first = p.first;
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Pair &p) {
    std::cout << p.first << " : " << p.second;
    return stream;
}

std::istream &operator>>(std::istream &stream, Pair &p) {
    std::cout << "Double? ";
    stream >> p.second;
    std::cout << "Int? ";
    stream >> p.first;
    return stream;
}

Pair Pair::operator+(Pair &p) {
    Pair second(*this);
    second.second += p.second;
    second.first += p.first;
    return second;
}

Pair Pair::operator+(int a) {
    Pair tmp(*this);
    tmp.first += a;
    return tmp;
}

Pair Pair::operator+(double a) {
    Pair tmp(*this);
    tmp.second += a;
    return tmp;
}

Pair Pair::operator*(const Pair& p) {
    double d = p.second * this->second;
    int i = p.first * this->first;
    return Pair(d, i);
}
