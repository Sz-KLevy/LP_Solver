#include <iostream>
#include <vector>
#include<string>
using namespace std;


class Monom{
public:
    double egyutthato;
    string ismeretlen;

    Monom(double e, string i){
        egyutthato = e;
        ismeretlen = i;
    }

    void changeCoefficient(double uj_egyutthato){egyutthato = uj_egyutthato;}

    double getCoefficient(){return egyutthato;}

    void changeName(string uj_ismeretlen){ismeretlen = uj_ismeretlen;}

    string getName(){return ismeretlen;}

    show(){
        cout << egyutthato << ismeretlen;
    }
};

class Feltetel{
public:
    vector<Monom> bal_oldal;
    vector<Monom> jobb_oldal;

    Feltetel(vector<Monom> bal, vector<Monom> jobb){
        bal_oldal = bal;
        jobb_oldal = jobb;
    }

    void add(string oldal, Monom monom){
        if(oldal=="bal"){bal_oldal.push_back(monom);}
        else if(oldal == "jobb"){jobb_oldal.push_back(monom);}
        else{cerr << "Nincsen ilyen oldal";}
    }

    void removeLast(string oldal){
        if(oldal=="bal"){bal_oldal.pop_back();}
        else if(oldal == "jobb"){jobb_oldal.pop_back();}
        else{cerr << "Nincsen ilyen oldal";}
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
    string irany;
    vector<Monom> fuggveny;

    //nincsen irany ellenőrzés
    Celfuggveny(string i, vector<Monom> f){
        irany = i;
        fuggveny = f;
    }

    void changeDirection(){
        if(irany == "max"){irany = "min";}
        else if(irany == "min"){irany = "max";}
        else{cerr << "Nem megfelelo az iranya:" << irany;}

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

    vector<double> temp_storage;
    string a="";

    do{
        cin >> a;
        try{
            double b=stod(a);
            if(legkisebb_ertek <= b && b <= legnagyobb_ertek){
                temp_storage.push_back(b);
            }
            else{
                cout << "Ertek tartomanyon kivul esik.";
            }
        }
        catch(...){
        }
    }while(a!="END");



    return 0;
}
