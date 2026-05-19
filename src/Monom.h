#ifndef MONOM_H
#define MONOM_H

#include <string>

class Monom
{
private:
    double egyutthato;
    std::string ismeretlen;

public:
    Monom(double e, std::string i="");

    void changeCoefficient(double uj_egyutthato);
    double getCoefficient();

    void changeName(const std::string& uj_ismeretlen);
    std::string getName();

    bool isConstant() const;

    Monom& operator*=(double val);
    Monom& operator/=(double val);

    operator std::string() const;
};

#endif // MONOM_H
