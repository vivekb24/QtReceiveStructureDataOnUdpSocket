#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    recv_socket = new QUdpSocket(this);
    recv_socket->bind(4444);
    connect(recv_socket,SIGNAL(readyRead()),this,SLOT(receivedData()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receivedData()
{
    QByteArray dataToRece;
    while (recv_socket->hasPendingDatagrams())
    {
        dataToRece.resize(recv_socket->pendingDatagramSize());
        recv_socket->readDatagram(dataToRece.data(),dataToRece.size(),&senderip,&senderportno);
        memcpy((char*)&r_Data,dataToRece.data(),sizeof(r_Data));

        qDebug()<<"readData : "<<sizeof (r_Data);

        if(r_Data.msgId==1){
            ui->label_msgId->setText("Msg Id Matched");
            ui->label_angle->setText(tr("%1").arg(QString::number(r_Data.angle).toDouble()));
            ui->label_speed->setText(tr("%1").arg(QString::number(r_Data.speed).toInt()));
            ui->label_range->setText(tr("%1").arg(QString::number(r_Data.range).toInt()));
        }
        else {
            qDebug()<<"ERROR : ";
        }
        qDebug()<<"Message From : "<<senderip.toString();
        qDebug()<<"Message port : "<<senderportno;
    }
}
