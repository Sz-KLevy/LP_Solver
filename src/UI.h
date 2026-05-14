#ifndef UI_H
#define UI_H

#include <vector>
#include <array>
#include <QApplication>
#include <QLabel>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include <QWidget>

#include <iostream>
#include <string>
#include <memory>
#include <format>

class UI : public QWidget{
public:
    int windowSize[2] = {500, 500};
    int cellSize = 50;
    std::vector<std::array<float,2>> points;
    std::array<float,2> optimalPoint;

    explicit UI(QWidget *parent = nullptr);
    std::vector<std::array<float,2>> getPoints();

private:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;
    void drawGrid(QPainter& painter, int cellSize);
    void drawPoints(QPainter& painter);
    void drawOptimalPoint(QPainter& painter, std::array<float,2> optimal);
};

#endif
