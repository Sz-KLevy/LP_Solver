#ifndef LP_H
#define LP_H

#include <vector>
#include <memory>
#include "Feltetel.h"
#include "Celfuggveny.h"

class LP {
private:
    std::vector<std::unique_ptr<Feltetel>> m_feltetelek;
    std::unique_ptr<Celfuggveny> m_celfuggveny;

public:
    LP(
        std::vector<std::unique_ptr<Feltetel>>& feltetelek,
        std::unique_ptr<Celfuggveny>& celfuggveny);

    operator std::string() const;
};

#endif // LP_H
