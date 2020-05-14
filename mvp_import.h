#ifndef MVP_IMPORT_H
#define MVP_IMPORT_H

//  SYB
#include "mvp_system.h"
#include "gtbuffers_udp_d2.h"
#include "modelgroupgorka.h"
#include "m_otceps.h"
#include "gtcommandinterface.h"


struct tSl2OdoRec2{
    int   NO=0;           //  Номер  Отцепа  НО
    int   SP=0;           //  СП  Сорт Путь
    qreal  ves_sl;        //  вес на ос
    int   OSO;       //  Особые отметки ????
    int   Ne;           // не спускать
    int  Ln;            // в метрах
    int Osy;
    int       aDb=0;     // ��������
    int       aNg=0;
    QVector<tSlVagon> vVag;
};

struct tSl2Odo2
{
    uint32 Id;
    QVector<tSl2OdoRec2> vOtceps;

};

class MVP_Import: public QObject
{
    Q_OBJECT
public:
    explicit MVP_Import();
    virtual ~MVP_Import(){}
    static MVP_Import* instance(){
           static MVP_Import one;
           return &one;

    }
    GtBuffers_UDP_D2 udp;
    bool load(QString fn);
    ModelGroupGorka *gorka=nullptr;
    GtCommandInterface *cmd;
    uint32 _Id=0;

signals:
    void sortirArrived(const tSl2Odo2 *srt);
public slots:
    void slotTimer();
    void buffer14Changed(GtBuffer *B);
    void makeSortir();
protected:

};

#endif // MVP_IMPORT_H
