/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "app/viewotcepsmodel.h"
#include "app/editotcepsmodel.h"
#include "mvp_import.h"
#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>

int main(int argc, char *argv[])
{



    // Qt Charts uses Qt Graphics View Framework for drawing, therefore QApplication must be used.
    QApplication app(argc, argv);
    //  SYB
    if (!MVP_Import::instance()->load("./M.xml"))
    {
        exit(-1);
    }
    QQuickView viewer;
    ViewOtcepsModel model;
    EditOtcepsModel model1;

    viewer.setTitle(QStringLiteral("QML Weather"));
    viewer.rootContext()->setContextProperty("otcepsModel", &model);
    viewer.rootContext()->setContextProperty("otcepsModelRedact", &model1);
//    viewer.rootContext()->setContextProperty("weatherAppKey", appKey);
    viewer.setSource(QUrl("qrc:/qml/main.qml"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
//    viewer.show();

    return app.exec();
}



//#include "app/viewotcepsmodel.h"
//#include "app/editotcepsmodel.h"
//#include "app/emitwinthread.h"
//#include <QGuiApplication>
//#include <QQmlApplicationEngine>
//#include <QQmlContext>
//#include <QTimer>



//#include <QRandomGenerator>
//#include <random>
//#include <iostream>


//#include "mvp_import.h"

//int main(int argc, char *argv[])
//{
//    //  SYB
//    if (!MVP_Import::instance()->load("./M.xml"))
//    {
//        exit(-1);
//    }


//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);

//    //        std::uniform_real_distribution<double> dist(0.0, 10.0);


//    ViewOtcepsModel model;
//    EditOtcepsModel model1;
//    qDebug() << "start" ;
//    QQmlApplicationEngine engine;
/*//    qmlRegisterType<EmitWinThread>("TestAsync", 1, 0, "EmitWinThread");*/
//    engine.rootContext()->setContextProperty("otcepsModel", &model);
//    engine.rootContext()->setContextProperty("otcepsModelRedact", &model1);
//    QString msg = "Hello from C++";
//    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
// if (engine.rootObjects().isEmpty())
//        return -1;

    /*QTimer timer;
        QObject::connect(&timer, &QTimer::timeout, [&model, &dist](){
            QModelIndex ix = model.index(88);
            model.setData(ix, dist(*QRandomGenerator::global()), DataSourceModel::valueRole);
        });
        timer.start(1000);*/
//    return app.exec();










//    //    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    //    QGuiApplication app(argc, argv);
//    //    DataSourceModel model;
//    //    QQmlApplicationEngine engine;
//    //    engine.rootContext()->setContextProperty("dataSourceModel", &model);
//    //    engine.rootContext()->setContextProperty("otcepsModel", &model);
//    //    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
//    //    if (engine.rootObjects().isEmpty())
//    //        return -1;

//    //    return app.exec();
//}
