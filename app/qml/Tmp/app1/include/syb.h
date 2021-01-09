#ifndef SYB_H
#define SYB_H

#include <QObject>

struct tSl2Odo2;
class Syb : public QObject
{
    Q_OBJECT
private:
        explicit Syb(QObject *parent = nullptr);
        virtual ~Syb(){}
public:
    static Syb &instance(){
    static Syb *_instance=0;
    if(_instance ==0){
        _instance=new Syb();
    }
    return *_instance;
}


    bool loadSortirToUvk(const tSl2Odo2 *srt);
    void deleteDataSourceObject();


public slots:

    void slotOtcepChanged();
    void sortirArrived(const tSl2Odo2 *srt);
    void uvk_cmd_accept(QMap<QString,QString> m);
};

#endif // SYB_H
