#include "managemodel.h"
#include <QFileInfo>
#include <QDebug>
#include "mvp_import.h"
#include <QMetaProperty>
#include "otcepsmodel.h"
#include "vagonsmodel.h"


ManageModel::ManageModel(QObject *parent) : QObject(parent)
{

    m_uvkLive=0;
    m_newList=false;
    m_selectHook=0;
    m_qmlCurrentIndex=0;
    m_textInput="";
    m_focus=1;
    notice=new Json("notice.json");
}

//Удалить один отцеп
void ManageModel::delOtcep(const int &index)
{
    if(m_stateBt.m_regim!=1 && m_qmlCurrentIndex>=0){
        MVP_Import::instance()->delOtcep(m_qmlCurrentIndex+index);
        if(m_qmlCurrentIndex!=0){
            m_qmlCurrentIndex--;
            setqmlCurrentIndex(m_qmlCurrentIndex);
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

void ManageModel::qmlRegim(const int & regim)
{
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
        //        if(m_stateBt.m_editing==1 || (m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0)){
        m_stateBt.m_bef_regim=3;
        m_stateBt.m_wCursor=true;
        setmsgEvent(QString(notice->getMXml("delOtcep","event")).arg(m_qmlCurrentIndex+1));
        //        }
        //        else{addMsg(notice->getMXml("delOtcep","msg"));}
        break;
        //Вставить до
    case 4:
        //        if(m_stateBt.m_editing==1 || (m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0)){
        m_stateBt.m_bef_regim=4;
        m_stateBt.m_wCursor=true;
        setmsgEvent(QString(notice->getMXml("insertUp","event")));
        //        }
        //        else{addMsg(notice->getMXml("insertUp","msg"));}
        break;
        //Вставить после
    case 5:
        //        if(m_stateBt.m_editing==1 || (m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0)){
        m_stateBt.m_bef_regim=5;
        m_stateBt.m_wCursor=true;
        setmsgEvent(QString(notice->getMXml("insertDown","event")));
        //        }
        //        else{addMsg(notice->getMXml("insertDown","msg"));}
        break;
        //Изменить путь
    case 6:
        //        if(m_stateBt.m_editing==1 || (m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0)){
        m_stateBt.m_bef_regim=6;
        m_stateBt.m_wCursor=true;
        setmsgEvent(QString(notice->getMXml("inputPut","event")).arg(m_textInput));
        //        }
        //        else{addMsg(notice->getMXml("inputPut","msg"));}
        break;
        //удалить все
    case 7:
        //        if(m_stateBt.m_editing==1 || (m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0)){
        m_stateBt.m_bef_regim=7;
        m_stateBt.m_wCursor=true;
        setmsgEvent(notice->getMXml("clearAll","event"));
        //        }
        //        else{addMsg(notice->getMXml("clearAll","msg"));}
        break;
    case 8:
        //        if(m_stateBt.m_regim!=1){
        m_stateBt.m_bef_regim=8;
        m_stateBt.m_wCursor=true;
        setmsgEvent(QString(notice->getMXml("setCurrentOtcep","event")).arg(m_qmlCurrentIndex+1));
        //        }
        //        else{addMsg(notice->getMXml("setCurrentOtcep","msg"));}
        break;
    case 12:
        setqmlCurrentIndex(0);
        if(m_stateBt.m_regim==0 && m_newList==true){
            m_stateBt.m_wGetList=true;
            m_stateBt.m_bef_regim=12;
        }
        break;
    case 10:
        m_stateBt.m_bef_regim=10;
        m_textInput="";
        break;
    case 11:
        m_stateBt.m_wCursor=false;
        setmsgEvent("");
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
    case 8:
        setCurrentOtcep();
        break;
    case 9:
        break;
    case 12:
        OtcepsModel::instance().sortirArrived(OtcepsModel::instance().tmpSrt);
        break;

    case 10:
        addMsg("Команда не задана");
        break;
    }
    qmlRegim(10);
    qmlRegim(11);
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
    if(m_textInput.length()<2 && m_focus==2)
        m_textInput.append(numberPut);
    else if(numberPut!="0")
        m_textInput=numberPut;
    //    if(m_textInput.length()==2 && m_qmlCurrentIndex==count && m_focus==2){
    //        accept();
    //        qmlRegim(5);
    //        m_textInput="";
    //        setfocus(1);
    //        setqmlCurrentIndex(m_qmlCurrentIndex);
    //        return;
    //    }

    int countEnabled=OtcepsModel::instance().countEnabled();
    if(countEnabled==-1 && m_stateBt.m_bef_regim==5) {
        m_stateBt.m_bef_regim=4;
    }
    qDebug()<<m_stateBt.m_bef_regim;
    if(m_stateBt.m_bef_regim==4){
        addOtcep(m_qmlCurrentIndex+1);
        setqmlCurrentIndex(m_qmlCurrentIndex);
        qmlRegim(6);
        accept();
        setfocus(2);
        return;
    }
    else if(m_stateBt.m_bef_regim==5){
        addOtcep(m_qmlCurrentIndex+2);
        setqmlCurrentIndex(m_qmlCurrentIndex+1);
        qmlRegim(6);
        accept();
        setfocus(2);
        return;
    }
    else if(countEnabled>=0) {
        qmlRegim(6);
    }
    return;
}


void ManageModel::setPositionVagons()
{
    int countRow=0;
    while(VagonsModel::instance().get(countRow)["STATE_NUM_OTCEP"]!=m_qmlCurrentIndex+1 && countRow<99)
    {
        countRow++;
    }
    VagonsModel::instance().m_qmlCurrentIndex=countRow;
    emit VagonsModel::instance().qmlCurrentIndexChanged();
}

void ManageModel::updateOtcep()
{
    MVP_Import::instance()->updateOtceps();
}

//Навигация по списку отцепов
void ManageModel::keyUpDown(const int &updown)
{
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
    qmlRegim(10);
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
        qmlRegim(12);
        //        setRegimEdit();
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
            if(m_stateBt.m_bef_regim==6)
            {
                accept();
            }
            qmlRegim(5);
            break;
        }
        //Вставить до
        if(m_stateBt.m_bef_regim==6)
        {
            accept();
        }
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
        qmlRegim(10);
        break;

    }
    return;
}
