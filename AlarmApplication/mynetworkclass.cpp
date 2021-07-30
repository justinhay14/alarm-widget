#include "mynetworkclass.h"
#include <QDebug>
MyNetworkClass::MyNetworkClass(QObject *parent) : QObject(parent)
{
    connect(qnam, SIGNAL(finished(QNetworkReply *)), this, SLOT(readRead(QNetworkReply *)));
}

void MyNetworkClass::makeRequest(QString endpointRequest) {
    qnam->get(QNetworkRequest(QUrl(endpointRequest)));
}

void MyNetworkClass::readRead(QNetworkReply *reply) {
    QByteArray myData;
    myData = reply->readAll();
    qDebug() << myData;
    emit(dataReadyRead(myData));
}
