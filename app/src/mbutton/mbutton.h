#ifndef MBUTTON_H
#define MBUTTON_H

#include <QObject>

struct QML_ManagerButton {
    Q_GADGET
    Q_PROPERTY(int setPutNadviga MEMBER m_setPutNadviga)
    Q_PROPERTY(int selectPutNadviga MEMBER m_selectPutNadviga)
    Q_PROPERTY(bool chngPutNadviga MEMBER m_chngPutNadviga)
    Q_PROPERTY(int editing MEMBER m_editing)
    Q_PROPERTY(int regim MEMBER m_regim)

public:
    int m_setPutNadviga;
    int m_selectPutNadviga;
    bool m_chngPutNadviga;
    int m_editing;
    int m_regim;
};
Q_DECLARE_METATYPE(QML_ManagerButton)

class MButton: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QML_ManagerButton qmlManagerButton READ getManagerButton WRITE setManagerButton NOTIFY qmlManagerButtonChanged)

public:
    explicit MButton(QObject *parent = nullptr);
    virtual ~MButton(){}
    QML_ManagerButton qmlManagerButton;
    QML_ManagerButton getManagerButton()const;
    void setManagerButton(const QML_ManagerButton &);

signals:
    void qmlManagerButtonChanged();
};

#include <QObject>
#include <QQmlExtensionPlugin>
#include <QtQml>
#include "mbutton.h"

class QExampleQmlPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
//    Q_PLUGIN_METADATA(IID "mbutton.json")
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri)
    {
    Q_ASSERT(uri == QLatin1String("Base"));
    qmlRegisterType<MButton>(uri, 1, 0, "MButton");
    }
};
#endif // MBUTTON_H
