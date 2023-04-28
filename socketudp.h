
#ifndef SOCKETUDP_H
#define SOCKETUDP_H


#include "comUdpData.h"
#include <QObject>
#include <QUdpSocket>
#include <QByteArray>
#include <QTimer>
#include <QNetworkDatagram>
class socketUDP : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString socketType READ socketType WRITE setsocketType NOTIFY socketTypeChanged)
    Q_PROPERTY(QString addressIP READ addressIP WRITE setAddressIP NOTIFY addressIPChanged)
    Q_PROPERTY(QString addressPORT READ addressPORT WRITE setAddressPORT NOTIFY addressPORTChanged)

public:
    explicit socketUDP(QObject *parent = nullptr ,QString pcIP = "10.100.30.202",QString addressIP = "" , QString addressPORT = "", QString socketType = "Receive" , const comUdpData* dataReceive= nullptr,const comUdpData* dataSend= nullptr);

    QString socketType() const;
    void setsocketType(const QString &newSocketType);

    QString addressIP() const;
    void setAddressIP(const QString &newAddressIP);

    QString addressPORT() const;
    void setAddressPORT(const QString &newAddressPORT);

    void processReceiveDatagram(QNetworkDatagram* datagram);

    QByteArray processSendDatagram();

public slots:
    void sendTheDatagram();
    void readPendingDatagrams();
    void startBroadcasting();
    void stopBroadcasting();

signals:

    void nameChanged();
    void socketTypeChanged();
    void addressIPChanged();
    void addressPORTChanged();
    void dataPtrChanged();
    void sendDatagram();

private:
    QString m_socketType;
    QString m_addressIP;
    QString m_addressPORT;
    bool m_socketBind;

    QUdpSocket *socketUdp;
    QTimer timer;
    QTimer timerTimeoutChecker;

    const comUdpData* receiveData;
    const comUdpData* sendData;

};

#endif // SOCKETUDP_H
