#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_PAIR_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_PAIR_H

#include <iosfwd>

class Pair {
    int first;
    double second;

public:
    Pair();
    Pair(int f, double s);
    Pair(const Pair &p);
    ~Pair();

    int getFirst() const;
    double getSecond() const;
    void setFirst(int f);
    void setSecond(double s);

    Pair operator-(const Pair &p) const;
    Pair operator+(int v) const;
    Pair operator+(double v) const;
    Pair &operator=(const Pair &p);

    bool operator==(const Pair &p) const;
    bool operator!=(const Pair &p) const;
    bool operator<(const Pair &p) const;
    bool operator>(const Pair &p) const;

    friend std::ostream &operator<<(std::ostream &out, const Pair &p);
    friend std::istream &operator>>(std::istream &in, Pair &p);
    friend std::fstream &operator<<(std::fstream &out, const Pair &p);
    friend std::fstream &operator>>(std::fstream &in, Pair &p);
};

#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_PAIR_H
