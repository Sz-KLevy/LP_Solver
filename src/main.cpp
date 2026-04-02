#include <iostream>
#include <vector>
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


class UI : public QWidget{
public:
    int windowSize[2] = {500, 500};
    int cellSize = 50;
    std::vector<QPoint> points;
    QPoint optimalPoint;



    UI(QWidget *parent = nullptr) : QWidget(parent){
        resize(windowSize[0], windowSize[1]);
        optimalPoint = QPoint(windowSize[0]/2, windowSize[1]/2);
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

        points.push_back(QPoint(click.x(), click.y()));

        int intOptimalPoint[2] = {100, 100}; //this is where the UI asks for the position of the optimal point
        optimalPoint = QPoint(intOptimalPoint[0], intOptimalPoint[1]);

        update(); //repaints
    }


    void drawGrid(QPainter& painter, int cellSize){
        painter.setPen(Qt::black);

        for (int x = 0; x < width(); x += cellSize)
            painter.drawLine(x, 0, x, height());

        for (int y = 0; y < height(); y += cellSize)
            painter.drawLine(0, y, width(), y);
    }

    void drawPoints(QPainter& painter){
        painter.setPen(Qt::red);
        painter.setBrush(Qt::red);

        for (const QPoint& p : points) {
            painter.drawEllipse(p, 5, 5);
        }
    }

    void drawOptimalPoint(QPainter& painter, QPoint optimal){
        painter.setPen(Qt::darkGreen);
        painter.setBrush(Qt::darkGreen);
        painter.drawEllipse(optimal, 5, 5);
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
    auto celf = std::make_unique<Celfuggveny>(Celfuggveny::Irany::Min, monom);

    celf->show();
    std::cout << '\n';

    QApplication app(argc, argv);
    /*QLabel label{"Hello world"};
    label.setMargin(20);
    label.show();*/
    UI ui;
    ui.show();

    return app.exec();
}
