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
    bool m_dictionaryForm = false;

public:
    Celfuggveny(Irany i, std::vector<Monom> f);

    void changeDirection();

    void add(Monom monom);
    void removeLast();

    void convertToStandardForm();
    void convertToDictionaryForm();
    bool isOptimal() const;

    operator std::string() const;
};

#endif // CELFUGGVENY_H
