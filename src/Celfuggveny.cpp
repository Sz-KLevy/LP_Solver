#include "Celfuggveny.h"

Celfuggveny::Celfuggveny(Irany i, std::vector<Monom> f){
    irany = i;
    fuggveny = f;
}

void Celfuggveny::changeDirection(){
    irany = (irany == Irany::Max ? Irany::Min : Irany::Max);

    for(int i = 0; i < fuggveny.size(); i++){
        fuggveny[i].changeCoefficient(-fuggveny[i].getCoefficient());
    }
}

void Celfuggveny::add(Monom monom){
    fuggveny.push_back(monom);
}

void Celfuggveny::removeLast(){
    fuggveny.pop_back();
}

Celfuggveny::operator std::string() const {
    std::string out = "z = ";
    out += (irany == Irany::Min ? "min" : "max");
    out += " ";
    for (const auto& v : fuggveny) {
        out += v;
    }

    return out;
}
