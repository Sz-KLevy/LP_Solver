#include "LP.h"
#include "Feltetel.h"
#include <format>
#include <memory>
#include <cassert>
#include <limits>

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

bool LP::isOptimal() const
{
    return m_celfuggveny->isOptimal();
}

void LP::stepSimplex()
{
    auto enteringVariable = m_celfuggveny->getEnteringVariable();
    if(!enteringVariable){return;}
    auto leavingVariable = getLeavingVariable(*enteringVariable);
    if(!leavingVariable){return;}
    for(auto& felt : m_feltetelek)
    {
        if(felt ->getSide(Oldal::Bal)[0].getName() == *leavingVariable)
        {
            felt ->switchVariables(*enteringVariable);
            for(auto&felt2 : m_feltetelek)
            {
                if(felt2 -> getSide(Oldal::Bal)[0].getName() != *enteringVariable)
                {
                    felt2 -> changeFeltetel(*enteringVariable, *felt);
                }
            }
            m_celfuggveny -> changeCelfuggveny(*enteringVariable, *felt);
            break;
        }
    }

    return;
}

std::optional<std::string> LP::getLeavingVariable(std::string enteringVariable) const{
    std::optional<std::string> leavingVariable;
    double leavingMinimumRatioTest = std::numeric_limits<double>::infinity();

    for(const auto& feltetel : m_feltetelek){
        auto result = feltetel -> minimumRatioTest(enteringVariable);
        if(result)
        {
            auto [ratioTestName, ratioTestValue] = *result;
            if(ratioTestValue < leavingMinimumRatioTest)
            {
                    leavingMinimumRatioTest = ratioTestValue;
                    leavingVariable = ratioTestName;
            }
        }
    }
    return leavingVariable;
}

std::map<std::string, double> LP::getVariables() const
{
    std::map<std::string, double> out;
    for (const auto& felt : m_feltetelek)
    {
        const auto& left = felt->getSide(Oldal::Bal);
        assert(left.size() == 1);

        const auto& right = felt->getSide(Oldal::Jobb);
        assert(right.size() >= 1 && right[0].isConstant());

        out[left[0].getName()] = right[0].getCoefficient();

        for (const auto& r : right)
        {
            if (r.isConstant()) continue;
            out[r.getName()] = 0;
        }
    }

    return out;
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

