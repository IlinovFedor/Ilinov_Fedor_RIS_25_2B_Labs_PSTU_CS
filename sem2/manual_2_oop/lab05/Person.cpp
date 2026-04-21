//
// Created by localuser on 4/8/26.
//

#include "Person.h"

#include <iostream>

Person::Person() {
    name = "Unknown";
    age = 18;
}

Person::Person(std::string s, int a) {
    name = s;
    age = a;
}

Person::Person(Person & p) {
    name = p.name;
    age = p.age;
}

Person::~Person() {
    name = "Unknown";
    age = 18;
}

const std::string Person::getName() {
    return name;
}

void Person::setName(std::string s) {
    name = s;
}

const int Person::getAge() {
    return age;
}

void Person::setAge(int a) {
    age = a;
}

Person &Person::operator=(Person const &p) {
    name = p.name;
    age = p.age;
    return *this;
}

void Person::show() {
    std::cout << *this;
}

std::ostream &operator<<(std::ostream &stream, const Person &p) {
    std::cout << p.name << " : " << p.age << '\n';
    return stream;
}

std::istream &operator>>(std::istream &stream, Person &p) {
    std::cout << "Name? ";
    stream >> p.name;
    std::cout << "Age? ";
    stream >> p.age;
    return stream;
}