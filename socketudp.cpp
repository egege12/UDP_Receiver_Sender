
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

    sendIndex= this->sendData->qm_comParam.begin();
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

        if(packData.size()>9){
            QString ID0 =  QString::number(combineBytes(subarray(packData,0,1)));
            if(receiveData->qm_comParam.contains(ID0)){
                foreach(comUdpData::paramSignal* signal , receiveData->qm_comParam[ID0]){
                    receiveData->qm_data[signal->m_name]= takeResOffset(QString::number(this->getBetween(combineBytes(subarray(packData,2,9)),signal->m_startBit,signal->m_length)),signal->m_resolution,signal->m_offset);
                }
            }else{
                qInfo()<< "Data 0 not received, ID cant find";
            }
        }else{
            qInfo()<< "Data 0 not received, length is short";
        }
        if(packData.size()>19){
            QString ID1 =  QString::number(combineBytes(subarray(packData,10,11)));
            if(receiveData->qm_comParam.contains(ID1)){
                for(comUdpData::paramSignal* signal : receiveData->qm_comParam.value(ID1)){
                    receiveData->qm_data[signal->m_name]= takeResOffset(QString::number(this->getBetween(combineBytes(subarray(packData,12,19)),signal->m_startBit,signal->m_length)),signal->m_resolution,signal->m_offset);
                }
            }else{
                qInfo()<< "Data 1 not received, ID cant find";
            }
        }else{
            qInfo()<< "Data 1 not received, length is short";
        }
        if(packData.size()>29){
            QString ID2 =  QString::number(combineBytes(subarray(packData,20,21)));
            if(receiveData->qm_comParam.contains(ID2)){
                for(comUdpData::paramSignal* signal : receiveData->qm_comParam.value(ID2)){
                    receiveData->qm_data[signal->m_name]= takeResOffset(QString::number(this->getBetween(combineBytes(subarray(packData,22,29)),signal->m_startBit,signal->m_length)),signal->m_resolution,signal->m_offset);
                }
            }else{
                qInfo()<< "Data 2 not received, ID cant find";
            }
        }else{
            qInfo()<< "Data 2 not received, length is short";
        }
        if(packData.size()>39){
            QString ID3 =  QString::number(combineBytes(subarray(packData,30,31)));
            if(receiveData->qm_comParam.contains(ID3))
                for(comUdpData::paramSignal* signal : receiveData->qm_comParam.value(ID3)){
                    receiveData->qm_data[signal->m_name]= takeResOffset(QString::number(this->getBetween(combineBytes(subarray(packData,32,39)),signal->m_startBit,signal->m_length)),signal->m_resolution,signal->m_offset);
                }else{
                qInfo()<< "Data 3 not received, ID cant find";
            }
        }else{
            qInfo()<< "Data 3 not received, length is short";
        }
        emit dataChanged();

}

