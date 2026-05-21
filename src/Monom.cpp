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

double Monom::getCoefficient() const
{
    return egyutthato;
}

void Monom::changeName(const std::string& uj_ismeretlen)
{
    ismeretlen = uj_ismeretlen;
}

std::string Monom::getName() const
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
    if (egyutthato == 1 && !ismeretlen.empty()) return "+"+ismeretlen;
    if (egyutthato == -1 && !ismeretlen.empty()) return "-"+ismeretlen;
    return std::format("{:+}", egyutthato) + ismeretlen;
}
