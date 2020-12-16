#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QUdpSocket>
#include <QString>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void receivedData();
private:
    Ui::MainWindow *ui;
    QUdpSocket *recv_socket;
    QHostAddress senderip;
    quint16 senderportno;

    struct ProjData{
        int msgId;
        float angle;
        int speed;
        int range;
    }__attribute__((packed));
    ProjData r_Data;
};

#endif // MAINWINDOW_H
