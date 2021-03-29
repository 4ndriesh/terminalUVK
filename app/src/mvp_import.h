#ifndef MVP_IMPORT_H
#define MVP_IMPORT_H

//  SYB
#include "mvp_system.h"
#include "gtbuffers_udp_d2.h"
#include "modelgroupgorka.h"
#include "m_otceps.h"
#include "gtcommandinterface.h"
#include "managemodel.h"

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

    ManageModel &pB = ManageModel::instance();
    GtBuffers_UDP_D2 udp;
    bool load(QString fn);
    ModelGroupGorka *gorka=nullptr;
    m_Otceps *otceps=nullptr;
    GtCommandInterface *cmd;
    uint32 _Id=0;
    bool loadSortirToUvk(const tSl2Odo2 *srt);
    void setRegim(int p);
    void setOsaga();
    void setPutNadvig(int p);
    void setOtcepSP(int N, int SP);
    void incOtcep(int N);
    void delOtcep(int N);
    void setCurOtcep(int N);
    void ClearAllOtcep();
    void updateOtceps();
    QMap<QString,QString> getDSOBusyRc();
    void resetDSOBusyRc(QString idtsr);
    void send_cmd(QMap<QString,QString> &m);

signals:
    void sortirArrived(const tSl2Odo2 *srt);
//    void sendStartProgressBar();
//    void sendStopProgressBar();
public slots:
    void quickSlotUpdate();
    void slotTimer();
    void buffer14Changed(GtBuffer *B);
    void makeSortir();
protected:
    QElapsedTimer sended_cmd;

};

#endif // MVP_IMPORT_H
