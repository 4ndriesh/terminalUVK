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
        return  false;
    }

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
        o.Ln+=v->Ln;
        o.ves_sl+= (v->MassV + v->MassG);
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
