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
    notice=new Json("notice.json");
}
//Навигация по списку отцепов
void ManageModel::keyUpDown(const int &updown)
{
    switch (updown) {
    case VK_UP:
        if(m_qmlCurentIndex>0)
        {
            m_qmlCurentIndex--;
            setQmlCurrentItem(m_qmlCurentIndex);
            qmlRegim(10);
        }
        break;
    case VK_DOWN:
        if(m_qmlCurentIndex<ViewOtcepsModel::instance().countEnabled()-1)
        {
            m_qmlCurentIndex++;
            setQmlCurrentItem(m_qmlCurentIndex);
            qmlRegim(10);
        }
        break;
    }
    return;
}
//Удалить один отцеп
void ManageModel::delOtcep(const int &index)
{
    if(m_stateBt.m_regim!=1 && m_qmlCurentIndex>=0){
        MVP_Import::instance()->delOtcep(m_qmlCurentIndex+index);
        if(m_qmlCurentIndex!=0){
            m_qmlCurentIndex--;
            setQmlCurrentItem(m_qmlCurentIndex);
        }
    }
    return;
}
//Удалить все отцепы
void ManageModel::clearAllOtcep()
{
    setQmlCurrentItem(0);
    MVP_Import::instance()->ClearAllOtcep();
    m_stateBt.m_wCursor=false;
    return;
}

void ManageModel::addOtcep(const int & index)
{
    MVP_Import::instance()->incOtcep(index);
    return;
}


void ManageModel::qmlRegim(const int & regim)
{
    if(m_stateBt.m_editing==1 && regim<=3){
        addMsg("Закончить режим <<ВВОД СЛ>>");
        return;
    }
    switch (regim) {
    case 0:
        m_stateBt.m_bef_regim=0;
        m_stateBt.m_wStop=true;
        break;
    case 1:
        m_stateBt.m_bef_regim=1;
        m_stateBt.m_wNadvig=true;
        break;
    case 2:
        m_stateBt.m_bef_regim=2;
        m_stateBt.m_wPause=true;
        break;
    case 3:
        if(m_stateBt.m_editing==1 || (m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0)){
            m_stateBt.m_bef_regim=3;
            m_stateBt.m_wCursor=true;
            setMsgEvent(QString(notice->getMXml("delOtcep","event")).arg(m_qmlCurentIndex+1));
        }
        else{addMsg(notice->getMXml("delOtcep","msg"));}
        break;
        //Вставить до
    case 4:
        if(m_stateBt.m_editing==1 || (m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0)){
            m_stateBt.m_bef_regim=4;
            m_stateBt.m_wCursor=true;
            setMsgEvent(QString(notice->getMXml("insertUp","event")));
        }
        else{addMsg(notice->getMXml("insertUp","msg"));}
        break;
        //Вставить после
    case 5:
        if(m_stateBt.m_editing==1 || (m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0)){
            m_stateBt.m_bef_regim=5;
            m_stateBt.m_wCursor=true;
            setMsgEvent(QString(notice->getMXml("insertDown","event")));
        }
        else{addMsg(notice->getMXml("insertDown","msg"));}
        break;
        //Изменить путь
    case 6:
        if(m_stateBt.m_editing==1 || (m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0)){
            m_stateBt.m_bef_regim=6;
            m_stateBt.m_wCursor=true;
            setMsgEvent(QString(notice->getMXml("inputPut","event")).arg(m_textInput));
        }
        else{addMsg(notice->getMXml("inputPut","msg"));}
        break;
        //удалить все
    case 7:
        if(m_stateBt.m_editing==1 || (m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0)){
            m_stateBt.m_bef_regim=7;
            m_stateBt.m_wCursor=true;
            setMsgEvent(notice->getMXml("clearAll","event"));
        }
        else{addMsg(notice->getMXml("clearAll","msg"));}
        break;
    case 10:
        m_stateBt.m_bef_regim=10;
        break;
    case 11:
        m_stateBt.m_wCursor=false;
        setMsgEvent("");
        m_stateBt.m_wPause=false;
        m_stateBt.m_wStop=false;
        m_stateBt.m_wNadvig=false;
        break;
    }
    emit stateBtChanged();
    return;
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
    case 3:
        delOtcep(1);
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        emit textInputChanged();
        break;
    case 7:
        clearAllOtcep();

        break;

    case 10:
        addMsg("Команда не задана");
        break;
    }
    qmlRegim(10);
    qmlRegim(11);
    return;
}

