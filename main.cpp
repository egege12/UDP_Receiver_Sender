
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "dataSendUDP.h"
#include "dataReceiveUDP.h"
#include "socketudp.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/UDP_Receiver_Sender/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
