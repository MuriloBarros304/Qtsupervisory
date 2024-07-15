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

    painter.setRenderHint(QPainter::Antialiasing);
    int min, max;
    float y0, y1;

    brush.setColor(QColor(255, 255, 100));
    brush.setStyle(Qt::SolidPattern);
    pen.setWidth(2);
    painter.setBrush(brush);
    pen.setColor(QColor(255, 50, 50));
    painter.setPen(pen);
    painter.drawRect(1, 1, width()-2, height()-2);
    pen.setColor(QColor(100, 0, 255));
    painter.setPen(pen);
    min = getMin();
    max = getMax();

    for(int i = 1; i < points.length(); i++) {
        y0 = ((float)points.at(i-1)-min) / (max-min);
        y1 = ((float)points.at(i)-min) / ((max)-min);
        painter.drawLine(width()/(points.length()-1)*(i-1), height()-(y0*height()), width()/(points.length()-1)*(i), height()-(y1*height()));
    }
}

void Plotter::updatePoints(QList<int> newPoints) {
    points = newPoints;
    repaint();
}

int Plotter::getMax() {
    if (points.isEmpty()) {
        return 0;
    }
    int max = points.at(0);
    for(int i = 1; i < points.length(); i++) {
        if(points.at(i) > max) {
            max = points.at(i);
        }
    }
    qDebug() << "max: " << max;
    return max;
}

int Plotter::getMin() {
    if (points.isEmpty()) {
        return 0;
    }
    int min = points.at(0);
    for(int i = 1; i < points.length(); i++) {
        if(points.at(i) < min) {
            min = points.at(i);
        }
    }
    qDebug() << "min: " << min;
    return min;
}


