//
// Created by localuser on 4/8/26.
//

#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_Student_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_Student_H
#include <string>
#include "Person.h"

class Student : public Person {
    std::string subject;
    int grade;

public:
    Student();
    Student(std::string name, int age, std::string subject, int grade);
    Student(Person, std::string subject, int grade);
    Student(Student&);
    ~Student();
    std::string getSubject();
    void setSubject(std::string);
    int getGrade();
    void setGrade(int);
    Student &operator=(Student &p);
    friend std::ostream &operator<<(std::ostream &, Student &);
    friend std::istream &operator>>(std::istream &, Student &);
    void show();
};


#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_Student_H
