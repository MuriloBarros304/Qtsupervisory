#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>

class Plotter : public QWidget {
    Q_OBJECT
public:
    explicit Plotter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    QList<int> points;
signals:

public slots:
    void updatePoints(QList<int> newPoints);
    int getMax();
    int getMin();
};

#endif // PLOTTER_H
