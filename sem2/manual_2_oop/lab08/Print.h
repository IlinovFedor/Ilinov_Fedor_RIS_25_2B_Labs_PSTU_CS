#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_PERSON_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_PERSON_H
#include <string>
#include "Object.h"


class Print : public Object {
    std::string name;
    std::string author;

public:
    Print();
    Print(std::string, std::string);
    Print(Print &);
    ~Print();
    const std::string getName() override;
    void setName(std::string);
    const std::string getAuthor();
    void setAuthor(std::string);
    Print &operator=(Print const &p);
    friend std::ostream &operator<<(std::ostream &, const Print &);
    friend std::istream &operator>>(std::istream &, Print &);
    void show() override;
    void input() override;

    virtual void handleEvent(const Event &e);
};


#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_PERSON_H
