#include "plotter.h"
#include <QPainter>
#include <QBrush>
#include <QPen>

Plotter::Plotter(QWidget *parent)
    : QWidget{parent}
{}

void Plotter::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QBrush brush;
    QPen pen;

    brush.setColor(QColor(255,255,100));
    brush.setStyle(Qt::SolidPattern);

    pen.setWidth(2);

    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawRect(0,0,width(), height());
    pen.setColor(QColor(100,0,255));

    //painter.drawLine(

}

int Plotter::getX(MainWindow &x, int index) {

}

int Plotter::getY(MainWindow &y, int index) {

}
