#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <memory>
#include <format>
#include <QApplication>
#include <QLabel>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>

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
        std::cout << std::format("{:+}", egyutthato) << ismeretlen;
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
    enum class Irany {
        Min,
        Max,
    };

    Irany irany;
    std::vector<Monom> fuggveny;

    Celfuggveny(Irany i, std::vector<Monom> f){
        irany = i;
        fuggveny = f;
    }

    void changeDirection(){
        irany = (irany == Irany::Max ? Irany::Min : Irany::Max);

        for(int i = 0; i < fuggveny.size(); i++){
            fuggveny[i].changeCoefficient(-fuggveny[i].getCoefficient());
        }
    }

    void add(Monom monom){fuggveny.push_back(monom);}

    void removeLast(){fuggveny.pop_back();}

    void show(){
        std::cout << "z = " << (irany == Irany::Min ? "min" : "max") << " ";
        for(int i = 0; i < fuggveny.size(); i++){
            fuggveny[i].show();
        }
    }
};

class LP {
private:
    std::vector<std::unique_ptr<Feltetel>> m_feltetelek;
    std::unique_ptr<Celfuggveny> m_celfuggveny;

public:
    LP(
        std::vector<std::unique_ptr<Feltetel>>& feltetelek,
        std::unique_ptr<Celfuggveny>& celfuggveny) {
        m_feltetelek = std::move(feltetelek);
        m_celfuggveny = std::move(celfuggveny);
    }

    operator std::string() const
    {
        std::string out;
        for (const auto& v : m_feltetelek) {
            out += (std::string{*v} + "\n");
        }
        out += *m_celfuggveny;

        return out;
    }

};


class UI : public QWidget{
public:
    int windowSize[2] = {500, 500};
    int cellSize = 50;
    std::vector<std::array<float,2>> points;
    std::array<float,2> optimalPoint;



    UI(QWidget *parent = nullptr) : QWidget(parent){
        resize(windowSize[0], windowSize[1]);
        optimalPoint={0.0,0.0};
    }

    std::vector<std::array<float,2>> getPoints(){
        return points;
    }




private:
    void paintEvent(QPaintEvent*) override {
        QPainter painter(this);
        drawGrid(painter, cellSize);
        drawPoints(painter);
        drawOptimalPoint(painter, optimalPoint);
    }

    void mousePressEvent(QMouseEvent* event) override {
        QPoint click = event->pos();
        int origo[2] = {((width()/cellSize)/2)*cellSize, ((height()/cellSize)/2)*cellSize};

        points.push_back({(float)(click.x()-origo[0])/cellSize, (float)-(click.y()-origo[1])/cellSize});
        std::cout << (float)(click.x()-origo[0])/cellSize << "\t" << (float)-(click.y()-origo[1])/cellSize << std::endl;

        optimalPoint = {1.0,1.0};//this is where the UI asks for the position of the optimal point

        update(); //repaints
    }


    void drawGrid(QPainter& painter, int cellSize){
        QPen gridPen(Qt::black);
        gridPen.setWidth(1);
        painter.setPen(gridPen);

        QPen wideGridPen(Qt::black);
        wideGridPen.setWidth(4);

        for (int x = 0; x < width(); x += cellSize){
            if(((width()/cellSize)/2)*cellSize==x){
                painter.setPen(wideGridPen);
                painter.drawLine(x,0,x,height());
                painter.setPen(gridPen);

                int number=(height()/cellSize)/2;
                for (int y = 0; y < height(); y += cellSize){
                    painter.drawText(x+5,y+15, QString::number(number));
                    number--;
                }
            }
            else{painter.drawLine(x, 0, x, height());}
        }

        for (int y = 0; y < height(); y += cellSize){
            if(((height()/cellSize)/2)*cellSize==y){
                painter.setPen(wideGridPen);
                painter.drawLine(0,y,width(),y);
                painter.setPen(gridPen);

                int number = -(width()/cellSize)/2;
                for(int x = 0; x < width(); x+=cellSize){
                    painter.drawText(x+5, y+15, QString::number(number));
                    number++;
                }
            }
            else{painter.drawLine(0, y, width(), y);}
        }
    }

    void drawPoints(QPainter& painter){
        painter.setPen(Qt::red);
        painter.setBrush(Qt::red);

        std::array<int,2> origo = {((width()/cellSize)/2), ((height()/cellSize)/2)};

        for (const std::array<float,2>& p : points) {
            QPoint point = QPoint((p[0]+origo[0])*cellSize,(-p[1]+origo[1])*cellSize);
            painter.drawEllipse(point, 5, 5);
        }
    }

    void drawOptimalPoint(QPainter& painter, std::array<float,2> optimal){
        painter.setPen(Qt::darkGreen);
        painter.setBrush(Qt::darkGreen);

        std::array<int,2> origo = {((width()/cellSize)/2), ((height()/cellSize)/2)};
        QPoint point = QPoint((optimalPoint[0]+origo[0])*cellSize, (-optimalPoint[1]+origo[1])*cellSize);

        painter.drawEllipse(point, 5, 5);
    }
};


/*
celfuggveny:
min |x-x1|+|x-x2|+|x-x3|+...

feltetel:
x>=legkisebb_ertek
x<= legnagyobb_ertek
*/


int main(int argc, char** argv)
{
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
    feltetelek.emplace_back(std::make_unique<Feltetel>(std::vector<Monom>{{5, "x1"}}, std::vector<Monom>{{20, "x2"}}));
    auto celf = std::make_unique<Celfuggveny>(Celfuggveny::Irany::Min, monom);

    auto lp = std::make_unique<LP>(feltetelek, celf);

    std::cout << std::string{*lp} << '\n';

    QApplication app(argc, argv);
    /*QLabel label{"Hello world"};
    label.setMargin(20);
    label.show();*/
    UI ui;
    ui.show();

    return app.exec();
}
