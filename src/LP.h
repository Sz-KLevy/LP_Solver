#ifndef LP_H
#define LP_H

#include <vector>
#include <memory>
#include <map>
#include <optional>
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

    void convertToStandardForm();
    void convertToDictionaryForm();
    bool isOptimal() const;
    void stepSimplex();
    std::optional<std::string> getLeavingVariable(std::string) const;
    std::map<std::string, double> getVariables() const;
    operator std::string() const;
};

#endif // LP_H
