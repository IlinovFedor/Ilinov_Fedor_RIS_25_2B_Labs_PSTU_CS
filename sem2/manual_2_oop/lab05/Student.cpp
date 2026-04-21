//
// Created by localuser on 4/8/26.
//

#include "Student.h"

#include <iostream>

Student::Student() {
    subject = "Unknown";
    grade = 5;
}

Student::Student(std::string name, int age, std::string subject, int grade) : Person(name, age) {
    this->subject = subject;
    this->grade = grade;
}

Student::Student(Person p, std::string subject, int grade) : Person(p){
    this->subject = subject;
    this->grade = grade;
}

Student::Student(Student & p) {
    subject = p.subject;
    grade = p.grade;
}

Student::~Student() {
    subject = "Unknown";
    grade = 5;
}

std::string Student::getSubject() {
    return subject;
}

void Student::setSubject(std::string s) {
    subject = s;
}

int Student::getGrade() {
    return grade;
}

void Student::setGrade(int a) {
    grade = a;
}

Student &Student::operator=(Student &p) {
    this->setName(p.getName());
    this->setAge(p.getAge());
    subject = p.subject;
    grade = p.grade;
    return *this;
}

std::ostream &operator<<(std::ostream &stream, Student &p) {
    std::cout << p.getName() << " : " << p.getAge() << " / " << p.getSubject() << " : " << p.getGrade() << '\n';
    return stream;
}

std::istream &operator>>(std::istream &stream, Student &p) {
    std::cout << "name? ";
    std::string s;
    stream >> s;
    p.setName(s);
    std::cout << "age? ";
    int a;
    stream >> a;
    p.setAge(a);
    std::cout << "subject? ";
    stream >> p.subject;
    std::cout << "grade? ";
    stream >> p.grade;
    return stream;
}

void Student::show() {
    std::cout << *this;
}