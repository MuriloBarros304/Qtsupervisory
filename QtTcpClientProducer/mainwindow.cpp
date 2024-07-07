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
    socket = new QTcpSocket(this);
    connect(ui->pushButtonConnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpConnect()));

}

void MainWindow::tcpConnect() {
    socket->connectToHost(getIP(),1234);
    if(socket->waitForConnected(3000)){
        ui->textBrowserCommand->append("Connected \r\n");
        qDebug() << "Connected";
    }
    else{
        qDebug() << "Disconnected";
    }
}

void MainWindow::putData() {
    timer = ui->horizontalSliderTiming->value();
    timer = startTimer((timer)*1000);
}

MainWindow::~MainWindow(){
    delete socket;
    delete ui;
}

QString MainWindow::getIP() {
    QString ip;
    ip = ui->lineEditIP->text();
    return ip;
}

void MainWindow::timerEvent(QTimerEvent *t) {
    QDateTime datetime;
    QString str;
    qint64 msecdate;
    int max, min;

    max = ui->horizontalSliderMax->value();
    min = ui->horizontalSliderMin->value();

    timer = ui->horizontalSliderTiming->value();
    timer = startTimer((timer)*1000);

    if(socket->state()== QAbstractSocket::ConnectedState){

        msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
        str = "set "+ QString::number(msecdate) + " " +
              QString::number(rand()%(max - min) + min)+"\r\n";
        ui->textBrowserCommand->append(str);
        qDebug() << str;

        qDebug() << socket->write(str.toStdString().c_str())
                 << " bytes written";
        if(socket->waitForBytesWritten(3000)){
            qDebug() << "wrote";
        }
    }
}

