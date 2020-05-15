// qt
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QMovie>
#include <QQmlContext>

// wclasses
#include "WQtSVGImage.h"

//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    // log the supported animated file formats
    qDebug() << "Supported animated file formats:" << QMovie::supportedFormats();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // declare the svg image type
    qmlRegisterType<WQtSVGImage>("WQtSVGImage", 1, 0, "WQtSVGImage");

    QApplication          app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl            url(QStringLiteral("qrc:/main.qml"));

    (void)QObject::connect(&engine,
                           &QQmlApplicationEngine::objectCreated,
                           &app,
                           [url](QObject *obj, const QUrl &objUrl)
                           {
                               if (!obj && url == objUrl)
                                   QCoreApplication::exit(-1);
                           },
                           Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
//---------------------------------------------------------------------------
