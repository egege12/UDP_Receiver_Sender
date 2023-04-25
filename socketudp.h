
#ifndef SOCKETUDP_H
#define SOCKETUDP_H


#include <QObject>
#include "dataSendUDP.h"
#include "dataReceiveUDP.h"

class socketUDP : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString socketType READ socketType WRITE setsocketType NOTIFY socketTypeChanged)
    Q_PROPERTY(QString addressIP READ addressIP WRITE setAddressIP NOTIFY addressIPChanged)
    Q_PROPERTY(QString addressPORT READ addressPORT WRITE setAddressPORT NOTIFY addressPORTChanged)
    Q_PROPERTY(bool socketBind READ socketBind WRITE setSocketBind NOTIFY socketBindChanged)
public:
    explicit socketUDP(QObject *parent = nullptr);

    QString socketType() const;
    void setsocketType(const QString &newSocketType);

    QString addressIP() const;
    void setAddressIP(const QString &newAddressIP);

    QString addressPORT() const;
    void setAddressPORT(const QString &newAddressPORT);

    bool socketBind() const;
    void setsocketBind(bool newSocketBind);
    dataSendUDP *dataPtr() const;

public slots:
    void sendTheDatagram();
    void readPendingDatagrams();

    bool doBindSocket();
signals:

    void nameChanged();

    void socketTypeChanged();
    void addressIPChanged();

    void addressPORTChanged();

    void socketBindChanged();

    void dataPtrChanged();

private:
    QString m_socketType;
    QString m_addressIP;
    QString m_addressPORT;
    bool m_socketBind;

    dataReceiveUDP *dataReceivePtr;
    dataSendUDP *dataSendPtr;
};

#endif // SOCKETUDP_H
