#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::vector<qint64> x;
    std::vector<int> y;

public slots:
    void tcpConnect();
    void tcpDisconnect();
    void getData();
    QString getIP();
    void startTiming();
    void stopTiming();
    void timerEvent(QTimerEvent *t);
    void updateList();
    void updateGetDataVisibility();
private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    bool timerIsRunning = false;
    int timer;
    QString pastIP;
    std::vector<QString> ips;
};

#endif // MAINWINDOW_H
