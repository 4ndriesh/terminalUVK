#include "vagonsobject.h"

#include "m_vagon.h"
#include <QMetaProperty>
#include "mvp_import.h"

VagonsObject::VagonsObject(m_Vagon *vagon)
{
    this->vagon=vagon;
    m_storedStateVal=toMap();


}

//void VagonsObject::setState(QString stateName, QVariant val)
//{
//    QVariant oldVal=getState(stateName);
//    if (oldVal!=val){
//        // отсылаем
//        m_storedStateVal.clear();
//        m_storedStateVal[stateName]=val;
//        QMap<QString,QString> m;
//        m["DEST"]="UVK";
//        m["CMD"]="SET_OTCEP_STATE";
//        m["N"]=QString::number(vagon->NUM());

//        // убираю STATE
//        stateName=stateName.replace("STATE_","");
//        m[stateName]=val.toString();
//        MVP_Import::instance()->cmd->send_cmd(m);

//        // надо отслеживать что увк воспринял.. или пофиг
//    }
//}

QVariant VagonsObject::getState(QString stateName) const
{
    return vagon->property(qPrintable(stateName));
}

QVariantMap VagonsObject::toMap() const
{
    QVariantMap  m;
    for (int idx = 0; idx < vagon->metaObject()->propertyCount(); idx++) {
        QMetaProperty metaProperty = vagon->metaObject()->property(idx);
        QString proprtyName=metaProperty.name();
        QVariant V;
        V=metaProperty.read(vagon);
        if (V.isValid()) m[proprtyName]=V;
    }
    return m;
}


