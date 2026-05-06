#ifndef CELFUGGVENY_H
#define CELFUGGVENY_H

#include <vector>
#include "Monom.h"

class Celfuggveny
{
public:
    enum class Irany {
        Min,
        Max,
    };

private:
    Irany irany;
    std::vector<Monom> fuggveny;

public:
    Celfuggveny(Irany i, std::vector<Monom> f);

    void changeDirection();

    void add(Monom monom);

    void removeLast();

    operator std::string() const;
};

#endif // CELFUGGVENY_H
