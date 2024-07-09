#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButtonConnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpConnect()));

    connect(ui->pushButtonStop,
            SIGNAL(clicked(bool)),
            this,
            SLOT(stopTiming()));

    connect(ui->pushButtonStart,
            SIGNAL(clicked(bool)),
            this,
            SLOT(startTiming()));

    connect(ui->pushButtonDisconnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpDisconnect()));

    connect(ui->pushButtonUpdate,
            SIGNAL(clicked(bool)),
            this,
            SLOT(updateList()));

    ui->horizontalSliderTiming->setValue(8);
    pastIP = getIP();
    ui->listWidgetIPs->addItem(getIP());
}

void MainWindow::tcpConnect() {
    socket = new QTcpSocket(this);
    socket->connectToHost(getIP(),1234);
    if(socket->waitForConnected(3000)) {
        qDebug() << "Connected";
    }
    else {
        qDebug() << "Disconnected";
    }
}

void MainWindow::tcpDisconnect() {
    if(socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnectFromHost();
        qDebug() << "Disconnected\r\n";
    }
    if(timerIsRunning)
        killTimer(timer);
}

QString MainWindow::getIP() {
    return ui->lineEditIP->text();;
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
    getData();
}

void MainWindow::updateList() {
    if(pastIP != getIP()) {
        ui->listWidgetIPs->addItem(getIP());
        pastIP = getIP();
    }
}

void MainWindow::getData(){
    QString str;
    QByteArray array;
    QStringList list;
    qint64 thetime;
    qDebug() << "to get data...";
    if(socket->state() == QAbstractSocket::ConnectedState){
        if(socket->isOpen()){
            qDebug() << "reading...";
            socket->write("get ");
            socket->write(getIP().toLocal8Bit());
            socket->write(" 5\r\n");
            socket->waitForBytesWritten();
            socket->waitForReadyRead();
            qDebug() << socket->bytesAvailable();
            while(socket->bytesAvailable()){
                str = socket->readLine().replace("\n","").replace("\r","");
                list = str.split(" ");
                if(list.size() == 2){
                    bool ok;
                    str = list.at(0);
                    thetime = str.toLongLong(&ok);
                    str = list.at(1);
                    qDebug() << thetime << ": " << str; // tempo e número
                }
            }
        }
    }
}


MainWindow::~MainWindow() {
  delete socket;
  delete ui;
}
