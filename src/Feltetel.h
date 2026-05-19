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
public:
    enum class Condition
    {
        LessThan,
        LessThanOrEquals,
        GreaterThan,
        GreaterThanOrEquals,
    };

private:
    std::vector<Monom> bal_oldal;
    std::vector<Monom> jobb_oldal;
    Condition m_condition;

public:
    Feltetel(Condition cond, std::vector<Monom> bal, std::vector<Monom> jobb);

    void add(Oldal oldal, Monom monom);
    void removeLast(Oldal oldal);

    void convertToLessThanOrEquals();

    operator std::string() const;
};

#endif // FELTETEL_H
