#ifndef OTCEPSOBJECT_H
#define OTCEPSOBJECT_H

#include <QVariantMap>
class m_Otcep;
class DataObject
{
public:
    m_Otcep *otcep;
    DataObject(m_Otcep *otcep);
    void setState(QString, const QVariant &);
    QVariant getState(const QString &) const;
    QVariantMap toMap() const;

private:
    QVariantMap  m_storedStateVal;

};
#endif // OTCEPSOBJECT_H
