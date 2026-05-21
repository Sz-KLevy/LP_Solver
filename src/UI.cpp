#include "UI.h"



UI::UI(QWidget *parent) : QWidget(parent){
    resize(windowSize[0], windowSize[1]);
    optimalPoint={0.0,0.0};
}

std::vector<std::array<float,2>> UI::getPoints(){
    return points;
}


void UI::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    drawGrid(painter, cellSize);
    drawPoints(painter);
    drawOptimalPoint(painter, optimalPoint);
}

void UI::mousePressEvent(QMouseEvent* event) {
    QPoint click = event->pos();
    int origo[2] = {((width()/cellSize)/2)*cellSize, ((height()/cellSize)/2)*cellSize};

    points.push_back({(float)(click.x()-origo[0])/cellSize, (float)-(click.y()-origo[1])/cellSize});
    point_added.emit_cords(points.back());

    update(); //repaints
}


void UI::drawGrid(QPainter& painter, int cellSize){
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

void UI::drawPoints(QPainter& painter){
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);

    std::array<int,2> origo = {((width()/cellSize)/2), ((height()/cellSize)/2)};

    for (const std::array<float,2>& p : points) {
        QPoint point = QPoint((p[0]+origo[0])*cellSize,(-p[1]+origo[1])*cellSize);
        painter.drawEllipse(point, 5, 5);
    }
}

void UI::drawOptimalPoint(QPainter& painter, std::array<float,2> optimal){
    painter.setPen(Qt::darkGreen);
    painter.setBrush(Qt::darkGreen);

    std::array<int,2> origo = {((width()/cellSize)/2), ((height()/cellSize)/2)};
    QPoint point = QPoint((optimalPoint[0]+origo[0])*cellSize, (-optimalPoint[1]+origo[1])*cellSize);

    painter.drawEllipse(point, 5, 5);
}

