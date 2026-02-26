#include <fstream>
#include <iostream>

using namespace std;

ifstream in("in.txt");

struct Student {
    string name;
    string surname;
    string middleName;
    string phoneNumber;
    int group{};
    int grades[3]{};
    double getAvgGrades();
    void print();
};

double Student::getAvgGrades() {
    return (grades[0] + grades[1] + grades[2]) / 3.0;
}

void Student::print() {
    cout << surname << ' ' << name << ' ' << middleName << '\n';
    cout << phoneNumber << '\n';
    cout << group << '\n';
    cout << grades[0] << ' ' << grades[1] << ' ' << grades[2] << ' ' << this->getAvgGrades() << '\n';
    cout << '\n';
}

int grade, group, n;
string surname;
string s;
Student student;

int main() {
    in >> n >> grade >> group >> surname;

    for (int i = 0; i < n + 1; i++) {
        Student tmp;
        in >> tmp.surname >> tmp.name >> tmp.middleName;
        in >> tmp.phoneNumber;
        in >> tmp.group;
        in >> tmp.grades[0] >> tmp.grades[1] >> tmp.grades[2];
        if (i == 0) student = tmp;
        bool f = true;
        if (i == 0)
            f = false;
        if (tmp.getAvgGrades() < grade
            && tmp.group == group)
            f = false;
        if (f)
            tmp.print();

        if (tmp.surname == surname) student.print();
    }
}