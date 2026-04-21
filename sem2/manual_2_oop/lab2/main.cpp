#include <iostream>;
#include "Salary.h"

using namespace std;

Salary makeSalary()
{
    string s;
    int i;
    double d;
    cout<<"Name? ";
    cin>>s;
    cout<<"Bonus percents? ";
    cin>>i;
    cout<<"Base salary? ";
    cin>>d;
    Salary t(s,i,d);
    return t;
}

int main() {
    //конструктор без параметров
    Salary t1;
    //коструктор с параметрами
    Salary t2("Computer", 1, 15000);
    //конструктор копирования
    Salary t3=t2;
    t3.setName("Telephon");
    t3.setBonusPercents(2);
    t3.setBaseSalary(5000.0);
    //конструктор копирования
    t1=makeSalary();
    t1.show();
}