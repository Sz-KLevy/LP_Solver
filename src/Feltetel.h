#ifndef FELTETEL_H
#define FELTETEL_H

#include "Monom.h"
#include <vector>

enum class Oldal
{
    Jobb,
    Bal,
};

class Feltetel
{
private:
    std::vector<Monom> bal_oldal;
    std::vector<Monom> jobb_oldal;

public:
    Feltetel(std::vector<Monom> bal, std::vector<Monom> jobb);

    void add(Oldal oldal, Monom monom);

    void removeLast(Oldal oldal);

    operator std::string() const;
};

#endif // FELTETEL_H
