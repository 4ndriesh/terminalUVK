#include "otcepsobject.h"


DataObject::DataObject(int n,
                       QString mar,
                       QString mar_f,
                       QString len,
                       QString len_f,
                       QString kat,
                       QString kat_f,
                       QString baz,
                       QString nag,
                       QString ur,
                       QString V,
                       QString kzp):
    m_n(n),
    m_mar(mar),
    m_mar_f(mar_f),
    m_len(len),
    m_len_f(len_f),
    m_kat(kat),
    m_kat_f(kat_f),
    m_baz(baz),
    m_nag(nag),
    m_ur(ur),
    m_V(V),
    m_kzp(kzp)
{

}

int DataObject::n() const
{
    return m_n;
}

void DataObject::setn(int n)
{
    m_n = n;
}

QString DataObject::mar() const
{
    return m_mar;
}

void DataObject::setmar(QString mar)
{
    m_mar = mar;
}

QString DataObject::mar_f() const
{
    return m_mar_f;
}

void DataObject::setmar_f(QString mar_f)
{
    m_mar_f = mar_f;
}


QString DataObject::len() const
{
    return m_len;
}

void DataObject::setlen(QString len)
{
    m_len = len;
}

QString DataObject::len_f() const
{
    return m_len_f;
}

void DataObject::setlen_f(QString len_f)
{
    m_len_f = len_f;
}

QString DataObject::kat() const
{
    return m_kat;
}

void DataObject::setkat(QString kat)
{
    m_kat = kat;
}

QString DataObject::kat_f() const
{
    return m_kat_f;
}

void DataObject::setkat_f(QString kat_f)
{
    m_kat_f = kat_f;
}

QString DataObject::baz() const
{
    return m_baz;
}

void DataObject::setbaz(QString baz)
{
    m_baz = baz;
}

QString DataObject::nag() const
{
    return m_nag;
}

void DataObject::setnag(QString nag)
{
    m_nag = nag;
}

QString DataObject::ur() const
{
    return m_ur;
}

void DataObject::setur(QString ur)
{
    m_ur = ur;
}

QString DataObject::V() const
{
    return m_V;
}

void DataObject::setV(QString V)
{
    m_V = V;
}

QString DataObject::kzp() const
{
    return m_kzp;
}

void DataObject::setkzp(QString kzp)
{
    m_kzp = kzp;
}
QVariantMap DataObject::toMap() const
{
    QVariantMap map;
    map["n"] = m_n;
    map["mar"] = m_mar;
    map["mar_f"] = m_mar_f;
    map["len"] = m_len;
    map["len_f"] = m_len_f;
    map["kat"] = m_kat;
    map["kat_f"] = m_kat_f;
    map["baz"] = m_baz;
    map["nag"] = m_nag;
    map["ur"] = m_ur;
    map["V"] = m_V;
    map["kzp"] = m_kzp;
    return map;
}
