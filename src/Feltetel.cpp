#include "Feltetel.h"

Feltetel::Feltetel(Condition cond, std::vector<Monom> bal, std::vector<Monom> jobb){
    m_condition = cond;
    bal_oldal = bal;
    jobb_oldal = jobb;
}

void Feltetel::add(Oldal oldal, Monom monom){
    if(oldal==Oldal::Bal){bal_oldal.push_back(monom);}
    else if(oldal == Oldal::Jobb){jobb_oldal.push_back(monom);}
}

void Feltetel::removeLast(Oldal oldal){
    if(oldal==Oldal::Bal){bal_oldal.pop_back();}
    else if(oldal == Oldal::Jobb){jobb_oldal.pop_back();}
}

void Feltetel::convertToLessThanOrEquals()
{
    switch (m_condition)
    {
    case Condition::LessThanOrEquals:
    case Condition::LessThan:
        // Noop
        break;
    case Condition::GreaterThanOrEquals:
    case Condition::GreaterThan:
        for (auto& mon : bal_oldal)
            mon *= -1;
        for (auto& mon : jobb_oldal)
            mon *= -1;
        break;
    }
    m_condition = Condition::LessThanOrEquals;
}

Feltetel::operator std::string() const {
    std::string out;
    for (const auto& val : bal_oldal) {
        out += val;
    }
    switch (m_condition)
    {
    case Condition::LessThan:
        out += " < ";
        break;
    case Condition::LessThanOrEquals:
        out += " ≤ ";
        break;
    case Condition::GreaterThan:
        out += " > ";
        break;
    case Condition::GreaterThanOrEquals:
        out += " ≥ ";
        break;
    }
    for (const auto& val : jobb_oldal) {
        out += val;
    }
    return out;
}

std::unique_ptr<Feltetel> Feltetel::clone() const {
    return std::make_unique<Feltetel>(*this);
}