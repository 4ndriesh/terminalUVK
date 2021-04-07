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

#include "otcepsmodel.h"
#include "mvp_import.h"
#include "kbdllhooks.h"
#include "railchain.h"
#include "vagonsmodel.h"
#include "managemodel.h"
#include <QtSvg>
#include <QQmlContext>
#include <QHostInfo>
#include "json.h"

void registerMetaTypes()
{
    qRegisterMetaType<QML_ManagerButton>("QML_ManagerButton");
    qRegisterMetaType<StructProgressBar>("StructProgressBar");
}

int main(int argc, char *argv[])
{
    //    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //    QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    //    QCoreApplication::setAttribute( Qt::AA_UseDesktopOpenGL );
    QCoreApplication::setAttribute( Qt::AA_UseOpenGLES);
    QGuiApplication app(argc, argv);
//    Json *sett = new Json(":/settings.json");
    Json *sett = new Json("settings/settings.json");

    if(QHostInfo::localHostName() == sett->getSettings("localHostName"))
        KBdllhooks::instance();

    if (!MVP_Import::instance()->load(sett->getSettings("xml")))
    {
        exit(-1);
    }    


    registerMetaTypes();
    VagonsModel &vagons = VagonsModel::instance();
    OtcepsModel &model = OtcepsModel::instance();
//   qmlRegisterUncreatableType<OtcepsModel>( "otcepsModel", 1, 0, "OtcepsModel", "" );
    ManageModel &manage = ManageModel::instance();
    manage.notice=new Json(sett->getSettings("notice"));
    delete sett;
    RailChain &rch = RailChain::instance();
    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/qml");
//    engine.addImportPath("./qml");
//    engine.addPluginPath("/");

//    engine.setObjectOwnership(&model,QQmlEngine::ObjectOwnership::CppOwnership);
    //    QQmlEngine::setObjectOwnership(&engine, QQmlEngine::CppOwnership);

    QQmlContext* context = engine.rootContext();
    context->setContextProperty("otcepsModel", &model);
    context->setContextProperty("manageModel", &manage);
    context->setContextProperty("rChain", &rch);
    context->setContextProperty("vagonsModel", &vagons);
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
    const QUrl url(QStringLiteral("./main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    int r = app.exec();
    UnhookWindowsHookEx(KBdllhooks::instance().kbHook);
    return r;
}

