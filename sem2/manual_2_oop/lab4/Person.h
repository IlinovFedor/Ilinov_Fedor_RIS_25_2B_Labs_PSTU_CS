//
// Created by localuser on 4/8/26.
//

#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_PERSON_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_PERSON_H
#include <string>


class Person {
    std::string name;
    int age;

public:
    Person();

    Person(std::string, int);

    Person(Person&);

    ~Person();

    const std::string getName();

    void setName(std::string);

    const  int getAge();

    void setAge(int);

    Person &operator=(Person const &p);

    friend std::ostream &operator<<(std::ostream &, const Person &);

    friend std::istream &operator>>(std::istream &, Person &);
};


#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_PERSON_H
