#include "app/viewotcepsmodel.h"
#include "app/editotcepsmodel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>



#include <QRandomGenerator>
#include <random>
#include <iostream>


#include "mvp_import.h"

int main(int argc, char *argv[])
{

    //  SYB
    if (!MVP_Import::instance()->load("./M.xml"))
    {
        exit(-1);
    }


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //        std::uniform_real_distribution<double> dist(0.0, 10.0);


    ViewOtcepsModel model;
    EditOtcepsModel model1;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("otcepsModel", &model);
    engine.rootContext()->setContextProperty("otcepsModelRedact", &model1);
    QString msg = "Hello from C++";
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    /*QTimer timer;
        QObject::connect(&timer, &QTimer::timeout, [&model, &dist](){
            QModelIndex ix = model.index(88);
            model.setData(ix, dist(*QRandomGenerator::global()), DataSourceModel::valueRole);
        });
        timer.start(1000);*/
    return app.exec();










    //    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //    QGuiApplication app(argc, argv);
    //    DataSourceModel model;
    //    QQmlApplicationEngine engine;
    //    engine.rootContext()->setContextProperty("dataSourceModel", &model);
    //    engine.rootContext()->setContextProperty("otcepsModel", &model);
    //    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    //    if (engine.rootObjects().isEmpty())
    //        return -1;

    //    return app.exec();
}
