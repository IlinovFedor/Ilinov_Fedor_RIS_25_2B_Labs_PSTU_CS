#include "Salary.h"
#include <iostream>
#include <string>

std::string Salary::marshal()  {
    std::string res;
    res += "Name: " + name;
    res += "\nBase salary: " + std::to_string(baseSalary);
    res += "\nBonus percents: " + std::to_string(bonusPercents);
    res += "\nFinal salary: " + std::to_string(baseSalary * (100 + bonusPercents) / 100);
    res += '\n';
    return res;
}

Salary::Salary() {
    name = "";
    bonusPercents = 0;
    baseSalary = 0;
    std::cout << "Constructor without params:\n" << marshal() << '\n';
}

Salary::Salary(std::string N, int K, double S) {
    name = N;
    bonusPercents = K;
    baseSalary = S;
    std::cout << "Constructor with params:\n" << marshal() << '\n';
}

Salary::Salary(const Salary &t) {
    name = t.name;
    bonusPercents = t.bonusPercents;
    baseSalary = t.baseSalary;
    std::cout << "Copy constructor:\n" << marshal() << '\n';
}

Salary::~Salary() {
    std::cout << "Destructor:\n" << marshal() << '\n';
}

std::string Salary::getName() {
    return name;
}

double Salary::getBonusPercents() {
    return bonusPercents;
}

int Salary::getBaseSalary() {
    return baseSalary;
}

void Salary::setName(std::string N) {
    name = N;
}

void Salary::setBonusPercents(int K) {
    bonusPercents = K;
}

void Salary::setBaseSalary(double S) {
    baseSalary = S;
}

void Salary::show() {
    std::cout << marshal();
}
