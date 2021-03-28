#include "managemodel.h"
#include <QFileInfo>
#include <QDebug>
#include "mvp_import.h"
#include <QMetaProperty>
#include "otcepsmodel.h"
#include "vagonsmodel.h"
#include <QUrl>

ManageModel::ManageModel(QObject *parent) : QObject(parent)
{
    m_uvkLive=false;
    m_newList=false;
    m_selectHook=0;
    m_qmlCurrentIndex=0;
    m_textInput="";
    m_focus=1;

//    notice=new Json("settings/notice.json");
}

//Удалить один отцеп
void ManageModel::delOtcep()
{
    if(m_stateBt.m_regim!=1 && m_qmlCurrentIndex>=0){
        MVP_Import::instance()->delOtcep(m_qmlCurrentIndex+1);
        if(m_qmlCurrentIndex!=0){
            setqmlCurrentIndex(m_qmlCurrentIndex-1);
        }
    }
    return;
}
//Удалить все отцепы
void ManageModel::clearAllOtcep()
{
    setqmlCurrentIndex(0);
    MVP_Import::instance()->ClearAllOtcep();
    m_stateBt.m_wCursor=false;
    return;
}

void ManageModel::addOtcep(const int & index)
{
    MVP_Import::instance()->incOtcep(index);
    return;
}

void ManageModel::qmlRegim(const int & bef_regim)
{
    switch (bef_regim) {
    case Stop:
        m_stateBt.m_bef_regim=Stop;
        m_stateBt.m_wStop=true;
        break;
    case Rospusk:
        m_stateBt.m_bef_regim=Rospusk;
        m_stateBt.m_wNadvig=true;
        break;
    case Pause:
        m_stateBt.m_bef_regim=Pause;
        m_stateBt.m_wPause=true;
        break;
    case DelOtcep:
        //        if(m_stateBt.m_editing==1 || (m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0)){
        m_stateBt.m_bef_regim=DelOtcep;
        m_stateBt.m_wCursor=true;
        setmsgEvent(QString(notice->getMXml("delOtcep","event")).arg(m_qmlCurrentIndex+1));
        //        }
        //        else{addMsg(notice->getMXml("delOtcep","msg"));}
        break;
        //Вставить до
    case InsertUp:
        //        if(m_stateBt.m_editing==1 || (m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0)){
        m_stateBt.m_bef_regim=InsertUp;
        m_stateBt.m_wCursor=true;
        setmsgEvent(QString(notice->getMXml("insertUp","event")));
        //        }
        //        else{addMsg(notice->getMXml("insertUp","msg"));}
        break;
        //Вставить после
    case InsertDown:
        //        if(m_stateBt.m_editing==1 || (m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0)){
        m_stateBt.m_bef_regim=InsertDown;
        m_stateBt.m_wCursor=true;
        setmsgEvent(QString(notice->getMXml("insertDown","event")));
        //        }
        //        else{addMsg(notice->getMXml("insertDown","msg"));}
        break;
        //Изменить путь
    case InputPut:
        //        if(m_stateBt.m_editing==1 || (m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0)){
        m_stateBt.m_bef_regim=InputPut;
        m_stateBt.m_wCursor=true;
        setmsgEvent(QString(notice->getMXml("inputPut","event")).arg(m_textInput));
        //        }
        //        else{addMsg(notice->getMXml("inputPut","msg"));}
        break;
        //удалить все
    case DelAllOtcep:
        //        if(m_stateBt.m_editing==1 || (m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0)){
        m_stateBt.m_bef_regim=DelAllOtcep;
        m_stateBt.m_wCursor=true;
        setmsgEvent(notice->getMXml("clearAll","event"));
        //        }
        //        else{addMsg(notice->getMXml("clearAll","msg"));}
        break;
    case SetCurrentOtcep:
        //        if(m_stateBt.m_regim!=1){
        m_stateBt.m_bef_regim=SetCurrentOtcep;
        m_stateBt.m_wCursor=true;
        setmsgEvent(QString(notice->getMXml("setCurrentOtcep","event")).arg(m_qmlCurrentIndex+1));
        //        }
        //        else{addMsg(notice->getMXml("setCurrentOtcep","msg"));}
        break;
    case GetNewList:
//        for(int i=1;i<100;i++)
//            addOtcep(i);
        setqmlCurrentIndex(0);
        if(m_stateBt.m_regim==Stop && m_newList==true){
            m_stateBt.m_wGetList=true;
            m_stateBt.m_bef_regim=GetNewList;
        }
        else if(m_stateBt.m_regim!=Stop){addMsg(notice->getMXml("getNewList","msg"));}
        else if(m_newList==false){addMsg(notice->getMXml("getNewList","msg2"));}
        break;
    case InputVag:
        m_stateBt.m_bef_regim=InputVag;
        m_stateBt.m_wCursor=true;
        setmsgEvent(QString(notice->getMXml("inputVag","event")).arg(m_textInput));
        break;
    case Escape:
        m_stateBt.m_bef_regim=Escape;
        m_textInput="";
        setmsgEvent("");
        m_stateBt.m_wCursor=false;
        m_stateBt.m_wPause=false;
        m_stateBt.m_wStop=false;
        m_stateBt.m_wNadvig=false;
        m_stateBt.m_wGetList=false;
        break;
    }

    emit stateBtChanged();
    return;
}
void ManageModel::accept()
{
    switch (m_stateBt.m_bef_regim) {

    case Stop:
        setRegim(Stop);
        break;
    case Rospusk:
        setPutNadviga(1);
        setRegim(Rospusk);
        break;
    case Pause:
        setRegim(Pause);
        break;
    case DelOtcep:
        delOtcep();
        break;
    case InsertUp:
        break;
    case InsertDown:
        break;
    case InputPut:
        emit textInputChanged();
        break;
    case InputVag:
        emit textInputChanged();
        break;
    case DelAllOtcep:
        clearAllOtcep();
        break;
    case SetCurrentOtcep:
        setCurrentOtcep();
        break;
    case GetNewList:
        OtcepsModel::instance().sortirArrived(OtcepsModel::instance().tmpSrt);
        break;

    case Escape:
        addMsg("Команда не задана");
        break;
    }
    qmlRegim(Escape);
    return;
}

