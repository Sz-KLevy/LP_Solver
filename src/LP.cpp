#include "LP.h"

LP::LP(
    std::vector<std::unique_ptr<Feltetel>>& feltetelek,
    std::unique_ptr<Celfuggveny>& celfuggveny) {
    m_feltetelek = std::move(feltetelek);
    m_celfuggveny = std::move(celfuggveny);
}

LP::operator std::string() const
{
    std::string out;
    for (const auto& v : m_feltetelek) {
        out += (std::string{*v} + "\n");
    }
    out += *m_celfuggveny;

    return out;
}

