#ifndef FROMSYB_H
#define FROMSYB_H
#include <QObject>

struct tSl2Odo2;
class FromSyb : public QObject
{
    Q_OBJECT
private:
        explicit FromSyb(QObject *parent = nullptr);
        virtual ~FromSyb(){}
public:
    static FromSyb &instance(){
    static FromSyb *_instance=0;
    if(_instance ==0){
        _instance=new FromSyb();
    }
    return *_instance;
}


    bool loadSortirToUvk(const tSl2Odo2 *srt);
    void deleteDataSourceObject();


public slots:
//signals:

    void sortirArrived(const tSl2Odo2 *srt);
    void uvk_cmd_accept(QMap<QString,QString> m);
};

#endif // FROMSYB_H
