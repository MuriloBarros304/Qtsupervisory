#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <vector>
#include "mainwindow.h"

class Plotter : public QWidget {
    Q_OBJECT
public:
    explicit Plotter(QWidget *parent = nullptr);

    int getX(MainWindow &mainWindow, int index);
    int getY(MainWindow &mainWindow, int index);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // PLOTTER_H
