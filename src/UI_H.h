#ifndef UI_H
#define UI_H

#include <vector>
#include <array>
#include <QApplication>
#include <QLabel>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>


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

#endif
