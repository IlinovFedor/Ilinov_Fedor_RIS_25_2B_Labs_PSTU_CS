#include <iostream>
#include "Student.h"
#include "Vector.h"

using namespace std;

void f1(Person &p) {
    p.setName("John");
}

void test(Object *o) {
    o->show();
}

int main() {
    Person person("Alex", 20);
    Student student(person, "Math", 5);
    f1(student);
    person.show();
    student.show();
    student.setGrade(2);
    Vector v(100);
    v.Add(&student);
    v.Add(&person);
    cout << v;
}

