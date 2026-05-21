#include "LP.h"

LP::LP(
    std::vector<std::unique_ptr<Feltetel>>& feltetelek,
    std::unique_ptr<Celfuggveny>& celfuggveny) {
    m_feltetelek = std::move(feltetelek);
    m_celfuggveny = std::move(celfuggveny);
}

void LP::convertToStandardForm()
{
    m_celfuggveny->convertToStandardForm();
    for (auto& felt : m_feltetelek)
    {
        felt->convertToLessThanOrEquals();
        felt->convertToStandardForm();
    }
}

LP::operator std::string() const
{
    std::string out;
    size_t maxLeftSideLen = 0;
    for (const auto& v : m_feltetelek) {
        maxLeftSideLen = std::max(std::string{*v}.find(" "), maxLeftSideLen);
    }
    for (const auto& v : m_feltetelek) {
        const auto& s = std::string{*v};
        out += std::string(maxLeftSideLen-s.find(" "), ' ');
        out += s + "\n";
    }
    out += *m_celfuggveny;

    return out;
}

