#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_FRACTION_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_FRACTION_H
#include <ostream>

class Pair {
    int first;
    double second;

public:
    Pair(double, int);
    Pair(const Pair &);
    Pair();
    ~Pair();
    double getDouble() const;
    void setDouble(double);
    int getInt() const;
    void setInt(int);
    Pair &operator=(Pair const &p);
    Pair operator+(Pair &p);
    Pair operator+(const Pair &p) const;
    Pair operator+(int);
    Pair operator+(double);
    Pair& operator+=(Pair const &p);
    Pair& operator/=(int a);
    Pair operator/(int a) const;
    bool operator>(Pair const &p) const;
    bool operator<(Pair const &p) const;
    bool operator==(const Pair &p) const;
    friend std::ostream &operator<<(std::ostream &, const Pair &);
    friend std::istream &operator>>(std::istream &, Pair &);
};

#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_FRACTION_H
