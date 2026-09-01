#include "Celfuggveny.h"
#include <algorithm>

Celfuggveny::Celfuggveny(Irany i, std::vector<Monom> f){
    irany = i;
    fuggveny = f;
}

void Celfuggveny::changeDirection(){
    irany = (irany == Irany::Max ? Irany::Min : Irany::Max);

    for(int i = 0; i < fuggveny.size(); i++){
        fuggveny[i] *= -1;
    }
}

void Celfuggveny::add(Monom monom){
    fuggveny.push_back(monom);
}

void Celfuggveny::removeLast(){
    fuggveny.pop_back();
}

void Celfuggveny::convertToStandardForm()
{
    if (irany == Irany::Min)
    {
        changeDirection();
    }
}

void Celfuggveny::convertToDictionaryForm()
{
    convertToStandardForm();
    m_dictionaryForm = true;
}

bool Celfuggveny::isOptimal() const
{
    return std::all_of(fuggveny.begin(), fuggveny.end(), [](const Monom& mon){
        return mon.getCoefficient() <= 0;
    });
}

std::optional<std::string> Celfuggveny::getEnteringVariable() const
{
    for(auto& mon : fuggveny)
    {
        if(irany == Irany::Max && mon.getCoefficient() > 0){return mon.getName();}
        else if(irany == Irany::Min && mon.getCoefficient() < 0){return mon.getName();}
    }
    return std::nullopt;
}

void Celfuggveny::changeCelfuggveny(std::string changeName, Feltetel change)
{
    double changeValue = 0;
    bool found = false;
    for(auto it = fuggveny.begin(); it != fuggveny.end(); ++it)
    {
        if(it->getName()==changeName)
        {
            changeValue = it->getCoefficient();
            if(changeValue==0){return;}
            found = true;
            fuggveny.erase(it);
            break;
        }
    }
    if(!found){return;}

    for(auto& monom : change.getSide(Oldal::Jobb))
    {
        bool changed = false;
        std::string searchName = monom.getName();
        for(auto& fuggvenyMonom : fuggveny){
            if(fuggvenyMonom.getName() == searchName)
            {
                fuggvenyMonom+=(changeValue*monom.getCoefficient());
                changed = true;
                break;
            }
        }
        if(!changed)
        {
            auto newMonom = monom;
            newMonom *= changeValue;
            fuggveny.push_back(newMonom);
        }
    }
}

Celfuggveny::operator std::string() const {
    std::string out;
    if (m_dictionaryForm)
    {
        out += "z =";
    }
    else
    {
        out += (irany == Irany::Min ? "min" : "max");
    }
    out += " ";
    for (const auto& v : fuggveny) {
        out += v;
    }

    return out;
}
