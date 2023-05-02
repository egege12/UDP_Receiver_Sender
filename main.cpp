
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "socketudp.h"
#include "comUdpData.h"
#include <QThread>
int main(int argc, char *argv[])
{
    QThread workerThread;
    comUdpData *const udpReceive = new comUdpData;
    comUdpData *const udpSend = new comUdpData;

    udpReceive->importDBC("udpReceive.dbc");
    udpSend->importDBC("udpSend.dbc");
    QThread::currentThread()->setObjectName("Main Thread");
    workerThread.setObjectName("Communication Thread");
    socketUDP udpSocket(nullptr,"10.100.30.202","10.100.30.200","5500","bidirectional",100,udpReceive,udpSend);
    udpSocket.moveToThread(&workerThread);
    QObject::connect(&workerThread, SIGNAL(started()), &udpSocket, SLOT(startUdpCom()));
    QObject::connect(&workerThread, SIGNAL(finished()), &udpSocket, SLOT(stopUdpCom()));
    workerThread.start();
    emit udpSocket.sendDatagram();
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/UDP_Receiver_Sender/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    QQmlContext * Context1 = engine.rootContext();
    QQmlContext * Context2 = engine.rootContext();
    Context1->setContextProperty("udpReceive", udpReceive);
    Context2->setContextProperty("udpSend", udpSend);
    engine.load(url);

    return app.exec();
}