void ManageModel::setCurrentOtcep()
{
    MVP_Import::instance()->setCurOtcep(m_qmlCurrentIndex+1);
    return;
}
void ManageModel::setPutNadviga(const int &putNadviga)
{
    MVP_Import::instance()->setPutNadvig(putNadviga);
    return;
}

void ManageModel::setRegim(const int &regim)
{
    setqmlCurrentIndex(0);
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
        m_timerDelMsg=true;
    }
    m_listMsg.append(valMsg);
    std::reverse(m_listMsg.begin(), m_listMsg.end());
    emit timerDelMsgChanged();
    emit listMsgChanged();
    return;
}

//Удаляем сообщения об ошибках по таймеру
void ManageModel::deleteMsg()
{
    if(!m_listMsg.isEmpty())
        m_listMsg.removeLast();
    else {
        m_timerDelMsg=false;
    }
    emit timerDelMsgChanged();
    emit listMsgChanged();
    return;
}

//Установить путь
void ManageModel::inputPut(const QString &numberPut)
{
    int countEnabled=OtcepsModel::instance().countEnabled();
    if(m_textInput.length()<2 && m_focus==2)
        m_textInput.append(numberPut);
    else if(m_textInput.length()==2 && m_focus==2){
        m_textInput=numberPut;
    }
    else if(m_focus==1 && numberPut!="0")
        m_textInput=numberPut;

    if(countEnabled==-1)m_stateBt.m_bef_regim=InsertUp;

    if(m_stateBt.m_bef_regim==InsertUp){
        setfocus(1);
        addOtcep(m_qmlCurrentIndex+1);
        MVP_Import::instance()->setOtcepSP(m_qmlCurrentIndex+1,m_textInput.toInt());
        qmlRegim(Escape);
        setqmlCurrentIndex(m_qmlCurrentIndex);
        qmlRegim(InputVag);
        setfocus(2);
        return;
    }
    else if(m_stateBt.m_bef_regim==InsertDown){
        setfocus(1);
        addOtcep(m_qmlCurrentIndex+2);
        MVP_Import::instance()->setOtcepSP(m_qmlCurrentIndex+2,m_textInput.toInt());
        qmlRegim(Escape);
        setqmlCurrentIndex(m_qmlCurrentIndex+1);
        qmlRegim(InputVag);
        setfocus(2);
        return;
    }
    else if(countEnabled>=0) {
        if(m_focus==1)
            qmlRegim(InputPut);
        else if(m_focus==2)
            qmlRegim(InputVag);
    }
    return;
}

