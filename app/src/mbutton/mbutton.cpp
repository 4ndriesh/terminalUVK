#include "mbutton.h"
//#import "QDebug"
#include <QObject>
#include <QQmlExtensionPlugin>
#include <QtQml>
//#include "mvp_import.h"

MButton::MButton(QObject *parent) : QObject(parent)
{
qmlManagerButton.m_regim=2;
}
void MButton::setManagerButton(const QML_ManagerButton &setManagerButton)
{

    qmlManagerButton = setManagerButton;
//    qDebug()<<"qmlPutNadviga.m_set_putnadviga"<<qmlManagerButton.m_setPutNadviga;
//    if(qmlPutNadviga.m_chg_putnadviga==false)
//    MVP_Import::instance()->setPutNadvig(qmlManagerButton.m_setPutNadviga);
//    qmlManagerButton.m_setPutNadviga=MVP_Import::instance()->gorka->PUT_NADVIG();
    qDebug()<<"asdasdasd" <<qmlManagerButton.m_regim;
    emit qmlManagerButtonChanged();

}

QML_ManagerButton MButton::getManagerButton()const
{
    return qmlManagerButton;
}
