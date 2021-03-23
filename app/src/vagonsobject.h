#ifndef VAGONSOBJECT_H
#define VAGONSOBJECT_H

#include <QVariantMap>
class m_Vagon;
class VagonsObject
{
public:
    m_Vagon *vagon;
    VagonsObject(m_Vagon *vagon);
    void setState(QString stateName,QVariant val);
    QVariant getState(QString stateName) const;
    QVariantMap toMap() const;

private:
    QVariantMap  m_storedStateVal;
};

#endif // VAGONSOBJECT_H
