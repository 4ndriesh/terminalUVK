#include "managemodel.h"
#include <QFileInfo>
#include <QDebug>
#include "mvp_import.h"
#include <QMetaProperty>


ManageModel::ManageModel(QObject *parent) : QObject(parent)
{
    m_uvkLive=0;
    m_newList=0;
    qmlCurentIndex=1;
}

void ManageModel::delOtcep(const int &index)
{
    MVP_Import::instance()->delOtcep(index);
}

void ManageModel::clearAllOtcep()
{
    MVP_Import::instance()->ClearAllOtcep();
}

void ManageModel::getRndChart()
{
    //    qmlStopPause=MVP_Import::instance()->gorka->STATE_REGIM();
    //    qmlX+=1;
    //    qmlY=qrand() % 10;
    //    emit setRndChart(qmlX,qmlY);
}

void ManageModel::addOtcep(const int & index)
{
    MVP_Import::instance()->incOtcep(index);
}

void ManageModel::qmlRegim(const int & regim)
{
    switch (regim) {
    case 0:
        m_stateBt.m_bef_regim=0;
        m_stateBt.m_wPause=false;
        m_stateBt.m_wStop=true;
        m_stateBt.m_wNadvig=false;
        emit stateBtChanged();
        break;
    case 1:
        m_stateBt.m_bef_regim=1;
        m_stateBt.m_wPause=false;
        m_stateBt.m_wStop=false;
        m_stateBt.m_wNadvig=true;
        emit  stateBtChanged();
        break;
    case 2:
        m_stateBt.m_bef_regim=2;
        m_stateBt.m_wPause=true;
        m_stateBt.m_wStop=false;
        m_stateBt.m_wNadvig=false;
        emit stateBtChanged();
        break;

    default:
        break;
    }
}
void ManageModel::accept()
{
    switch (m_stateBt.m_bef_regim) {

    case 0:
        setRegim(0);
        break;
    case 1:
        setPutNadviga(1);
        setRegim(1);
        break;
    case 2:
        setRegim(2);
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

//Добавляем сообщения об ошибках итд
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

//Удаляем сообщения об ошибках по таймеру
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

void ManageModel::setIndex(const int &index)
{
    qmlCurentIndex=index;
    emit qmlCurrentItemChanged();
}
//Ресет рельсовой цепи
void ManageModel::resetRChain(const QString &valRChain)
{
   qDebug()<<"Delete";
    MVP_Import::instance()->resetDSOBusyRc(m[valRChain]);
}
//Добавляем рельсовые цепи в список
void ManageModel::addRChain()
{

    m_qmlRChain.clear();
    m=MVP_Import::instance()->getDSOBusyRc();
    qDebug()<<m.count();
        foreach (auto rc_name, m.keys()) {
            m_qmlRChain.append(rc_name);
        }
        emit qmlRChainChanged();
}
