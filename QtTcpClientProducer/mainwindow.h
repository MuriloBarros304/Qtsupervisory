#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
  
public slots:
    void putData();
    void tcpConnect();
    void tcpDisconnect();
    void startTiming();
    void stopTiming();
    QString getIP();
    void timerEvent(QTimerEvent *t);

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    int timer;
    bool timerIsRunning = false;
};

#endif // MAINWINDOW_H
