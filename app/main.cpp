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
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include "viewotcepsmodel.h"
#include "mvp_import.h"
#include "kbdllhooks.h"
#include "managemodel.h"

#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    KBdllhooks::instance();

    //    QObject::connect(&KBdllhooks::instance(), &KBdllhooks::mouseEvent,
    //                     [](){
    //        qDebug() << "KeyBoard Event";
    //    });

    if (!MVP_Import::instance()->load("./M.xml"))
    {
        exit(-1);
    }


    qRegisterMetaType<StructPutNadviga>("StructPutNadviga");
    qRegisterMetaType<StructProgressBar>("StructProgressBar");
    ViewOtcepsModel &model = ViewOtcepsModel::instance();
    Management &manage = Management::instance();
    QQmlApplicationEngine engine;
    engine.addImportPath(":/qml");

    QQmlContext* context = engine.rootContext();
    context->setContextProperty("otcepsModel", &model);
    context->setContextProperty("manageModel", &manage);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

