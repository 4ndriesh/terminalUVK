#include "managemodel.h"
#include <QFileInfo>
#include <QDebug>
#include "mvp_import.h"
#include <QMetaProperty>
#include "viewotcepsmodel.h"



ManageModel::ManageModel(QObject *parent) : QObject(parent)
{
    m_uvkLive=0;
    m_newList=0;
    //    m_qmlCurentIndex=0;
//            for(int i=0;i<10;i++)
//            m_qmlRChain.append("123123");
}
//Навигация по списку отцепов
void ManageModel::keyUpDown(const int &updown)
{
    switch (updown) {
    case VK_UP:
        if(m_stateBt.m_editing && m_qmlCurentIndex>0)
        {
            m_qmlCurentIndex--;
            setQmlCurrentItem(m_qmlCurentIndex);
        }
        break;
    case VK_DOWN:
        if(m_stateBt.m_editing && m_qmlCurentIndex<ViewOtcepsModel::instance().countEnabled()-1)
        {
            m_qmlCurentIndex++;
            setQmlCurrentItem(m_qmlCurentIndex);
        }
        break;
    }
}
//Удалить один отцеп
void ManageModel::delOtcep(const int &index)
{
    MVP_Import::instance()->delOtcep(m_qmlCurentIndex+index);
}
//Удалить все отцепы
void ManageModel::clearAllOtcep()
{
    setQmlCurrentItem(0);
    MVP_Import::instance()->ClearAllOtcep();
}

void ManageModel::addOtcep(const int & index)
{
    if(m_stateBt.m_editing && m_qmlCurentIndex>=0)
        MVP_Import::instance()->incOtcep(m_qmlCurentIndex+index);
}

void ManageModel::qmlRegim(const int & regim)
{
    if(m_stateBt.m_editing==1)return;
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
//        if(m_stateBt.m_regim==1){
            m_stateBt.m_bef_regim=2;
            m_stateBt.m_wPause=true;
//            m_stateBt.m_wStop=false;
//            m_stateBt.m_wNadvig=false;
            emit stateBtChanged();
//        }
        break;
    case 10:
        qDebug()<<"Команда не задана";
        m_stateBt.m_bef_regim=10;
        emit stateBtChanged();
        break;

    default:
        m_stateBt.m_wPause=false;
        m_stateBt.m_wStop=false;
        m_stateBt.m_wNadvig=false;
//        emit stateBtChanged();
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
void ManageModel::addMsg(const QString &valMsg)
{
    if(m_listMsg.isEmpty()){
        qDebug()<<"Start Timer";
        timerDelMsg=true;
        emit timerDelMsgChanged();
    }
    m_listMsg.append(valMsg);
    std::reverse(m_listMsg.begin(), m_listMsg.end());
    emit listMsgChanged();
}

//Удаляем сообщения об ошибках по таймеру
void ManageModel::deleteMsg()
{
    if(!m_listMsg.isEmpty())
        m_listMsg.removeLast();
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

//Установить путь
void ManageModel::inputPut(const int &numberPut)
{
    m_textInput=numberPut;
    emit textInputChanged();
}
//Режим редактирования
void ManageModel::setRegimEdit()
{
    if(m_stateBt.m_regim==1){
        addMsg("Роспуск");
    }
    else{
        m_stateBt.m_editing=!m_stateBt.m_editing;
        if(m_newList)
            ViewOtcepsModel::instance().sortirArrived(ViewOtcepsModel::instance().tmpSrt);
        m_qmlCurentIndex=0;
        emit qmlCurrentItemChanged();
        emit stateBtChanged();
    }
}
//Обработка клавы
void ManageModel::keyDown(const DWORD &key)
{

    qDebug()<<"vkCode"<<key ;
    switch (key) {
    case VK_F5:
        emit openRChainChanged();
        break;
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
        keyUpDown(VK_UP);
        break;
        //            case  65:
    case VK_DOWN:
        //DOWN
        keyUpDown(VK_DOWN);
        break;

    case VK_NEXT:
        //Вставить до
        addOtcep(0);
        break;
    case VK_PRIOR:
        //Вставить после
        addOtcep(1);
        break;
    case VK_DELETE:
        //Удалить все
        clearAllOtcep();
        break;
    case VK_F12:
        //Удалить
        delOtcep(1);
        break;
    case VK_F1:
        inputPut(1);
        break;
    case VK_F2:
        m_textInput=3;
        emit textInputChanged();
        break;
    case VK_LEFT:
        m_qmlCurentIndex--;
        emit qmlCurrentItemChanged();
        break;
    case VK_RIGHT:
        m_qmlCurentIndex++;
        emit qmlCurrentItemChanged();
        break;
    default:
        break;

    }
}
