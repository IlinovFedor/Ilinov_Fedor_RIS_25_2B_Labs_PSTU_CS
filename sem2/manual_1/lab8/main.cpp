#include <fstream>
#include <iostream>

using namespace std;


struct Student {
    string name;
    string surname;
    string middleName;
    string phoneNumber;
    int group;
    int grades[3];
    double getAvgGrades();
    void print(ostream&);
    void read(istream&);
};

double Student::getAvgGrades() {
    return (grades[0] + grades[1] + grades[2]) / 3.0;
}

void Student::print(ostream& stream) {
    stream << surname << ' ' << name << ' ' << middleName << '\n';
    stream << phoneNumber << '\n';
    stream << group << '\n';
    stream << grades[0] << ' ' << grades[1] << ' ' << grades[2] << '\n';
    stream << '\n';
}

void Student::read(istream & stream) {
    stream >> surname >> name >> middleName;
    stream >> phoneNumber;
    stream >> group;
    stream >> grades[0] >> grades[1] >> grades[2];
}

fstream file("file.txt", ios::in);
int grade, group;
string surname;
string s;
Student newStudent;
Student students[256];
int cnt = 0;

int main() {
    cin >> grade >> group >> surname;
    newStudent.read(cin);

    while (!file.eof()) {
        Student tmp;
        tmp.read(file);
        bool f = true;
        if (tmp.getAvgGrades() < grade
            && tmp.group == group)
            f = false;
        if (f) {
            students[cnt] = tmp;
            cnt++;
        }
        if (tmp.surname == surname) {
            students[cnt] = newStudent;
            cnt++;
        }
    }

    file.close();
    file.open("file.txt", ios::out | ios::trunc);
    for (int i = 0; i < cnt; i++) {
        students[i].print(file);
    }
}

/*
CIN:
3 1 Tolstoy
Bulgakov Mikhail Afanasyevich
+79675544332
2
5 5 5

FILE:
Pushkin Alexander Sergeyevich
+78005553535
1
5 5 5

Tolstoy Lev Nikolayevich
+79161234567
2
5 5 5

Dostoevsky Fyodor Mikhailovich
+79037654321
2
5 5 5

Chekhov Anton Pavlovich
+79254443322
2
5 5 5

Turgenev Ivan Sergeyevich
+79109876543
1
2 2 2

Gogol Nikolai Vasilyevich
+79381122334
1
2 2 2
*/