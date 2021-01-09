#include "otcepsobject.h"

#include "m_otcep.h"
#include <QMetaProperty>
#include "mvp_import.h"
DataObject::DataObject(m_Otcep *otcep)
{
    this->otcep=otcep;
    m_storedStateVal=toMap();


}

void DataObject::setState(QString stateName, QVariant val)
{
    QVariant oldVal=getState(stateName);
    if (oldVal!=val){
        // отсылаем
        m_storedStateVal.clear();
        m_storedStateVal[stateName]=val;
        QMap<QString,QString> m;
        m["DEST"]="UVK";
        m["CMD"]="SET_OTCEP_STATE";
        m["N"]=QString::number(otcep->NUM());

        // убираю STATE
        stateName=stateName.replace("STATE_","");
        m[stateName]=val.toString();
        MVP_Import::instance()->cmd->send_cmd(m);

        // надо отслеживать что увк воспринял.. или пофиг
    }
}

QVariant DataObject::getState(QString stateName) const
{
    return otcep->property(qPrintable(stateName));
}

QVariantMap DataObject::toMap() const
{
    QVariantMap  m;
    for (int idx = 0; idx < otcep->metaObject()->propertyCount(); idx++) {
        QMetaProperty metaProperty = otcep->metaObject()->property(idx);
        QString proprtyName=metaProperty.name();
        QVariant V;
        V=metaProperty.read(otcep);
        if (V.isValid()) m[proprtyName]=V;
    }
    return m;
}

