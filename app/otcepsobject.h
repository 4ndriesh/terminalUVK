#ifndef OTCEPSOBJECT_H
#define OTCEPSOBJECT_H

#include <QVariantMap>

class DataObject
{
public:
    DataObject(int n=0,
               QString mar="",
               QString mar_f="",
               QString len="",
               QString len_f="",
               QString kat="",
               QString kat_f="",
               QString baz="",
               QString nag="",
               QString ur="",
               QString V="",
               QString kzp="");
    int n() const;
    void setn(int n);

    QString mar() const;
    void setmar(QString mar);

    QString mar_f() const;
    void setmar_f(QString mar_f);

    QString len() const;
    void setlen(QString len);

    QString len_f() const;
    void setlen_f(QString len_f);

    QString kat() const;
    void setkat(QString kat);

    QString kat_f() const;
    void setkat_f(QString kat_f);

    QString baz() const;
    void setbaz(QString baz);

    QString nag() const;
    void setnag(QString nag);

    QString ur() const;
    void setur(QString ur);

    QString V() const;
    void setV(QString V);

    QString kzp() const;
    void setkzp(QString kzp);

    QVariantMap toMap() const;

private:
    int m_n;
    QString m_mar;
    QString m_mar_f;
    QString m_len;
    QString m_len_f;
    QString m_kat;
    QString m_kat_f;
    QString m_baz;
    QString m_nag;
    QString m_ur;
    QString m_V;
    QString m_kzp;
};
#endif // OTCEPSOBJECT_H
