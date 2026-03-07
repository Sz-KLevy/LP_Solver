#include <iostream>
#include <vector>
#include<string>


class Monom{
public:
    double egyutthato;
    std::string ismeretlen;

    Monom(double e, std::string i){
        egyutthato = e;
        ismeretlen = i;
    }

    void changeCoefficient(double uj_egyutthato){egyutthato = uj_egyutthato;}

    double getCoefficient(){return egyutthato;}

    void changeName(std::string uj_ismeretlen){ismeretlen = uj_ismeretlen;}

    std::string getName(){return ismeretlen;}

    void show(){
        std::cout << egyutthato << ismeretlen;
    }
};

enum class Oldal
{
    Jobb,
    Bal,
};

class Feltetel{
public:
    std::vector<Monom> bal_oldal;
    std::vector<Monom> jobb_oldal;

    Feltetel(std::vector<Monom> bal, std::vector<Monom> jobb){
        bal_oldal = bal;
        jobb_oldal = jobb;
    }

    void add(Oldal oldal, Monom monom){
        if(oldal==Oldal::Bal){bal_oldal.push_back(monom);}
        else if(oldal == Oldal::Jobb){jobb_oldal.push_back(monom);}
    }

    void removeLast(Oldal oldal){
        if(oldal==Oldal::Bal){bal_oldal.pop_back();}
        else if(oldal == Oldal::Jobb){jobb_oldal.pop_back();}
    }

    void show(){
        for(int i = 0; i < bal_oldal.size(); i++){
            bal_oldal[i].show();
        }
        for(int i = 0; i < jobb_oldal.size(); i++){
            jobb_oldal[i].show();
        }
    }
};

class Celfuggveny{
public:
    std::string irany;
    std::vector<Monom> fuggveny;

    //nincsen irany ellenőrzés
    Celfuggveny(std::string i, std::vector<Monom> f){
        irany = i;
        fuggveny = f;
    }

    void changeDirection(){
        if(irany == "max"){irany = "min";}
        else if(irany == "min"){irany = "max";}
        else{std::cerr << "Nem megfelelo az iranya:" << irany;}

        for(int i = 0; i < fuggveny.size(); i++){
            fuggveny[i].changeCoefficient(-fuggveny[i].getCoefficient());
        }
    }

    void add(Monom monom){fuggveny.push_back(monom);}

    void removeLast(){fuggveny.pop_back();}

    void show(){
        for(int i = 0; i < fuggveny.size(); i++){
            fuggveny[i].show();
        }
    }
};


/*
celfuggveny:
min |x-x1|+|x-x2|+|x-x3|+...

feltetel:
x>=legkisebb_ertek
x<= legnagyobb_ertek
*/


int main()
{
    std::cout << "Add meg a kordinatakat:\n";

    double legkisebb_ertek =0;
    double legnagyobb_ertek =1;

    std::vector<double> temp_storage;
    std::string a="";

    do{
        std::cin >> a;
        try{
            double b=std::stod(a);
            if(legkisebb_ertek <= b && b <= legnagyobb_ertek){
                temp_storage.push_back(b);
            }
            else{
                std::cout << "Ertek tartomanyon kivul esik.";
            }
        }
        catch(...){
        }
    }while(a!="END");



    return 0;
}
