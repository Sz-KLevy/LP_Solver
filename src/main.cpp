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

    QApplication app(argc, argv);

    UI ui;

    auto celf = std::make_unique<Celfuggveny>(Celfuggveny::Irany::Min, std::vector<Monom>{});

    std::vector<std::unique_ptr<Feltetel>> feltetelek;

    int counter = 1;

    ui.point_added.connect([&celf, &feltetelek, &counter](std::array<float, 2> point){
        //std::cout <<"point added to: x: " << point[0] << " y: " << point[1] << "\n";

        celf->add(Monom{1, "u" + std::to_string(counter)});
        celf->add(Monom{1, "v" + std::to_string(counter)});

        feltetelek.emplace_back(std::make_unique<Feltetel>(Feltetel::Condition::GreaterThanOrEquals,std::vector<Monom>{{1, "u" + std::to_string(counter)}}, std::vector<Monom>{{1, "x"},{-point[0],}}));
        feltetelek.emplace_back(std::make_unique<Feltetel>(Feltetel::Condition::GreaterThanOrEquals,std::vector<Monom>{{1, "u" + std::to_string(counter)}}, std::vector<Monom>{{point[0],},{-1, "x"}}));

        feltetelek.emplace_back(std::make_unique<Feltetel>(Feltetel::Condition::GreaterThanOrEquals,std::vector<Monom>{{1, "v" + std::to_string(counter)}}, std::vector<Monom>{{1, "y"},{-point[0],}}));
        feltetelek.emplace_back(std::make_unique<Feltetel>(Feltetel::Condition::GreaterThanOrEquals,std::vector<Monom>{{1, "v" + std::to_string(counter)}}, std::vector<Monom>{{point[0],},{-1, "y"}}));

        counter++;

        std::vector<std::unique_ptr<Feltetel>> feltetelek_copy;
        feltetelek_copy.reserve(feltetelek.size());

        for(const auto &f:feltetelek){
            feltetelek_copy.push_back(f->clone());
        }

        auto celf_copy = std::make_unique<Celfuggveny>(*celf);

        auto lp = std::make_unique<LP>(feltetelek_copy, celf_copy);

        std::cout << "Original:\n";
        std::cout << std::string{*lp} << '\n';

        lp->convertToStandardForm();
        std::cout << "Standard form:\n";
        std::cout << std::string{*lp} << '\n';

        lp->convertToDictionaryForm();
        std::cout << "Dictionary form:\n";
        std::cout << std::string{*lp} << '\n';
        std::cout << '\n';
    });

    ui.show();

    //return 0;
    return app.exec();
};
