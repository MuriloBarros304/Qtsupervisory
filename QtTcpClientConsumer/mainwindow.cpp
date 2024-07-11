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

    connect(ui->listWidgetIPs,
            SIGNAL(itemSelectionChanged()),
            this,
            SLOT(updateGetDataVisibility()));

    ui->horizontalSliderTiming->setValue(8);
    pastIP = getIP();
    ui->getDataTiming->setVisible(false);
    ui->listWidgetIPs->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->listWidgetIPs->setSelectionMode(QAbstractItemView::SingleSelection);
}

void MainWindow::tcpConnect() {
    socket = new QTcpSocket(this);
    socket->connectToHost(getIP(),1234);
    if(socket->waitForConnected(3000)) {
        qDebug() << "Connected";
        ips.push_back(getIP());
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
    auto selectedItems = ui->listWidgetIPs->selectedItems();

    for (auto it = ips.begin(); it != ips.end(); ) {
        bool eraseItem = false;
        for (auto &item : selectedItems) {
            if (*it == item->text()) {
                eraseItem = true;
                break;
            }
        }
        if (eraseItem) {
            it = ips.erase(it); // Apaga o item e atualiza o iterador
        } else {
            ++it; // Avança o iterador
        }
    }
}

QString MainWindow::getIP() {
    return ui->lineEditIP->text();
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
    repaint();
}

void MainWindow::updateList() {
    QString currentIP = getIP();
    if (pastIP != currentIP) {
        for (const auto &ip : ips) {
            // Verifica se o item já está na lista antes de adicionar
            bool itemExists = false;
            for (int i = 0; i < ui->listWidgetIPs->count(); ++i) {
                if (ui->listWidgetIPs->item(i)->text() == ip) {
                    itemExists = true;
                    break;
                }
            }
            if (!itemExists) {
                ui->listWidgetIPs->addItem(ip);
            }
        }
        // Atualiza o pastIP com o novo IP
        pastIP = currentIP;
    }
}


void MainWindow::updateGetDataVisibility()
{
    if (!ui->listWidgetIPs->selectedItems().isEmpty()) {
        ui->getDataTiming->setVisible(true);
    } else {
        ui->getDataTiming->setVisible(false);
    }
}

void MainWindow::getData(){
    QString str;
    QByteArray array;
    QStringList list;
    qint64 thetime;
    qDebug() << "to get data...";
    str = ui->listWidgetIPs->selectedItems()[0]->text();
    array = str.toLocal8Bit();
    if(socket->state() == QAbstractSocket::ConnectedState){
        if(socket->isOpen()){
            qDebug() << "reading...";
            socket->write("get ");
            socket->write(array);
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
                    x.push_back(thetime); // armazenar tempo no eixo x
                    thetime = str.toLongLong(&ok);
                    str = list.at(1);
                    y.push_back(str.toInt()); // armazenar valor no eixo y
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
