#include "Celfuggveny.h"

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
