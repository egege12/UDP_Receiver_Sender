
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
    Q_PROPERTY(QString PCIP READ PCIP WRITE setPCIP NOTIFY PCIPChanged)
    Q_PROPERTY(int initCycle READ initCycle WRITE setInitCycle NOTIFY initCycleChanged)
public:
    explicit socketUDP(QObject *parent = nullptr ,QString pcIP = "10.100.30.202",QString addressIP = "" , QString addressPORT = "", QString socketType = "Receive" , int initCylce = 0, comUdpData* dataReceive= nullptr, comUdpData* dataSend= nullptr);
    ~socketUDP();
    QString socketType() const;
    void setsocketType(const QString &newSocketType);

    QString addressIP() const;
    void setAddressIP(const QString &newAddressIP);

    QString addressPORT() const;
    void setAddressPORT(const QString &newAddressPORT);

    void processReceiveDatagram(QNetworkDatagram* datagram);

    QByteArray processSendDatagram();

    QString PCIP() const;
    void setPCIP(const QString &newPCIP);

    int initCycle() const;
    void setInitCycle(int newInitCycle);

public slots:
    void sendTheDatagram();
    void readPendingDatagrams();
    void startUdpCom();
    void stopUdpCom();

signals:

    void nameChanged();
    void socketTypeChanged();
    void addressIPChanged();
    void addressPORTChanged();
    void dataPtrChanged();
    void sendDatagram();
    void PCIPChanged();
    void initCycleChanged();
    void dataChanged();

private:
    QString m_socketType;
    QString m_addressIP;
    QString m_addressPORT;
    bool m_socketBind;
    QMap<QString,QList<comUdpData::paramSignal*>>::iterator sendIndex;
    QUdpSocket *socketUdp;
    QTimer *timer;
    QTimer timerTimeoutChecker;
    comUdpData* receiveData;
    comUdpData* sendData;

    QString m_PCIP;
    int m_initCycle;
    quint64 getBetween(uint64_t rawData, unsigned int startBit, unsigned int length);
    quint64 combineBytes(const QByteArray &data);
    QByteArray subarray(const QByteArray &data, unsigned int startIndex, unsigned int endIndex);
    QString takeResOffset(QString value,double resolution, double offset);

    quint64 setBetween(quint64 rawData, unsigned int startBit, unsigned int length);
    QByteArray makeSubArray(const quint64 &data);
    QString makeResOffset(QString value,double resolution, double offset);

};

#endif // SOCKETUDP_H
