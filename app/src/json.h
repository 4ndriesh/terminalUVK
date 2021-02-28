#ifndef JSON_H
#define JSON_H
#include <QJsonObject>
#include <QDebug>

class Json
{
    Q_DISABLE_COPY(Json)
public:
    explicit Json(const QString &);
    virtual ~Json(){
    }
    static Json &instance(const QString & path){
        static Json *_instance=0;
        if(_instance ==0){
            _instance=new Json(path);
        }
        return *_instance;
    }
    QString getMXml(const QString &,const QString &);
    QString getSettings(const QString &);

private:
    QString fileName;
    QJsonObject m_currentJsonObject;
};

#endif // JSON_H
