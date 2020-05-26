#include "mvp_import.h"
#include <QFileInfo>





MVP_Import::MVP_Import():QObject(nullptr)
{

    MVP.setGetGtBufferInterface(&udp);
    cmd=new GtCommandInterface(this,&udp);
}

bool MVP_Import::load(QString fn)
{
    if (!QFileInfo(fn).exists()){
        qDebug() << "file not found " << QFileInfo(fn).absoluteFilePath();
        return false;
    }
    QTimer *timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MVP_Import::slotTimer);
    QObject *O=MVP.loadObject(fn);
    gorka=qobject_cast<ModelGroupGorka *>(O);
    if (!gorka) {
        qDebug() << "load problem " << fn;
        return false;
    }
    otceps=MVP_Import::instance()->gorka->findChildren<m_Otceps *>().first();


    // прием сортира от дспг

//    GtBuffer * buffer12=udp.getGtBuffer(12,"Sl2Odo");
//    connect(buffer12,&GtBuffer::bufferChanged,this,&MVP_Import::buffer12Changed);
    for (int i=0;i<MaxVagon;i++){
        udp.getGtBuffer(14,QString("vag%1").arg(i+1));
    }
    GtBuffer * buffer14=udp.getGtBuffer(14,"vag1");
    connect(buffer14,&GtBuffer::bufferChanged,this,&MVP_Import::buffer14Changed);

    timer->start(250);
    return true;
}



void MVP_Import::slotTimer()
{
    gorka->updateStates();
}
void SplitOSO(int i, uint8* OSO)
{
    OSO[0] = i / 100 % 10;
    OSO[1] = i / 10 % 10;
    OSO[2] = i % 10;
}
int SumOSO(int i1, int i2)
{
    uint8 OSO[2][3];
    SplitOSO(i1, OSO[0]);
    SplitOSO(i2, OSO[1]);
    return  qMax(OSO[0][0], OSO[1][0])*100
            + qMax(OSO[0][1], OSO[1][1])*10
            + qMax(OSO[0][2], OSO[1][2]);
}
int SumUR(int ur1, int ur2)
{
    return qMax(ur1, ur2);
}

