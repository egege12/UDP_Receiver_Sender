
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "socketudp.h"
#include "comUdpData.h"

int main(int argc, char *argv[])
{
    comUdpData *const udpReceive = new comUdpData;
    comUdpData *const udpSend = new comUdpData;

    udpReceive->importDBC("../udpReceive.dbc");
    udpSend->importDBC("../udpSend.dbc");

    socketUDP udpSocket(nullptr,"broadcast","broadcast","5500","bidirectional",udpReceive,udpSend);
    udpSocket.startBroadcasting();
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/UDP_Receiver_Sender/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    QQmlContext * Context1 = engine.rootContext();
    QQmlContext * Context2 = engine.rootContext();
    Context1->setContextProperty("udpReceive", udpReceive);
    Context2->setContextProperty("udpSend", udpSend);
    engine.load(url);

    return app.exec();
}
