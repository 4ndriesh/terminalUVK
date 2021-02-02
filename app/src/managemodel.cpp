#include "managemodel.h"
#include <QFileInfo>
#include <QDebug>
#include "mvp_import.h"
#include <QMetaProperty>


ManageModel::ManageModel(QObject *parent) : QObject(parent)
{
    m_uvkLive=0;
    m_newList=0;
    qmlCurentIndex=0;
//        for(int i=0;i<10;i++)
//        m_qmlRChain.append("123123");
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
    if(m_stateBt.m_editing && qmlCurentIndex>=0)
        MVP_Import::instance()->incOtcep(index);
}

void ManageModel::qmlRegim(const int & regim)
{
    switch (regim) {
    case 0:
        m_stateBt.m_bef_regim=0;
        //        m_stateBt.m_wPause=false;
        m_stateBt.m_wStop=true;
        //        m_stateBt.m_wNadvig=false;
        emit stateBtChanged();
        break;
    case 1:
        m_stateBt.m_bef_regim=1;
        //        m_stateBt.m_wPause=false;
        //        m_stateBt.m_wStop=false;
        m_stateBt.m_wNadvig=true;
        emit  stateBtChanged();
        break;
    case 2:
        m_stateBt.m_bef_regim=2;
        m_stateBt.m_wPause=true;
        //        m_stateBt.m_wStop=false;
        //        m_stateBt.m_wNadvig=false;
        emit stateBtChanged();
        break;
    case 10:
        qDebug()<<"Команда не задана";
        m_stateBt.m_bef_regim=10;
        m_stateBt.m_wPause=false;
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

    case 10:
        qDebug()<<"Команда не задана";
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
//Установить путь
void ManageModel::inputPut(const int &numberPut)
{
    m_textInput=numberPut;
    emit textInputChanged();
}
//Установить путь
void ManageModel::setRegimEdit()
{
    if(m_stateBt.m_regim==1){
        addMsg("Роспуск",1);
    }
    else{
        m_stateBt.m_editing=!m_stateBt.m_editing;
        qmlCurentIndex=0;
        emit qmlCurrentItemChanged();
        emit stateBtChanged();
    }
}
//Обработка клавы
void ManageModel::keyDown(const DWORD &key)
{
    qDebug()<<"vkCode"<<key ;
    if(bWinKey == false)
        return;

    switch (key) {
    case VK_TAB:
        setRegimEdit();
        break;
    case VK_RETURN:
        accept();
        break;
    case VK_LCONTROL:
        //Роспуск 1
        qmlRegim(1);
        //        m_stateBt.m_bef_putNadviga=1;
        break;

    case VK_LSHIFT:
        //Пауза
        qmlRegim(2);
        break;
    case VK_RSHIFT:
        //Стоп
        qmlRegim(0);
        break;
    case VK_UP:
        //UP
        if(m_stateBt.m_editing && qmlCurentIndex>0)
        {
            qmlCurentIndex--;
            emit qmlCurrentItemChanged();
        }
        break;
        //            case  65:
    case VK_DOWN:
        //DOWN
        if(m_stateBt.m_editing)
        {
            qmlCurentIndex++;
            emit qmlCurrentItemChanged();
        }
        break;

    case VK_NEXT:
        //Вставить до
        addOtcep(qmlCurentIndex);
        break;
    case VK_PRIOR:
        //Вставить после
        addOtcep(qmlCurentIndex+1);
        break;
    case VK_DELETE:
        //Удалить все
        clearAllOtcep();
        break;
    case VK_F12:
        //Удалить
        delOtcep(qmlCurentIndex+1);
        break;
    case VK_F1:
        inputPut(1);
        break;
    case VK_F2:
        m_textInput=3;
        emit textInputChanged();
        break;
    case VK_LEFT:
        qmlCurentIndex--;
        emit qmlCurrentItemChanged();
        break;
    case VK_RIGHT:
        qmlCurentIndex++;
        emit qmlCurrentItemChanged();
        break;
    default:
        break;

    }
}
