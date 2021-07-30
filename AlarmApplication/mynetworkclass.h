#ifndef MYNETWORKCLASS_H
#define MYNETWORKCLASS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
class MyNetworkClass : public QObject
{
    Q_OBJECT
public:
    explicit MyNetworkClass(QObject *parent = nullptr);
    void makeRequest(QString endpointRequest);
signals:
    void dataReadyRead(QByteArray);
public slots:
    void readRead(QNetworkReply *reply);
private:
    QNetworkAccessManager *qnam = new QNetworkAccessManager(this);
};

#endif // MYNETWORKCLASS_H
