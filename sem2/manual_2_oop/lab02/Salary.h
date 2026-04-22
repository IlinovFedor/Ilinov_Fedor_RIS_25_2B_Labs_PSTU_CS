#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_TOVAR_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_TOVAR_H
#include <string>


class Salary {
    std::string name;
    int bonusPercents;
    double baseSalary;
    std::string marshal();
public:
    Salary();
    Salary(std::string, int, double);
    Salary(const Salary&);
    ~Salary();
    std::string getName();
    void setName(std::string);
    int getBaseSalary();
    void setBaseSalary(double);
    double getBonusPercents();
    void setBonusPercents(int);
    void show();
};


#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_TOVAR_H