#ifndef JSON_H
#define JSON_H
#include <QJsonObject>

class Json
{
    Q_DISABLE_COPY(Json)
public:
    explicit Json();
    virtual ~Json(){}
    static Json &instance(){
        static Json *_instance=0;
        if(_instance ==0){
            _instance=new Json();
        }
        return *_instance;
    }
    QString getMXml(const QString &);

private:
    void onLoadSettings();
    QJsonObject m_currentJsonObject;
};

#endif // JSON_H
