#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_Student_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_Student_H
#include <string>
#include "Print.h"

class Magazine : public Print {
    std::string title;
    int pages;

public:
    Magazine();
    Magazine(std::string name, std::string author, std::string subject, int grade);
    Magazine(Print, std::string subject, int grade);
    Magazine(Magazine&);
    ~Magazine();
    std::string getTitle();
    void setTitle(std::string);
    int getPages();
    void setPages(int);
    Magazine &operator=(Magazine &p);
    friend std::ostream &operator<<(std::ostream &, Magazine &);
    friend std::istream &operator>>(std::istream &, Magazine &);
    void show() override;
    void input() override;
};


#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_Student_H
