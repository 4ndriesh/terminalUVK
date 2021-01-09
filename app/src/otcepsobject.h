#ifndef OTCEPSOBJECT_H
#define OTCEPSOBJECT_H

#include <QVariantMap>
class m_Otcep;
class DataObject
{
public:
    m_Otcep *otcep;
    DataObject(m_Otcep *otcep);
    void setState(QString stateName,QVariant val);
    QVariant getState(QString stateName) const;
    QVariantMap toMap() const;

private:
    QVariantMap  m_storedStateVal;

};
#endif // OTCEPSOBJECT_H
