#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_TOVAR_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_TOVAR_H
#include <string>


class Salary {
    std::string name;
    int bonusPercents;
    double baseSalary;
    std::string marshal();
public:
    Salary();//конструктор без параметров
    Salary(std::string, int, double);//конструктор с параметрами
    Salary(const Salary&);//конструктор копирования
    ~Salary();//деструктор
    std::string getName();//селектор
    void setName(std::string);//модификатор
    int getBaseSalary();//селектор
    void setBaseSalary(double); //модификатор
    double getBonusPercents();//селектор
    void setBonusPercents(int); //модификатор
    void show();//просмотр атрибутов
};


#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_TOVAR_H