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

const std::vector<Monom>& Feltetel::getSide(Oldal oldal) const
{
    return oldal == Oldal::Bal ? bal_oldal : jobb_oldal;
}

std::optional<std::pair<std::string, double>> Feltetel::minimumRatioTest(const std::string& enteringVariable) const
{
    if(bal_oldal.size() != 1 || jobb_oldal.empty()){return std::nullopt;}
    const auto& balMonom = bal_oldal[0];
    if(balMonom.getCoefficient() != 1){return std::nullopt;}
    double constant, coefficient;
    bool hasConstant = false;
    bool hasEnteringVariable = false;
    for(auto& jobbMonom : jobb_oldal)
    {
        if(jobbMonom.getName() == ""){constant = jobbMonom.getCoefficient(); hasConstant = true;}
        if(jobbMonom.getName() == enteringVariable){coefficient = jobbMonom.getCoefficient(); hasEnteringVariable = true;}
    }
    if(!hasConstant || !hasEnteringVariable){return std::nullopt;}
    if(coefficient >= 0){return std::nullopt;}
    else{return std::pair<std::string, double>{balMonom.getName(), constant/(-coefficient)};}
}

void Feltetel::switchVariables(std::string enteringVariable)
{
    bal_oldal[0].changeCoefficient(-bal_oldal[0].getCoefficient());
    add(Oldal::Jobb, bal_oldal[0]);
    removeLast(Oldal::Bal);

    double enteringCoefficient;
    for(auto it = jobb_oldal.begin(); it != jobb_oldal.end(); ++it)
    {
        if(it->getName() == enteringVariable)
        {
            it->changeCoefficient(-it->getCoefficient());
            enteringCoefficient=it->getCoefficient();
            add(Oldal::Bal,*it);
            jobb_oldal.erase(it);
            break;
        }
    }
    bal_oldal[0].changeCoefficient(1);
    for(auto& jobbMonom :jobb_oldal)
    {
        jobbMonom /= enteringCoefficient;
    }
}

void Feltetel::changeFeltetel(std::string changeName, Feltetel change)
{
    double changeValue = 0;
    bool found = false;
    for(auto it = jobb_oldal.begin(); it != jobb_oldal.end(); ++it)
    {
        if(it->getName()==changeName)
        {
            changeValue = it->getCoefficient();
            if(changeValue==0){return;}
            found = true;
            jobb_oldal.erase(it);
            break;
        }
    }
    if(!found){return;}

    for(auto& monom : change.getSide(Oldal::Jobb))
    {
        bool changed = false;
        std::string searchName = monom.getName();
        for(auto& jobbMonom : jobb_oldal){
            if(jobbMonom.getName() == searchName)
            {
                jobbMonom+=(changeValue*monom.getCoefficient());
                changed = true;
                break;
            }
        }
        if(!changed)
        {
            auto newMonom = monom;
            newMonom *= changeValue;
            add(Oldal::Jobb, newMonom);
        }
    }
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
    case Condition::Equal:
        return;
    }
    m_condition = Condition::LessThanOrEquals;
}

void Feltetel::convertToStandardForm()
{
    for(auto it = jobb_oldal.begin(); it!= jobb_oldal.end();){
        if(!it->isConstant()){
            it ->changeCoefficient(-it ->getCoefficient());
            bal_oldal.push_back(*it);
            it = jobb_oldal.erase(it);
        }
        else{
            it++;
        }
    }

    for(auto it = bal_oldal.begin(); it!= bal_oldal.end();){
        if(it->isConstant()){
            it ->changeCoefficient(-it ->getCoefficient());
            jobb_oldal.push_back(*it);
            it = bal_oldal.erase(it);
        }
        else{
            it++;
        }
    }
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
    case Condition::Equal:
        out += " = ";
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
