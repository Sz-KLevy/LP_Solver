#include "LP.h"
#include "Feltetel.h"
#include <format>
#include <memory>
#include <cassert>

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

void LP::convertToDictionaryForm()
{
    m_celfuggveny->convertToDictionaryForm();

    std::vector<std::unique_ptr<Feltetel>> feltetelek;
    for (int i{}; i < m_feltetelek.size(); ++i)
    {
        const auto& cond = m_feltetelek[i];
        auto right = cond->getSide(Oldal::Bal);
        std::transform(right.cbegin(), right.cend(), right.begin(),
            [](Monom mon){
                mon *= -1;
                return mon;
        });
        auto constant = std::vector<Monom>{cond->getSide(Oldal::Jobb)};
        assert(constant.size() == 1);
        assert(constant[0].isConstant());
        right.insert(right.begin(), std::move(constant[0]));
        auto newCond = std::make_unique<Feltetel>(
            Feltetel::Condition::Equal,
            std::vector<Monom>{{1, std::format("w{:02}", i+1)}},
            std::move(right)
        );
        feltetelek.push_back(std::move(newCond));
    }
    m_feltetelek = std::move(feltetelek);
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

