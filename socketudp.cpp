
#include "socketudp.h"

socketUDP::socketUDP(QObject *parent ,QString addressIP  , QString addressPORT , QString socketType )
    : QObject{parent}
{
    if(addressIP !=""){
        setAddressIP(addressIP);
    }
    if(addressPORT !=""){
        setAddressPORT(addressPORT);
    }
    if(socketType !=""){
        setsocketType(socketType);
    }
    if(this->socketType() == "receive"){
        socketUdp = new QUdpSocket(this);
    }else if (this->socketType()=="transmit"){
        socketUdp = new QUdpSocket(this);
    }else if (this->socketType()=="bidirectional"){
        socketUdp = new QUdpSocket(this);
    }

}


QString socketUDP::socketType() const
{
    return m_socketType;
}

void socketUDP::setsocketType(const QString &newSocketType)
{
    if (m_socketType == newSocketType)
        return;
    m_socketType = newSocketType;
    emit socketTypeChanged();
}

QString socketUDP::addressIP() const
{
    return m_addressIP;
}

void socketUDP::setAddressIP(const QString &newAddressIP)
{
    if (m_addressIP == newAddressIP)
        return;
    m_addressIP = newAddressIP;
    emit addressIPChanged();
}

QString socketUDP::addressPORT() const
{
    return m_addressPORT;
}

void socketUDP::setAddressPORT(const QString &newAddressPORT)
{
    if (m_addressPORT == newAddressPORT)
        return;
    m_addressPORT = newAddressPORT;
    emit addressPORTChanged();
}

