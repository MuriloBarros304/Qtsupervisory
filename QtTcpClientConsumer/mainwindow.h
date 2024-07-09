#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void tcpConnect();
    void tcpDisconnect();
    void getData();
    QString getIP();
    void startTiming();
    void stopTiming();
    void timerEvent(QTimerEvent *t);

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    bool timerIsRunning = false;
    int timer;
};

#endif // MAINWINDOW_H
