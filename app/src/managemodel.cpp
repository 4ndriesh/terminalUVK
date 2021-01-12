#include "managemodel.h"
#include <QFileInfo>
#include <QDebug>
#include "mvp_import.h"
#include <QMetaProperty>



ManageModel::ManageModel(QObject *parent) : QObject(parent)
{
    //     qmlManagerButton->m_regim=0;
    for(int msg=0; msg<2;msg++)
        addMsg("Hello Word",msg);
}

void ManageModel::deleteFromList()
{

}

void ManageModel::getRndChart()
{
    //    qmlStopPause=MVP_Import::instance()->gorka->STATE_REGIM();
    //    qmlX+=1;
    //    qmlY=qrand() % 10;
    //    emit setRndChart(qmlX,qmlY);
}

void ManageModel::addOtcepUP(int index)
{
    if(index!=-1)
    {
        qDebug()<<"addup"<<index;
    }
}

void ManageModel::addOtcepDown(int index)
{
    if(index!=-1)
        qDebug()<<"addDown"<<index;
}

void ManageModel::addOtcepClearAll()
{
    qDebug()<<"addupClearAll";
    QMap<QString,QString> m;
    m.clear();
    m["DEST"]="UVK";
    m["CMD"]="OTCEPS";
    m["CLEAR_ALL"]="1";
    MVP_Import::instance()->cmd->send_cmd(m);
}

void ManageModel::setStatusPB(const StructProgressBar &set_statusPB)
{
    //  qmlPutNadviga.m_putnadviga=MVP_Import::instance()->gorka->PUT_NADVIG();
    qmlStatusPB=set_statusPB;
    emit statusPBChanged();

}

StructProgressBar ManageModel::getStatusPB() const
{

    //  qmlPutNadviga.m_putnadviga=MVP_Import::instance()->gorka->PUT_NADVIG();
    return qmlStatusPB;
}

void ManageModel::accept()
{
    switch (acceptRegim) {

    case 0:
        setRegim(0);
        break;
    case 1:
        setRegim(1);
        setPutNadviga(1);
        break;
    case 2:
        setRegim(2);
        break;
    case 3:
        setRegim(1);
        setPutNadviga(2);
        break;
    default:
        break;
    }
}

void ManageModel::setPutNadviga(const int &putNadviga)
{
    MVP_Import::instance()->setPutNadvig(putNadviga);
}

void ManageModel::setRegim(const int &regim)
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
}

//-------------------------------------------------


//Удаляем сообщения об ошибках по таймеру
void ManageModel::addMsg(const QString &valMsg, int msg)
{
    if(m_listMsg.isEmpty()){
        qDebug()<<"Start Timer";
        timerDelMsg=true;
        emit timerDelMsgChanged();
    }
    m_listMsg.append(valMsg+QString::number(msg));
    emit listMsgChanged();
}

void ManageModel::deleteMsg()
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

bool ManageModel::getTimerDelMsg() const
{
    return timerDelMsg;
}
