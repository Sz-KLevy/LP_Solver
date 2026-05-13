#include "Feltetel.h"

Feltetel::Feltetel(std::vector<Monom> bal, std::vector<Monom> jobb){
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

Feltetel::operator std::string() const {
    std::string out;
    for (const auto& val : bal_oldal) {
        out += val;
    }
    out += " ";
    for (const auto& val : jobb_oldal) {
        out += val;
    }
    return out;
}
