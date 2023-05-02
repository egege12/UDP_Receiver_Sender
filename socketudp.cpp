
#include "socketudp.h"
#include "qforeach.h"

socketUDP::socketUDP(QObject *parent , QString pcIP, QString addressIP  , QString addressPORT , QString socketType , int initCylce,  comUdpData* dataReceive, comUdpData* dataSend)
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
    if(pcIP !=""){
        setPCIP(pcIP);
    }
    if(initCylce != 0 ){
        setInitCycle(initCylce);
    }
    this->receiveData = dataReceive;
    this->sendData = dataSend;
}

socketUDP::~socketUDP()
{
    this->receiveData = nullptr;
    this->sendData = nullptr;
    delete socketUdp;
    delete this->timer;
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
    QByteArray packData = datagram->data();

    qInfo()<<QString::number(packData[0]);
    qInfo()<<QString::number(packData[1]);
    qInfo()<<QString::number(packData[2]);
    qInfo()<<QString::number(packData[3]);
    qInfo()<<QString::number(packData[4]);
    /*
    QString ID0 =  QString::number(combineBytes(subarray(packData,0,1)));


    for(comUdpData::paramSignal* signal : receiveData->qm_comParam.value(ID0)){
        receiveData->qm_data[signal->m_name]= QString::number(this->getBetween(combineBytes(subarray(packData,2,9)),signal->m_startBit,signal->m_length));
    }
    QString ID1 =  QString::number(combineBytes(subarray(packData,10,11)));
    for(comUdpData::paramSignal* signal : receiveData->qm_comParam.value(ID1)){
        receiveData->qm_data[signal->m_name]= QString::number(this->getBetween(combineBytes(subarray(packData,12,19)),signal->m_startBit,signal->m_length));
    }
    qInfo()<<ID1;
    QString ID2 =  QString::number(combineBytes(subarray(packData,20,21)));
    for(comUdpData::paramSignal* signal : receiveData->qm_comParam.value(ID2)){
        receiveData->qm_data[signal->m_name]= QString::number(this->getBetween(combineBytes(subarray(packData,22,29)),signal->m_startBit,signal->m_length));
    }
    QString ID3 =  QString::number(combineBytes(subarray(packData,30,31)));
    for(comUdpData::paramSignal* signal : receiveData->qm_comParam.value(ID3)){
        receiveData->qm_data[signal->m_name]= QString::number(this->getBetween(combineBytes(subarray(packData,32,39)),signal->m_startBit,signal->m_length));
    }*/
        emit dataChanged();
}

QByteArray socketUDP::processSendDatagram()
{
    QByteArray data;
    data.append("600 ");
    data.append("100");
    data.append("23223");
    return data;
}
QString socketUDP::PCIP() const
{
    return m_PCIP;
}

void socketUDP::setPCIP(const QString &newPCIP)
{
    if (m_PCIP == newPCIP)
        return;
    m_PCIP = newPCIP;
    emit PCIPChanged();
}

int socketUDP::initCycle() const
{
    return m_initCycle;
}

void socketUDP::setInitCycle(int newInitCycle)
{
    if (m_initCycle == newInitCycle)
        return;
    m_initCycle = newInitCycle;
    emit initCycleChanged();
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
            timer->stop();
            timer->start(this->initCycle()*20);
        }
        qInfo()<<"Data received";
        QNetworkDatagram datagram = socketUdp->receiveDatagram();
        processReceiveDatagram(&datagram);
        emit sendDatagram();
    }

}

void socketUDP::startUdpCom()
{
    if(this->socketType() == "receive"){
        socketUdp = new QUdpSocket(this);
        socketUdp -> bind((QHostAddress::AnyIPv4),this->addressPORT().toInt(),QUdpSocket::ShareAddress);
        if(this->m_PCIP != "broadcast"){
            socketUdp -> joinMulticastGroup(QHostAddress(this->m_PCIP));
        }
    }else if (this->socketType()=="transmit"){
        socketUdp = new QUdpSocket(this);
        socketUdp-> bind(this->addressPORT().toInt());
    }else if (this->socketType()=="bidirectional"){
        socketUdp = new QUdpSocket(this);
        socketUdp -> bind((QHostAddress::AnyIPv4),this->addressPORT().toInt(),QUdpSocket::ShareAddress);
    }
    this->timer = new QTimer(this);
    QObject::connect(socketUdp,&QUdpSocket::readyRead,this,&socketUDP::readPendingDatagrams,Qt::AutoConnection);
    QObject::connect(this,&socketUDP::sendDatagram,this,&socketUDP::sendTheDatagram,Qt::AutoConnection);
    QObject::connect(timer,&QTimer::timeout,this,&socketUDP::sendTheDatagram,Qt::AutoConnection);
    QObject::connect(this,&socketUDP::dataChanged,receiveData,&comUdpData::dataChangeNotify,Qt::AutoConnection);
    timer->start(this->initCycle());
}

void socketUDP::stopUdpCom()
{
    timer->stop();
    QObject::disconnect(socketUdp,&QUdpSocket::readyRead,this,&socketUDP::readPendingDatagrams);
    QObject::disconnect(this,&socketUDP::sendDatagram,this,&socketUDP::sendTheDatagram);
    QObject::disconnect(timer,&QTimer::timeout,this,&socketUDP::sendTheDatagram);

}
quint64 socketUDP::getBetween(uint64_t rawData, unsigned int startBit, unsigned int length)
{
    quint64 mask = (1ULL << length) - 1ULL;
    quint64 data = (rawData >> startBit) & mask;

    return data;
}
quint64 socketUDP::combineBytes(const QByteArray &data)
{
    Q_ASSERT(data.size() <= 8);

    quint64 result = 0;
    for (int i = 0; i < data.size(); i++) {
        result |= (quint64)(data[i] & 0xFF) << (i * data.size());
    }
    return result;
}
QByteArray socketUDP::subarray(const QByteArray& data, unsigned int startIndex, unsigned int endIndex)
{
    QByteArray result(endIndex - startIndex + 1, 0);
    for (int i = startIndex; i <= endIndex; i++)
    {
        qInfo()<<i;
        result[i - startIndex] = data[i];
        qInfo()<<QString::number(data[i]);
    }
    return result;
}
