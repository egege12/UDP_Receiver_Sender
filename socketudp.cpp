
#include "socketudp.h"

socketUDP::socketUDP(QObject *parent , QString pcIP, QString addressIP  , QString addressPORT , QString socketType ,  const comUdpData* dataReceive,const comUdpData* dataSend)
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
        socketUdp -> bind((QHostAddress::AnyIPv4),this->addressPORT().toInt(),QUdpSocket::ShareAddress);
        if(pcIP != "broadcast"){
            socketUdp -> joinMulticastGroup(QHostAddress(pcIP));
        }
        QObject::connect(socketUdp,&QUdpSocket::readyRead,this,&socketUDP::readPendingDatagrams);
    }else if (this->socketType()=="transmit"){
        socketUdp = new QUdpSocket(this);
        socketUdp-> bind(this->addressPORT().toInt());
        QObject::connect(&timer,&QTimer::timeout,this,&socketUDP::sendTheDatagram);
    }else if (this->socketType()=="bidirectional"){
        socketUdp = new QUdpSocket(this);
        socketUdp -> bind((QHostAddress::AnyIPv4),this->addressPORT().toInt(),QUdpSocket::ShareAddress);

        QObject::connect(socketUdp,&QUdpSocket::readyRead,this,&socketUDP::readPendingDatagrams);
        QObject::connect(this,&socketUDP::sendDatagram,this,&socketUDP::sendTheDatagram);
        QObject::connect(&timer,&QTimer::timeout,this,&socketUDP::sendTheDatagram);
    }

    this->receiveData = dataReceive;
    this->sendData = dataSend;


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

void socketUDP::processReceiveDatagram(QNetworkDatagram *datagram)
{

}

QByteArray socketUDP::processSendDatagram()
{

}

void socketUDP::sendTheDatagram()
{
    if(this->addressIP() == "broadcast"){
        socketUdp ->writeDatagram(processSendDatagram(),QHostAddress::Broadcast,this->addressPORT().toInt());
    }else{
        socketUdp ->writeDatagram(processSendDatagram(),QHostAddress(this->addressIP()),this->addressPORT().toInt());
    }
    qInfo()<<"Data sent";
}

void socketUDP::readPendingDatagrams()
{
    while (socketUdp->hasPendingDatagrams()) {
        if(this->socketType()=="bidirectional"){
            timer.stop();
            timer.start(1000);
        }
        qInfo()<<"Data received";
        QNetworkDatagram datagram = socketUdp->receiveDatagram();
        processReceiveDatagram(&datagram);
        emit sendDatagram();
    }

}

void socketUDP::startBroadcasting()
{
    timer.start(100);
}

void socketUDP::stopBroadcasting()
{
    timer.stop();
}

