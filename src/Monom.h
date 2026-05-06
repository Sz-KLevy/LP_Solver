#ifndef MONOM_H
#define MONOM_H

#include <string>

class Monom
{
private:
    double egyutthato;
    std::string ismeretlen;

public:
    Monom(double e, std::string i);

    void changeCoefficient(double uj_egyutthato);
    double getCoefficient();

    void changeName(std::string uj_ismeretlen);
    std::string getName();

    operator std::string() const;
};

#endif // MONOM_H
