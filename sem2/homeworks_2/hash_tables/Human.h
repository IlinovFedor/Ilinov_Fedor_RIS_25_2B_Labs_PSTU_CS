#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_HUMAN_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_HUMAN_H
#include <string>
#include <ostream>
#include <istream>

class Human {
    std::string name;
    std::string birthday;
    std::string passportNumber;
public:
    Human();
    Human(const std::string &n, const std::string &b, const std::string &p) {
        name = n;
        birthday = b;
        passportNumber = p;
    }

    std::string createRandomName();
    std::string createRandomBirthday();
    std::string createRandomPassportNumber();

    std::string getName() const { return name; }
    void setName(const std::string &s) { name = s; }
    std::string getBirthday() const { return birthday; }
    void setBirthday(const std::string &s) { birthday = s; }
    std::string getPassportNumber() const { return passportNumber; }
    void setPassportNumber(const std::string &s) { passportNumber = s; }

    int dateToNumber(const std::string &s) const;

    friend std::ostream& operator<<(std::ostream& stream, const Human& h);
    friend std::istream& operator>>(std::istream& stream, Human& h);
};

#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_HUMAN_H
