#include "management.h"
#include <QFileInfo>
#include <QDebug>
#include "mvp_import.h"
#include <QMetaProperty>


Management::Management(QObject *parent) : QObject(parent)
{
//    VisibleEditButton=1;

}

void Management::deleteFromList()
{

}

void Management::getRndChart()
{
    //    qmlStopPause=MVP_Import::instance()->gorka->STATE_REGIM();
//    qmlX+=1;
//    qmlY=qrand() % 10;
//    emit setRndChart(qmlX,qmlY);
}

void Management::addOtcepUP(int index)
{
    if(index!=-1)
    {
        qDebug()<<"addup"<<index;
    }
}

void Management::addOtcepDown(int index)
{
    if(index!=-1)
        qDebug()<<"addDown"<<index;
}

void Management::addOtcepClearAll()
{
    qDebug()<<"addupClearAll";
    QMap<QString,QString> m;
    m.clear();
    m["DEST"]="UVK";
    m["CMD"]="OTCEPS";
    m["CLEAR_ALL"]="1";
    MVP_Import::instance()->cmd->send_cmd(m);
}

void Management::setStatusPB(const StructProgressBar &set_statusPB)
{

    //  qmlPutNadviga.m_putnadviga=MVP_Import::instance()->gorka->PUT_NADVIG();
    qmlStatusPB=set_statusPB;
    emit statusPBChanged();

}
StructProgressBar Management::getStatusPB() const
{

    //  qmlPutNadviga.m_putnadviga=MVP_Import::instance()->gorka->PUT_NADVIG();
    return qmlStatusPB;
}


void Management::setPutNadviga(const StructPutNadviga &set_putnadviga)
{

    qmlPutNadviga = set_putnadviga;
    qDebug()<<"qmlPutNadviga.m_set_putnadviga"<<qmlPutNadviga.m_set_putnadviga;
//    if(qmlPutNadviga.m_chg_putnadviga==false)
    MVP_Import::instance()->setPutNadvig(qmlPutNadviga.m_set_putnadviga);

    qmlPutNadviga.m_set_putnadviga=MVP_Import::instance()->gorka->PUT_NADVIG();
    emit qmlPutNadvigaChanged();

}

StructPutNadviga Management::getPutNadviga()const
{
    return qmlPutNadviga;
}

//Управляет кнопкой стоп
int Management::getRegim()const
{
    return qmlRegim;
}
void Management::setRegim(const int &regim)
{
qDebug()<<regim;
    if (regim==ModelGroupGorka::regimStop){
        if (MVP_Import::instance()->gorka->STATE_REGIM()!=ModelGroupGorka::regimStop)
        {
            // проверяем отцепы в ходу
            int otcvhod=0;
            foreach (auto otcep, MVP_Import::instance()->otceps->l_otceps) {
                if ((otcep->STATE_ENABLED()) && (otcep->STATE_SP()!=otcep->STATE_SP())&&
                        (otcep->STATE_V()!=_undefV_)&&(otcep->STATE_V()>0)) otcvhod++;
            }
            if (otcvhod>0){
                qDebug() << "Отцепы в ходу!";
            }
            MVP_Import::instance()->setRegim(ModelGroupGorka::regimStop);
        }
    } else {
        MVP_Import::instance()->setRegim(regim);
    }
    qmlRegim = MVP_Import::instance()->gorka->STATE_REGIM();
    emit qmRegimChanged();
}

//Управляет курсором листвью
int Management::getCurrentItem()const
{
    return qmlCurentIndex;
}
void Management::setCurrentItem(const int &index)
{
    qmlCurentIndex = index;
//    emit qmlCurrentItemChanged();
}

//Управляет визиблами для редактирования
int Management::getEditSortir()const
{
    return qmlVisibleObject;
}
void Management::setEditSortir(const int &visible)
{
    qmlVisibleObject = visible;
    emit qmlVisibleObjectChanged();
}
//-------------------------------------------------
//Управляет сообщениями
QStringList Management::getListMsg()const
{
    return m_listMsg;
}
//Удаляем сообщения об ошибках по таймеру
void Management::addMsg(const QString &valMsg, int msg)
{
    if(m_listMsg.isEmpty()){
        qDebug()<<"Start Timer";
        timerDelMsg=true;
        emit timerDelMsgChanged();
    }
    m_listMsg.append(valMsg+QString::number(msg));
    emit listMsgChanged();
}

void Management::deleteMsg()
{
    if(!m_listMsg.isEmpty())
        m_listMsg.removeFirst();
    else {
        timerDelMsg=false;
        qDebug()<<"Stop Timer";
        emit timerDelMsgChanged();
    }
    emit listMsgChanged();
}

bool Management::getTimerDelMsg() const
{
    return timerDelMsg;
}
