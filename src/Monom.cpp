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

void Monom::changeName(const std::string& uj_ismeretlen)
{
    ismeretlen = uj_ismeretlen;
}

std::string Monom::getName()
{
    return ismeretlen;
}

bool Monom::isConstant() const
{
    return ismeretlen.empty();
}

Monom& Monom::operator*=(double val)
{
    egyutthato *= val;
    return *this;
}

Monom& Monom::operator/=(double val)
{
    egyutthato /= val;
    return *this;
}

Monom::operator std::string() const
{
    return std::format("{:+}", egyutthato) + ismeretlen;
}
