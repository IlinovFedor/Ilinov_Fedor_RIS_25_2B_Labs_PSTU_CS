#include "Print.h"
#include <iostream>

Print::Print() {
    name = "Unknown";
    author = 18;
}

Print::Print(std::string s, std::string a) {
    name = s;
    author = a;
}

Print::Print(Print & p) {
    name = p.name;
    author = p.author;
}

Print::~Print() {
    name = "Unknown";
    author = 18;
}

const std::string Print::getName() {
    return name;
}

void Print::setName(std::string s) {
    name = s;
}

const std::string Print::getAuthor() {
    return author;
}

void Print::setAuthor(std::string a) {
    author = a;
}

Print &Print::operator=(Print const &p) {
    name = p.name;
    author = p.author;
    return *this;
}

void Print::show() {
    std::cout << *this;
}

void Print::input() {
    std::cin >> *this;
}

void Print::handleEvent(const Event &e) {
}

std::ostream &operator<<(std::ostream &stream, const Print &p) {
    std::cout << "Print:";
    std::cout << "\n\tName: " << p.name;
    std::cout << "\n\tAuthor: " << p.author;
    return stream;
}

std::istream &operator>>(std::istream &stream, Print &p) {
    std::cout << "Name? ";
    stream >> p.name;
    std::cout << "Author? ";
    stream >> p.author;
    return stream;
}