QByteArray socketUDP::processSendDatagram()
{
        QByteArray data;
        data.resize(40);
        QString ID0,ID1,ID2,ID3;
        //senddata ID0
        if(sendIndex != sendData->qm_comParam.end()){
            ID0= sendIndex.key();
            sendIndex++;
        }else{
            sendIndex=this->sendData->qm_comParam.begin();
            ID0= sendIndex.key();
        }



        if(sendIndex != sendData->qm_comParam.end()){
            ID1= sendIndex.key();
            sendIndex++;
        }else{
            sendIndex=this->sendData->qm_comParam.begin();
            ID1= sendIndex.key();
        }


        if(sendIndex != sendData->qm_comParam.end()){
            ID2= sendIndex.key();
            sendIndex++;
        }else{
            sendIndex=this->sendData->qm_comParam.begin();
            ID2= sendIndex.key();
        }


        if(sendIndex != sendData->qm_comParam.end()){
            ID3= sendIndex.key();
            sendIndex++;
        }else{
            sendIndex=this->sendData->qm_comParam.begin();
            ID3= sendIndex.key();
        }
        {
        QByteArray data2 = this->makeSubArray(this->setBetween(static_cast<quint64>(ID0.toLong()),0,16));
        data[0]=data2[0];
        data[1]=data2[1];
        quint64 data8u=0;
        for(comUdpData::paramSignal* signal : sendData->qm_comParam.value(ID0)){
            data8u = data8u | (this->setBetween(static_cast<quint64>(sendData->qm_data.value(signal->m_name).toLong()),signal->m_startBit,signal->m_length));
        }
        QByteArray data8 = makeSubArray(data8u);
        data[2] = data8[0];
        data[3] = data8[1];
        data[4] = data8[2];
        data[5] = data8[3];
        data[6] = data8[4];
        data[7] = data8[5];
        data[8] = data8[6];
        data[9] = data8[7];
        }
        {
        QByteArray data2 = this->makeSubArray(this->setBetween(static_cast<quint64>(ID1.toLong()),0,16));
        data[10]=data2[0];
        data[11]=data2[1];
        quint64 data8u=0;
        for(comUdpData::paramSignal* signal : sendData->qm_comParam.value(ID1)){
            data8u = data8u | (this->setBetween(static_cast<quint64>(sendData->qm_data.value(signal->m_name).toLong()),signal->m_startBit,signal->m_length));
        }
        QByteArray data8 = makeSubArray(data8u);
        data[12] = data8[0];
        data[13] = data8[1];
        data[14] = data8[2];
        data[15] = data8[3];
        data[16] = data8[4];
        data[17] = data8[5];
        data[18] = data8[6];
        data[19] = data8[7];
        }
        {
        QByteArray data2 = this->makeSubArray(this->setBetween(static_cast<quint64>(ID2.toLong()),0,16));
        data[20]=data2[0];
        data[21]=data2[1];
        quint64 data8u=0;
        for(comUdpData::paramSignal* signal : sendData->qm_comParam.value(ID2)){
        data8u = data8u | (this->setBetween(static_cast<quint64>(sendData->qm_data.value(signal->m_name).toLong()),signal->m_startBit,signal->m_length));
        }
        QByteArray data8 = makeSubArray(data8u);
        data[22] = data8[0];
        data[23] = data8[1];
        data[24] = data8[2];
        data[25] = data8[3];
        data[26] = data8[4];
        data[27] = data8[5];
        data[28] = data8[6];
        data[29] = data8[7];
        }
        {
        QByteArray data2 = this->makeSubArray(this->setBetween(static_cast<quint64>(ID3.toLong()),0,16));
        data[30]=data2[0];
        data[31]=data2[1];
        quint64 data8u=0;
        for(comUdpData::paramSignal* signal : sendData->qm_comParam.value(ID3)){
        data8u = data8u | (this->setBetween(static_cast<quint64>(sendData->qm_data.value(signal->m_name).toLong()),signal->m_startBit,signal->m_length));
        }
        QByteArray data8 = makeSubArray(data8u);
        data[32] = data8[0];
        data[33] = data8[1];
        data[34] = data8[2];
        data[35] = data8[3];
        data[36] = data8[4];
        data[37] = data8[5];
        data[38] = data8[6];
        data[39] = data8[7];
        }

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
    quint64 mask = 0b1111111111111111111111111111111111111111111111111111111111111111;
    quint64 mask2 = (mask >> (64-length));
    quint64 data = (rawData >> startBit) & mask2;

    return data;
}
quint64 socketUDP::combineBytes(const QByteArray &data)
{
    Q_ASSERT(data.size() <= 8);

    quint64 result = 0;
    for (int i = 0; i < data.size(); i++) {
        result |= (quint64)(static_cast<quint8>(data[i]) & 0xFFU) << (i * 8);
    }
    return result;
}
QByteArray socketUDP::subarray(const QByteArray& data, unsigned int startIndex, unsigned int endIndex)
{
    QByteArray result(endIndex - startIndex + 1, 0);
    for (int i = startIndex; i <= endIndex; i++)
    {
        result[i - startIndex] = data[i];
    }
    return result;
}

QString socketUDP::takeResOffset(QString value, double resolution, double offset)
{
    return QString::number(value.toDouble()*resolution - offset);
}

quint64 socketUDP::setBetween(quint64 rawData, unsigned int startBit, unsigned int length)
{
    quint64 mask = 0b1111111111111111111111111111111111111111111111111111111111111111;
    return (rawData<<startBit) & ((mask>>length) << startBit);
}

QByteArray socketUDP::makeSubArray(const quint64 &data)
{
    QByteArray subArray;
    subArray.resize(8);
    quint64 mask = 0b0000000000000000000000000000000000000000000000000000000011111111;
    subArray[0]= data & mask;
    subArray[1]= data & (mask << 8);
    subArray[2]= data & (mask << 16);
    subArray[3]= data & (mask << 24);
    subArray[4]= data & (mask << 32);
    subArray[5]= data & (mask << 40);
    subArray[6]= data & (mask << 48);
    subArray[7]= data & (mask << 56);

    return subArray;

}

QString socketUDP::makeResOffset(QString value, double resolution, double offset)
{
    return QString::number((value.toDouble()+ offset)/resolution );
}
