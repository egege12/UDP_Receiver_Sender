
#ifndef DATASETUI_H
#define DATASETUI_H
#include <QObject>
#include<QList>
#include "dataReceiveUDP.h"

class dataSetIO : public QObject{

    Q_PROPERTY(bool enableSend READ enableSend WRITE setenableSend NOTIFY enableSendChanged)
    Q_PROPERTY(bool oneTimeSend READ oneTimeSend WRITE setOneTimeSend NOTIFY oneTimeSendChanged)
public:

    bool enableSend() const;
    void setenableSend(bool newEnableSend);

    bool oneTimeSend() const;
    void setoneTimeSend(bool newOneTimeSend);

public slots:

    void appendData(QString data);
    void appendReceive(dataReceiveUDP data);

signals:

    void enableSendChanged();
    void oneTimeSendChanged();
    void dataChanged();
    void dataReceivedChanged();
private:

    bool m_enableSend;
    bool m_oneTimeSend;

    QList<QString> data;

};

inline bool dataSetIO::oneTimeSend() const
{
    return m_oneTimeSend;
}

inline void dataSetIO::setoneTimeSend(bool newOneTimeSend)
{
    if (m_oneTimeSend == newOneTimeSend)
        return;
    m_oneTimeSend = newOneTimeSend;
    emit oneTimeSendChanged();
}

inline bool dataSetIO::enableSend() const
{
    return m_enableSend;
}

inline void dataSetIO::setenableSend(bool newEnableSend)
{
    if (m_enableSend == newEnableSend)
        return;
    m_enableSend = newEnableSend;
    emit enableSendChanged();
}

#endif // DATASETUI_H
