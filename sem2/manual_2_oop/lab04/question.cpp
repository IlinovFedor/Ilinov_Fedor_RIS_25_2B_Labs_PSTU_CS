#include <string>
class Student {
    int age;

public:
    std::string name;

    Student() {
        age = 0;
        name = "";
    }

    Student(int a, const std::string &n) {
        age = a;
        name = n;
    }

    Student(const Student &s) {
        age = s.age;
        name = s.name;
    }

    Student &operator=(const Student &other) {
        if (this != &other) {
            age = other.age;
            name = other.name;
        }
        return *this;
    }
};

class Employee : public Student {
protected:
    std::string post;

public:
    Employee() : Student() {
        post = "";
    }

    Employee(int a, const std::string &n, const std::string &p) : Student(a, n) {
        post = p;
    }

    Employee(const Employee &e) : Student(e) {
        post = e.post;
    }

    Employee &operator=(const Employee &e) {
        if (this != &e) {
            Student::operator=(e);
            post = e.post;
        }
        return *this;
    }
};

class Teacher : public Employee {
protected:
    int stage;

public:
    Teacher() : Employee() {
        stage = 0;
    }

    Teacher(int a, const std::string &n, const std::string &p, int s)
        : Employee(a, n, p) {
        stage = s;
    }

    Teacher(const Teacher &t) : Employee(t) {
        stage = t.stage;
    }

    Teacher &operator=(const Teacher &t) {
        if (this != &t) {
            Employee::operator=(t);
            stage = t.stage;
        }
        return *this;
    }
};