void ManageModel::setPutNadviga(const int &putNadviga)
{    
    MVP_Import::instance()->setPutNadvig(putNadviga);
    return;
}

void ManageModel::setRegim(const int &regim)
{
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
    return;
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
    return;
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
    return;
}

bool ManageModel::getTimerDelMsg() const
{
    return timerDelMsg;
}

//Установить путь
void ManageModel::inputPut(const int &numberPut)
{

    m_textInput=numberPut;
    if(m_stateBt.m_bef_regim==4){
        addOtcep(m_qmlCurentIndex+1);
        qmlRegim(6);
        //        setQmlCurrentItem(m_qmlCurentIndex);
        accept();
        return;
    }
    else if(m_stateBt.m_bef_regim==5){
        if(ViewOtcepsModel::instance().countEnabled()==0){
            addOtcep(m_qmlCurentIndex+1);
        }
        else{
            addOtcep(m_qmlCurentIndex+2);
            keyUpDown(VK_DOWN);
        }
        qmlRegim(6);
        //        setQmlCurrentItem(m_qmlCurentIndex);
        accept();
        return;
    }
    else{
        qmlRegim(6);
    }
    return;
}
//Режим редактирования
void ManageModel::setRegimEdit()
{
    if(m_stateBt.m_regim==1 || m_stateBt.m_regim==2){
        addMsg("Перейти в режим <<КОНЕЦ РОСПУСКА>>");
        return;
    }

    if(m_stateBt.m_editing==0){clearAllOtcep();}
    m_stateBt.m_editing=!m_stateBt.m_editing;
    m_qmlCurentIndex=0;
    emit qmlCurrentItemChanged();
    emit stateBtChanged();
    if(m_newList)
        ViewOtcepsModel::instance().sortirArrived(ViewOtcepsModel::instance().tmpSrt);

    return;
}
//Обработка клавы
void ManageModel::keyDown(const int &key, const bool &ctrl)
{
    qmlRegim(11);
    switch (key) {
    case VK_F5:
        emit openRChainChanged();
        break;

    case VK_F4:
        setRegimEdit();
        break;

    case VK_RETURN:
        accept();
        break;

    case VK_F1:
        //Роспуск 1
        qmlRegim(1);
        break;

    case VK_F2:
        //Пауза
        qmlRegim(2);
        break;

    case VK_F3:
        //Стоп
        qmlRegim(0);
        break;

    case VK_UP:
        //UP
        keyUpDown(VK_UP);
        break;

    case VK_DOWN:
        //DOWN
        keyUpDown(VK_DOWN);
        break;

    case VK_INSERT:
        //Вставить после
        if(ctrl){
            qmlRegim(5);
            break;
        }
        //Вставить до
        qmlRegim(4);
        break;

    case VK_DELETE:
        //Удалить все
        if(ctrl){
            qmlRegim(7);
            break;
        }
        //Удалить один
        qmlRegim(3);
        break;

    case VK_ESCAPE:
        qmlRegim(10);
        break;

    case 81:
        if(ctrl)inputPut(1);
        break;

    case 87:
        if(ctrl)inputPut(2);
        break;

    case 69:
        if(ctrl)inputPut(3);
        break;

    case 82:
        if(ctrl)inputPut(4);
        break;

    case 84:
        if(ctrl)inputPut(5);
        break;

    case 89:
        if(ctrl)inputPut(6);
        break;

    case 85:
        if(ctrl)inputPut(7);
        break;

    case 73:
        if(ctrl)inputPut(8);
        break;

    case 79:
        if(ctrl)inputPut(9);
        break;

    default:
        break;

    }
    return;
}
