#include <format>
#include "Monom.h"

Monom::Monom(double e, std::string i)
{
    egyutthato = e;
    ismeretlen = i;
}

void Monom::changeCoefficient(double uj_egyutthato)
{
    egyutthato = uj_egyutthato;
}

double Monom::getCoefficient()
{
    return egyutthato;
}

void Monom::changeName(std::string uj_ismeretlen)
{
    ismeretlen = uj_ismeretlen;
}

std::string Monom::getName()
{
    return ismeretlen;
}

Monom::operator std::string() const
{
    return std::format("{:+}", egyutthato) + ismeretlen;
}