void MVP_Import::makeSortir()
{
    GtBuffer * buffer14=udp.getGtBuffer(14,"vag1");
    const tSlVagon * SlVagon=reinterpret_cast<tSlVagon *>(buffer14->A.data());
    static tSl2Odo2 srt;
    srt.Id=SlVagon->Id;
    srt.vOtceps.clear();
    tSl2OdoRec2 o;
    o.NO=0;
    int sum_ves=0;
    for (int i=0;i<MaxVagon;i++){
        GtBuffer * b=udp.getGtBuffer(14,QString("vag%1").arg(i+1));
        const tSlVagon * v=reinterpret_cast<tSlVagon *>(b->A.data());
        if ((v->Id!=srt.Id)||(v->Id==0)){
            if (!o.vVag.isEmpty()>0) srt.vOtceps.push_back(o);
            o.vVag.clear();
            break;
        }
        if (v->NO!=o.NO){
            if (v->NO!=o.NO+1) return;
            if (v->IV==0) return;
            if (!o.vVag.isEmpty()>0) srt.vOtceps.push_back(o);
            o.vVag.clear();
            sum_ves=0;
            o.NO=v->NO;           //  Номер  Отцепа  НО
            o.SP=v->SP;           //  СП  Сорт Путь
            o.ves_sl=0;        //  весов категория
            o.OSO=0;       //  Особые отметки ????
            o.Ne=0;           // не спускать
            o.Ln=0;
            o.Osy=0;
        }
        o.vVag.push_back(*v);
        o.Ln+=v->Ln/1000.;
        sum_ves+= (v->MassV + v->MassG);

        o.Ne = SumUR(o.Ne, v->Ur);
        o.OSO = SumOSO(o.OSO, v->OSO);
        o.Osy+=v->Osy;
        o.ves_sl = sum_ves / (o.vVag.size() * 4);
        if (o.Osy) o.ves_sl =sum_ves / float(o.Osy);
        if (v->aDb!=0) o.aDb=1;
        if (v->aNg!=0) o.aNg=1;

    }
    if (!o.vVag.isEmpty()>0) srt.vOtceps.push_back(o);
    emit sortirArrived(&srt);
}
void MVP_Import::buffer14Changed(GtBuffer *)
{
    GtBuffer * buffer14=udp.getGtBuffer(14,"vag1");
    const tSlVagon * SlVagon=reinterpret_cast<tSlVagon *>(buffer14->A.data());
    if ((SlVagon->Id!=0)&&(SlVagon->Id!=_Id)){
        _Id=SlVagon->Id;
        // ждем изменения 2 сек
        QTimer::singleShot(2000, this, &MVP_Import::makeSortir);
    }
}
bool MVP_Import::loadSortirToUvk(const tSl2Odo2 *srt)
{

    m_Otceps *otceps=MVP_Import::instance()->gorka->findChildren<m_Otceps *>().first();

    QMap<QString,QString> m;
    m["DEST"]="UVK";
    m["CMD"]="OTCEPS";
    m["CLEAR_ALL"]="1";
    MVP_Import::instance()->cmd->send_cmd(m);
    emit sendStartProgressBar();
    qDebug()<< "sortir send clear " ;
    QElapsedTimer t;
    t.start();

    while ((!otceps->enabledOtceps().isEmpty())&&(t.elapsed()<1000)){
        QCoreApplication::processEvents();
    }
    if (!otceps->enabledOtceps().isEmpty()){
        // не прошла команда очистки
        qDebug()<< "error sortir send clear " ;
        return false;
    }
    bool errorLoad=false;
    foreach (const tSl2OdoRec2 &o, srt->vOtceps) {
        m.clear();
        m["DEST"]="UVK";
        m["CMD"]="SET_OTCEP_STATE";
        m["N"]=QString::number(o.NO);

        m["ENABLED"]=QString::number(1);
        m["ID_ROSP"]=QString::number(srt->Id);
        m["SP"]=QString::number(o.SP);
        m["SL_VAGON_CNT"]=QString::number(o.vVag.size());
        m["SL_OSY_CNT"]=QString::number(o.Osy);
        m["SL_LEN"]=QString::number(o.Ln);
        m["SL_VES"]=QString::number(o.ves_sl);
        m["SL_BAZA"]=QString::number(o.aDb);
        m["SL_UR"]=QString::number(o.Ne);
        m["SL_OSO"]=QString::number(o.OSO);
        MVP_Import::instance()->cmd->send_cmd(m);
        qDebug()<< "sortir send otcep " << o.NO;
        t.start();
        m_Otcep *otcep=otceps->otcepByNum(o.NO);
        if (otcep==nullptr){
            errorLoad=true;

            break;
        }
        while ((otcep->STATE_SP()!=o.SP)&&(t.elapsed()<1000)){
            QCoreApplication::processEvents();
        }
        if ((otcep->STATE_SP()!=o.SP)){
            // не прошла команда на отцеп
            errorLoad=true;
            qDebug()<< "error sortir send otcep " << o.NO;
            break;
        }

        foreach (const tSlVagon &v, o.vVag) {

            m.clear();
            m["DEST"]="UVK";
            m["CMD"]="ADD_OTCEP_VAG";
            m["N"]=QString::number(o.NO);
            QVariantHash vm=tSlVagon2Map(v);
            foreach (QString key, vm.keys()) {
                m[key]=vm[key].toString();
            }

            MVP_Import::instance()->cmd->send_cmd(m);
            qDebug()<< "sortir send otcep vagon" << o.NO << v.IV;
            t.start();
            while (((otcep->vVag.isEmpty())||(otcep->vVag.last().IV!=v.IV))&&(t.elapsed()<1000)){
                QCoreApplication::processEvents();
            }
            if ((otcep->vVag.isEmpty())||(otcep->vVag.last().IV!=v.IV)){
                // не прошла команда на вагон
                errorLoad=true;
                qDebug()<< "error sortir send otcep vagon" << o.NO << v.IV;
                break;
            }
        }
        if (errorLoad) break;
    }
    if (errorLoad){
        // чистим все
        m.clear();
        m["DEST"]="UVK";
        m["CMD"]="OTCEPS";
        m["CLEAR_ALL"]="1";
        MVP_Import::instance()->cmd->send_cmd(m);
    }
    emit sendStopProgressBar();
    return errorLoad;
}

void MVP_Import::setRegim(int p)
{
    QMap<QString,QString> m;
    m["DEST"]="UVK";
    m["CMD"]="SET_RIGIME";
    switch (p){
    case ModelGroupGorka::regimRospusk:
        m["REGIME"]="ROSPUSK";
        break;
    case ModelGroupGorka::regimPausa:
        m["REGIME"]="PAUSE";
        break;
    case ModelGroupGorka::regimStop:
        m["REGIME"]="STOP";
        break;
    default: return;
    }
    MVP_Import::instance()->cmd->send_cmd(m);
    qDebug()<< "setRegim to uvk" << p;

}

void MVP_Import::setPutNadvig(int p)
{
    QMap<QString,QString> m;
    m["DEST"]="UVK";
    m["CMD"]="SET_ACT_ZKR";
    switch (p){
    case 1:
        m["ACT_ZKR"]="1";
        break;
    case 2:
        m["ACT_ZKR"]="2";
        break;

    default: return;
    }
    MVP_Import::instance()->cmd->send_cmd(m);
    qDebug()<< "setPutNadvig to uvk" << p;
}
