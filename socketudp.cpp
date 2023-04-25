
#include "socketudp.h"

socketUDP::socketUDP(QObject *parent)
    : QObject{parent}
{

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

bool socketUDP::socketBind() const
{
    return m_socketBind;
}

void socketUDP::setsocketBind(bool newSocketBind)
{
    if (m_socketBind == newSocketBind)
        return;
    m_socketBind = newSocketBind;
    emit socketBindChanged();
}
