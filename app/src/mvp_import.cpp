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

    gorka->SIGNAL_ROSPUSK().getBuffer()->msecPeriodLive=2000;

    foreach (auto otcep, otceps->otceps()) {
        connect(otcep->SIGNAL_DATA().getBuffer(),&GtBuffer::bufferChanged,this,&MVP_Import::quickSlotUpdate);
    }

    timer->start(500);
    return true;
}



void MVP_Import::slotTimer()
{
    gorka->updateStates();

    struct TUVK_status{
        time_t time;
    };
    static TUVK_status c;
    c.time=QDateTime().currentDateTime().toTime_t();

    MVP_Import::instance()->udp.sendData(3,"Term_UVK",QByteArray((const char*)&c,sizeof(c)));

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

    pB.m_qmlStatusPB.m_set_value=0;
    pB.m_qmlStatusPB.m_set_visible=true;
    emit pB.statusPBChanged();

    m_Otceps *otceps=MVP_Import::instance()->gorka->findChildren<m_Otceps *>().first();

    QMap<QString,QString> m;
    m["DEST"]="UVK";
    m["CMD"]="OTCEPS";
    m["CLEAR_ALL"]="1";
    send_cmd(m);
    qDebug()<< "sortir send clear " ;
    QElapsedTimer t;
    t.start();

    while ((!otceps->enabledOtceps().isEmpty())&&(t.elapsed()<1000)){
        QCoreApplication::processEvents();
        send_cmd(m);
    }
    if (!otceps->enabledOtceps().isEmpty()){
        // не прошла команда очистки
        qDebug()<< "error sortir send clear " ;
        return false;
    }
    bool errorLoad=false;
    int allcnt=0;
    int vagcnt=0;
    foreach (const tSl2OdoRec2 &o, srt->vOtceps) {
        allcnt++;
        vagcnt+=o.vVag.size();
    }
    allcnt+=vagcnt;
    pB.m_qmlStatusPB.m_set_maximumValue=allcnt;
    emit pB.statusPBChanged();
    // сначала грузим отцепы
    foreach (const tSl2OdoRec2 &o, srt->vOtceps) {
        m.clear();
        m["DEST"]="UVK";
        m["CMD"]="SET_OTCEP_STATE";
        m["N"]=QString::number(o.NO);

        m["LOCATION"]=QString::number(1);
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
        send_cmd(m);
        qDebug()<< "sortir send otcep " << o.NO;
        pB.m_qmlStatusPB.m_set_value+=1.0;
        emit pB.statusPBChanged();
        QCoreApplication::processEvents();
        //send_cmd(m);
        QThread::msleep(20);
        //        t.start(); while (t.elapsed()<20) QCoreApplication::processEvents();


    }
    //    // проверим
    //    t.start();
    //    errorLoad=true;
    //    while (t.elapsed()<2000){
    //        QCoreApplication::processEvents();
    //        gorka->updateStates();
    //        bool good_compare=true;
    //        foreach (const tSl2OdoRec2 &o, srt->vOtceps) {
    //            m_Otcep *otcep=otceps->otcepByNum(o.NO);
    //            if ((otcep==nullptr)||(otcep->STATE_SP()!=o.SP)) {good_compare=false;break;}
    //        }
    //        if (good_compare){errorLoad=false;break;}
    //    }

    //    if (errorLoad){
    //        qDebug()<< "error sortir send otceps ";
    //    } else {
    //  грузим вагоны
    foreach (const tSl2OdoRec2 &o, srt->vOtceps) {
        int nv=0;
        foreach (const tSlVagon &v, o.vVag) {
            nv++;
            m.clear();
            m["DEST"]="UVK";
            m["CMD"]="SET_VAGON_STATE";

            QVariantHash vm=tSlVagon2Map(v);
            foreach (QString key, vm.keys()) {
                m[key]=vm[key].toString();
            }
            m["N"]=QString::number(o.NO);
            m["N_IN_OTCEP"]=QString::number(nv);
            send_cmd(m);
            qDebug()<< "sortir send otcep vagon" << o.NO << v.IV;
            pB.m_qmlStatusPB.m_set_value+=1.0;
            emit pB.statusPBChanged();
            //                send_cmd(m);
            QCoreApplication::processEvents();
            QThread::msleep(20);

            //                t.start(); while (t.elapsed()<20) QCoreApplication::processEvents();


        }
    }
    //        updateOtceps();
    // проверим
    //        t.start();
    //        errorLoad=true;
    //        while (t.elapsed()<1000){
    //            QCoreApplication::processEvents();
    //            gorka->updateStates();
    //            bool good_compare=true;
    //            foreach (const tSl2OdoRec2 &o, srt->vOtceps) {
    //                m_Otcep *otcep=otceps->otcepByNum(o.NO);
    //                if ((otcep==nullptr)||(otcep->vVag.size()!=o.vVag.size())) {good_compare=false;break;}
    //                for (int i=0;i<o.vVag.size();i++){
    //                    auto &ov=o.vVag[i];
    //                    auto &uvkv=otcep->vVag[i];
    //                    if (ov.NumV!=uvkv.STATE_NUMV()){
    //                        good_compare=false;
    //                        break;
    //                    }
    //                }

    //            }
    //            if (good_compare){errorLoad=false;break;}
    //        }
    //        if (errorLoad){
    //            qDebug()<< "error sortir send otcep vagons ";
    //        }
    //    }

    pB.m_qmlStatusPB.m_set_visible=false;
    emit pB.statusPBChanged();

    // проверим
    QThread::msleep(200);
    m.clear();
    m["DEST"]="UVK";
    m["CMD"]="OTCEPS";
    m["CHECK_LIST"]="1";
    m["ID_ROSP"]=QString::number(srt->Id);
    m["OTCEP_CNT"]=QString::number(srt->vOtceps.size());
    m["VAGON_CNT"]=QString::number(vagcnt);
    MVP_Import::instance()->cmd->send_cmd(m);

//                if (errorLoad){
//                    // чистим все
//                    m.clear();
//                    m["DEST"]="UVK";
//                    m["CMD"]="OTCEPS";
//                    m["CLEAR_ALL"]="1";
//                    MVP_Import::instance()->cmd->send_cmd(m);
//                }
                return false;
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

void MVP_Import::setOsaga()
{
    QMap<QString,QString> m;
    m["DEST"]="UVK";
    m["CMD"]="SET_OSAGA";

    MVP_Import::instance()->cmd->send_cmd(m);
    qDebug()<< "setOsaga to uvk" ;
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

void MVP_Import::setOtcepSP(int N, int SP)
{
    QMap<QString,QString> m;
    m["DEST"]="UVK";
    m["CMD"]="SET_OTCEP_STATE";
    m["SP"]=QString::number(SP);
    m["N"]=QString::number(N);
    MVP_Import::instance()->cmd->send_cmd(m);

    //    QThread::sleep(1);

    QElapsedTimer t;
    t.start();

    while (t.elapsed()<50){
        QCoreApplication::processEvents();
    }

}

void MVP_Import::incOtcep(int N, int SP)
{
    QMap<QString,QString> m;
    m["DEST"]="UVK";
    m["CMD"]="OTCEPS";
    m["INC_OTCEP"]=QString::number(N);
    m["SP"]=QString::number(SP);
    MVP_Import::instance()->cmd->send_cmd(m);

    //    QThread::sleep(1);

    QElapsedTimer t;
    t.start();

    while (t.elapsed()<50){
        QCoreApplication::processEvents();
    }
}

void MVP_Import::delOtcep(int N)
{
    QMap<QString,QString> m;
    m["DEST"]="UVK";
    m["CMD"]="OTCEPS";
    m["DEL_OTCEP"]=QString::number(N);
    MVP_Import::instance()->cmd->send_cmd(m);
    qDebug()<< "delOtcep to uvk" << N;
}

void MVP_Import::setCurOtcep(int N)
{
    QMap<QString,QString> m;
    m["DEST"]="UVK";
    m["CMD"]="OTCEPS";
    m["SET_CUR_OTCEP"]=QString::number(N);
    MVP_Import::instance()->cmd->send_cmd(m);
    qDebug()<< "setCurOtcep to uvk" << N;
}

void MVP_Import::ClearAllOtcep()
{
    QMap<QString,QString> m;
    m.clear();
    m["DEST"]="UVK";
    m["CMD"]="OTCEPS";
    m["CLEAR_ALL"]="1";
    MVP_Import::instance()->cmd->send_cmd(m);
}

void MVP_Import::updateOtceps()
{
    QMap<QString,QString> m;
    m.clear();
    m["DEST"]="UVK";
    m["CMD"]="OTCEPS";
    m["UPDATE_ALL"]="1";
    MVP_Import::instance()->cmd->send_cmd(m);
}

void MVP_Import::setUKVLight(int p)
{
    QMap<QString,QString> m;
    m.clear();
    m["DEST"]="UVK";
    m["CMD"]="SET_UKVAG_LIGHT";
    m["LIGHT"]=QString::number(p);
    MVP_Import::instance()->cmd->send_cmd(m);
}

QString MVP_Import::getSumString()
{
    static QString result;
    result.clear();
    if ((gorka!=nullptr)&&(otceps!=nullptr)){
        QMap<int,int> mpo;
        QMap<int,int> mxz;
        foreach (auto np, gorka->mSP2MAR.keys()) {
            mpo[np]=0;
            mxz[np]=0;
        }
        foreach (auto otcep, otceps->l_otceps) {
            if (!otcep->STATE_ENABLED()) continue;
            if (otcep->STATE_MAR()==0) continue;
            if ((otcep->STATE_SL_VAGON_CNT()==0)&&(otcep->STATE_SL_VAGON_CNT_PRED()==0))
                mxz[otcep->STATE_SP()]=1;

            mpo[otcep->STATE_SP()]=mpo[otcep->STATE_SP()]+otcep->STATE_SL_VAGON_CNT();
        }
        foreach (auto np, mpo.keys()) {
            if ((mpo[np]==0)&&(mxz[np]==0)) continue;
            if (!result.isEmpty()) result=result+"   ";
            if (mpo[np]<10) result=result+QString("%1-0%2").arg(np).arg(mpo[np]);else
                result=result+QString("%1-%2").arg(np).arg(mpo[np]);
            if (mxz[np]!=0) result=result+"?";

        }
    }
    return result;
}

QMap<QString, QString> MVP_Import::getDSOBusyRc()
{
    QMap<QString, QString> mName2Id;
    if (gorka!=nullptr){
        auto l=gorka->findChildren<m_RC*>();
        foreach (auto rc, l) {
            if (qobject_cast<m_RC_Gor_Park*>(rc)!=nullptr) continue;
            if ((rc->STATE_BUSY_DSO()!=0)|| (rc->STATE_BUSY_DSO()==MVP_Enums::TRCBusy::busy_unknow)||(rc->STATE_BUSY_DSO_ERR()==1)) mName2Id[rc->objectName()]=rc->idstr();
        }
        if (mName2Id.count()>0) mName2Id["ВСЕ"]="*";
    }
    return mName2Id;


    //     QMap<QString, QString> m=MVP_Import::instance()->getDSOBusyRc();
    //    foreach (auto rc_name, m.keys()) {
    //        ...add(rc_name);
    //    }

    //    MVP_Import::instance()->resetDSOBusyRc(m[rc_name]);
}

void MVP_Import::resetDSOBusyRc(QString idtsr)
{
    qDebug()<<"resetDSOBusyRc";
    QMap<QString,QString> m;
    m.clear();
    m["DEST"]="UVK";
    m["CMD"]="RESET_DSO_BUSY";
    m["RC"]=idtsr;
    MVP_Import::instance()->cmd->send_cmd(m);
}

void MVP_Import::send_cmd(QMap<QString, QString> &m)
{
    //    if ((!sended_cmd.isValid())||(sended_cmd.elapsed()>20)){
    MVP_Import::instance()->cmd->send_cmd(m);
    //        sended_cmd.restart();
    //    };
}
QDateTime _ttt;
void MVP_Import::quickSlotUpdate()
{
    if ((!_ttt.isValid())||(_ttt.msecsTo(QDateTime::currentDateTime())>100)){
        _ttt=QDateTime::currentDateTime();
        slotTimer();
    }
}
