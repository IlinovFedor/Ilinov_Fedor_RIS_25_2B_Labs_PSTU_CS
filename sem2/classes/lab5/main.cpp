#include <iostream>
#include "Student.h"
#include "Vector.h"

using namespace std;

int main() {
    Person alex("Alex", 20);
    Student studentAlex(alex, "Math", 5);
    Vector v(2);
    v.add(&studentAlex);
    v.add(&alex);

    cout << v;
}
