#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("../AlarmApplication/checkmark.png");
    QPixmap pix1("../AlarmApplication/redexclamation.png");
    ui->label_3->setPixmap(pix);
    ui->label_4->setPixmap(pix1);
    connect(&network, SIGNAL(dataReadyRead(QByteArray)), this, SLOT(dataTransfer(QByteArray)));

    //This is the a link to my RESTful API I was using for testing
    network.makeRequest("http://localhost:3000/alarms");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::retrieveData(QString json) {
    QStringList objects = json.split(QString("},"));
    int activeAlarms = objects.size();
    for (int i = 0; i < objects.size(); i++) {
        if (QString(objects[i].toStdString().substr(objects[i].indexOf("\"isActive\":") + 11, 4).c_str()) != "true") {
            activeAlarms--;
            continue;
        }
        int endId = objects[i].indexOf(",\"timestamp\"") - 10 - objects[i].indexOf("\"alarmId\":");
        //QString debugString = "";
        int endName = objects[i].indexOf("\",\"isActive\":") - 13 - objects[i].indexOf("\"alarmName\":\"");
        //ui->listWidget->addItem(debugString.setNum(endId));
        //std::cout << endId << " " << endName;
        QString alarmId = QString(objects[i].toStdString().substr(objects[i].indexOf("\"alarmId\":") + 10, endId).c_str());
        QString alarmName = QString(objects[i].toStdString().substr(objects[i].indexOf("\"alarmName\":\"") + 13, endName).c_str());
        ui->listWidget->addItem(alarmId + "   " + alarmName);
    }
    QString itemCount = "";
    itemCount.setNum(activeAlarms);
    if (activeAlarms > 0) {
        //ui->label_2->setStyleSheet("QLabel { background-color : white; color : red; }");
        ui->label_2->setStyleSheet("QLabel { color : red; }");
        ui->label->setStyleSheet("QLabel { color : red; }");
        ui->listWidget->setStyleSheet("QListWidget { background-color : red; color : black; }");
        ui->label_4->setVisible(true);
        ui->label_3->setVisible(false);
    }
    else {
        //ui->label_2->setStyleSheet("QLabel { background-color : white; color : green; }");
        ui->label_2->setStyleSheet("QLabel { color : green; }");
        ui->label->setStyleSheet("QLabel { color : green; }");
        ui->listWidget->setStyleSheet("QListWidget { background-color : white; color : black; }");
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(false);
    }
    ui->label_2->setText(itemCount);
}

void MainWindow::dataTransfer(QByteArray data) {
    QString dataString;
    dataString = data;
    ui->listWidget->clear();
    retrieveData(dataString);
}

void MainWindow::on_pushButton_clicked()
{
    //This is the a link to my RESTful API I was using for testing
    network.makeRequest("http://localhost:3000/alarms");
}
