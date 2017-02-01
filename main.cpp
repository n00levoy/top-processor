#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "topmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    TopModel topModel;
//    topModel.addAlbum(new Album("1. Warpaint - Heads Up"));

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("topModel", &topModel);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
