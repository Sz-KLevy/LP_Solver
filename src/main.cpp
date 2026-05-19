#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <memory>
#include "UI.h"
#include "LP.h"


/*
celfuggveny:
min |x-x1|+|x-x2|+|x-x3|+...

feltetel:
x>=legkisebb_ertek
x<= legnagyobb_ertek
*/


int main(int argc, char** argv){
    /*
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


    */

    std::vector<Monom> monom = {Monom{2, "x₁"}, Monom{0.5, "x₂"}};
    std::vector<std::unique_ptr<Feltetel>> feltetelek;
    feltetelek.emplace_back(std::make_unique<Feltetel>(
        Feltetel::Condition::GreaterThanOrEquals,
        std::vector<Monom>{{5, "x₁"}},
        std::vector<Monom>{{20}}
    ));
    feltetelek.emplace_back(std::make_unique<Feltetel>(
        Feltetel::Condition::LessThanOrEquals,
        std::vector<Monom>{{1, "x₂"}},
        std::vector<Monom>{{8}}
    ));
    feltetelek.emplace_back(std::make_unique<Feltetel>(
        Feltetel::Condition::LessThanOrEquals,
        std::vector<Monom>{{0.5, "x₃"}},
        std::vector<Monom>{{12}}
    ));
    auto celf = std::make_unique<Celfuggveny>(Celfuggveny::Irany::Min, monom);

    auto lp = std::make_unique<LP>(feltetelek, celf);

    std::cout << "Original:\n";
    std::cout << std::string{*lp} << '\n';
    lp->convertToStandardForm();
    std::cout << "\nStandard form:\n";
    std::cout << std::string{*lp} << '\n';

    QApplication app(argc, argv);
    /*QLabel label{"Hello world"};
    label.setMargin(20);
    label.show();*/
    UI ui;
    ui.show();

    //return 0;
    return app.exec();
};
