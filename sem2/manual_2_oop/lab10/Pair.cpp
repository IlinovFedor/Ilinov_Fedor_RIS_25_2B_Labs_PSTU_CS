#include "gpt_cal/Pair.h"
#include <fstream>
#include <iostream>

Pair::Pair() : first(0), second(0.0) {}

Pair::Pair(int f, double s) : first(f), second(s) {}

Pair::Pair(const Pair &p) : first(p.first), second(p.second) {}

Pair::~Pair() = default;

int Pair::getFirst() const {
    return first;
}

double Pair::getSecond() const {
    return second;
}

void Pair::setFirst(int f) {
    first = f;
}

void Pair::setSecond(double s) {
    second = s;
}

Pair Pair::operator-(const Pair &p) const {
    return Pair(first - p.first, second - p.second);
}

Pair Pair::operator+(int v) const {
    return Pair(first + v, second);
}

Pair Pair::operator+(double v) const {
    return Pair(first, second + v);
}

Pair &Pair::operator=(const Pair &p) {
    if (this != &p) {
        first = p.first;
        second = p.second;
    }
    return *this;
}

bool Pair::operator==(const Pair &p) const {
    return first == p.first && second == p.second;
}

bool Pair::operator!=(const Pair &p) const {
    return !(*this == p);
}

bool Pair::operator<(const Pair &p) const {
    if (first != p.first) {
        return first < p.first;
    }
    return second < p.second;
}

bool Pair::operator>(const Pair &p) const {
    return p < *this;
}

std::ostream &operator<<(std::ostream &out, const Pair &p) {
    out << p.first << ":" << p.second;
    return out;
}

std::istream &operator>>(std::istream &in, Pair &p) {
    in >> p.first >> p.second;
    return in;
}

std::fstream &operator<<(std::fstream &out, const Pair &p) {
    out << p.first << " " << p.second << "\n";
    return out;
}

std::fstream &operator>>(std::fstream &in, Pair &p) {
    in >> p.first >> p.second;
    return in;
}