int ManageModel::setPositionVagons()
{
    int countRow=0;
    while(VagonsModel::instance().get(countRow)["STATE_NUM_OTCEP"]!=m_qmlCurrentIndex+1)
    {
        countRow++;
        if(countRow==VagonsModel::instance().rowCount())return -1;
    }
    VagonsModel::instance().setqmlCurrentIndex(countRow);
    return countRow;
}

void ManageModel::updateOtcep()
{
    MVP_Import::instance()->updateOtceps();
}

//Навигация по списку отцепов
void ManageModel::keyUpDown(const int &updown)
{
    qmlRegim(Escape);
    switch (updown) {
    case VK_UP:
        if(m_qmlCurrentIndex>0)
        {
            m_qmlCurrentIndex--;
            emit qmlCurrentIndexChanged();
            setPositionVagons();
        }
        break;
    case VK_DOWN:
        if(m_qmlCurrentIndex<OtcepsModel::instance().countEnabled())
        {
            m_qmlCurrentIndex++;
            emit qmlCurrentIndexChanged();
            setPositionVagons();
        }
        break;
    case VK_RIGHT:
        setfocus(2);
        break;
    case VK_LEFT:
        setfocus(1);
        break;
    }
    return;
}

//Обработка клавы
void ManageModel::keyDown(const int &key, const bool &ctrl)
{    
    switch (key) {
    case VK_F5:
        emit openRChainChanged();
        break;

    case VK_F4:
        qmlRegim(GetNewList);
        break;

    case VK_RETURN:
        accept();
        break;

    case VK_F1:
        //Роспуск 1
        qmlRegim(Escape);
        qmlRegim(Rospusk);
        break;

    case VK_F2:
        //Пауза
        qmlRegim(Escape);
        qmlRegim(Pause);
        break;

    case VK_F3:
        //Стоп
        qmlRegim(Escape);
        qmlRegim(Stop);
        break;

    case VK_RIGHT:
        //UP
        keyUpDown(VK_RIGHT);
        break;
    case VK_LEFT:
        //UP
        keyUpDown(VK_LEFT);
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
            if(m_stateBt.m_bef_regim==InputVag)accept();
            qmlRegim(Escape);
            qmlRegim(InsertDown);
            break;
        }
        //Вставить до
        if(m_stateBt.m_bef_regim==InputVag)accept();
        qmlRegim(Escape);
        qmlRegim(InsertUp);
        break;

    case VK_DELETE:
        qmlRegim(Escape);
        //Удалить все
        if(ctrl){
            qmlRegim(DelAllOtcep);
            break;
        }
        //Удалить один
        qmlRegim(DelOtcep);
        break;

    case VK_ESCAPE:
        qmlRegim(Escape);
        break;

    case 81:
        if(ctrl)inputPut("1");
        break;

    case 87:
        if(ctrl)inputPut("2");
        break;

    case 69:
        if(ctrl)inputPut("3");
        break;

    case 82:
        if(ctrl)inputPut("4");
        break;

    case 84:
        if(ctrl)inputPut("5");
        break;

    case 89:
        if(ctrl)inputPut("6");
        break;

    case 85:
        if(ctrl)inputPut("7");
        break;

    case 73:
        if(ctrl)inputPut("8");
        break;

    case 79:
        if(ctrl)inputPut("9");
        break;
    case 80:
        if(ctrl)inputPut("0");
        break;

    default:
        qmlRegim(Escape);
        break;

    }
    return;
}
