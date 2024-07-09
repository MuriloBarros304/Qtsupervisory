#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QLabel>
#include <QLineEdit>
#include <QLCDNumber>
#include <QTextBrowser>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->pushButtonConnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpConnect()));

    connect(ui->pushButtonStopTiming,
            SIGNAL(clicked(bool)),
            this,
            SLOT(stopTiming()));

    connect(ui->pushButtonStartTiming,
            SIGNAL(clicked(bool)),
            this,
            SLOT(startTiming()));

    connect(ui->pushButtonDisconnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpDisconnect()));

    ui->horizontalSliderMax->setValue(35);
    ui->horizontalSliderTiming->setValue(3);
}

void MainWindow::tcpConnect() {
    socket = new QTcpSocket(this);
    socket->connectToHost(getIP(),1234);
    if(socket->waitForConnected(3000)){
        ui->textBrowserCommand->append("Connected\r\n");
        ui->labelStatus->setText("Connected");
    }
    else{
        ui->textBrowserCommand->append("Failed\r\n");
    }
}



void MainWindow::startTiming() {
    timer = ui->horizontalSliderTiming->value();
    timer = startTimer((timer)*1000);
    timerIsRunning = true;
}

void MainWindow::stopTiming() {
    killTimer(timer);
    timerIsRunning = false;
}

void MainWindow::timerEvent(QTimerEvent *t) {
    putData();
}

MainWindow::~MainWindow(){
    delete socket;
    delete ui;
}

QString MainWindow::getIP() {
    return ui->lineEditIP->text();;
}

void MainWindow::putData() {
    QDateTime datetime;
    QString str;
    qint64 msecdate;
    int max, min;

    max = ui->horizontalSliderMax->value();
    min = ui->horizontalSliderMin->value();

    if(min>max) {
        ui->textBrowserCommand->append("Invalid range\r\n");
        killTimer(timer);
        timerIsRunning = false;
    }
    if(socket->state() == QAbstractSocket::ConnectedState){
        msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
        str = "set "+ QString::number(msecdate) + " " +
            QString::number(rand()%(max - min) + min)+"\r\n";
        ui->textBrowserCommand->append(str);
        }
    socket->write(str.toStdString().c_str());
}

