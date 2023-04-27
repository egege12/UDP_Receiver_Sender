
#ifndef SOCKETUDP_H
#define SOCKETUDP_H


#include "dataSendUDP.h"
#include <QObject>
#include <QUdpSocket>
#include <QByteArray>
class socketUDP : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString socketType READ socketType WRITE setsocketType NOTIFY socketTypeChanged)
    Q_PROPERTY(QString addressIP READ addressIP WRITE setAddressIP NOTIFY addressIPChanged)
    Q_PROPERTY(QString addressPORT READ addressPORT WRITE setAddressPORT NOTIFY addressPORTChanged)

public:
    explicit socketUDP(QObject *parent = nullptr ,QString addressIP = "" , QString addressPORT = "", QString socketType = "Receive" );

    QString socketType() const;
    void setsocketType(const QString &newSocketType);

    QString addressIP() const;
    void setAddressIP(const QString &newAddressIP);

    QString addressPORT() const;
    void setAddressPORT(const QString &newAddressPORT);


public slots:
    void sendTheDatagram();
    void readPendingDatagrams();

signals:

    void nameChanged();
    void socketTypeChanged();
    void addressIPChanged();
    void addressPORTChanged();
    void dataPtrChanged();

private:
    QString m_socketType;
    QString m_addressIP;
    QString m_addressPORT;
    bool m_socketBind;

    QUdpSocket *socketUdp;

};

#endif // SOCKETUDP_H
