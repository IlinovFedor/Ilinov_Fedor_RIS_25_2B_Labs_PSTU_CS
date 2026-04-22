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
    Salary t1;
    Salary t2("Say Gabigi", 1, 15000);
    Salary t3=t2;
    t3.setName("Qebopi Coloyemuj");
    t3.setBonusPercents(2);
    t3.setBaseSalary(5000.0);
    t1=makeSalary();
    t1.show();
}