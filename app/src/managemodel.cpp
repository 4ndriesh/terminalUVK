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
    if(m_stateBt.m_bef_regim>=3 && m_stateBt.m_bef_regim<=5 )
        return;
    switch (updown) {
    case VK_UP:
        if(m_stateBt.m_regim!=1 && m_qmlCurentIndex>0)
        {
            m_qmlCurentIndex--;
            setQmlCurrentItem(m_qmlCurentIndex);
        }
        break;
    case VK_DOWN:
        if(m_stateBt.m_regim!=1 && m_qmlCurentIndex<ViewOtcepsModel::instance().countEnabled()-1)
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
    if(m_stateBt.m_regim!=1 && m_qmlCurentIndex>=0){
        MVP_Import::instance()->delOtcep(m_qmlCurentIndex+index);
    }
}
//Удалить все отцепы
void ManageModel::clearAllOtcep()
{
    setQmlCurrentItem(0);

    //    if(m_stateBt.m_editing && m_qmlCurentIndex>=0){
    MVP_Import::instance()->ClearAllOtcep();
    m_stateBt.m_wCursor=false;
    //    }
}

void ManageModel::addOtcep(const int & index)
{

    MVP_Import::instance()->incOtcep(index);
    //    MVP_Import::instance()->incOtcep(m_qmlCurentIndex+index);

}

void ManageModel::qmlRegimEditing(const int & regim)
{

    switch (regim) {
    //удалить один отцеп
    case 3:
        if(m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0){
            m_stateBt.m_bef_regim=3;
            m_stateBt.m_wCursor=true;
            emit stateBtChanged();
        }
        else{addMsg("Перейти в режим: <<ВВОД СЛ или ПАУЗА>>");}
        break;
        //удалить все
    case 7:
        if(m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0){
            m_stateBt.m_bef_regim=7;
            m_stateBt.m_wCursor=true;
            emit stateBtChanged();
        }
        else{addMsg("Перейти в режим: <<ВВОД СЛ или ПАУЗА>>");}
        break;
        //Вставить до
    case 4:
        if(m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0){
            m_stateBt.m_bef_regim=4;
            m_stateBt.m_wCursor=true;
            emit stateBtChanged();
        }
        else{addMsg("Перейти в режим: <<ВВОД СЛ, ПАУЗА>>");}
        break;
        //Вставить после
    case 5:
        if(m_stateBt.m_regim!=1 && m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0){
            m_stateBt.m_bef_regim=5;
            m_stateBt.m_wCursor=true;
            emit stateBtChanged();
        }
        else{addMsg("Перейти в режим: <<ВВОД СЛ, ПАУЗА>>");}
        break;
        //Изменить путь
    case 6:
        if( m_stateBt.m_regim!=0 && m_qmlCurentIndex>=0){
            m_stateBt.m_bef_regim=6;
            if(m_stateBt.m_regim!=1)
                m_stateBt.m_wCursor=true;
            emit stateBtChanged();
        }
        else{addMsg("Перейти в режим: <<ВВОД СЛ, РОСПУСК, ПАУЗА>>");}
        break;
    case 10:
        qDebug()<<"Сброс мигания курсора->>"<<m_stateBt.m_bef_regim;
        if(m_stateBt.m_bef_regim!=10){
            m_stateBt.m_wCursor=false;
            m_stateBt.m_bef_regim=10;
            emit stateBtChanged();
        }
        break;
    }
}
void ManageModel::qmlRegim(const int & regim)
{
    if(m_stateBt.m_editing==1){
        addMsg("Закончить режим <<ВВОД СЛ>>");
        return;
    }
    switch (regim) {
    case 0:
        m_stateBt.m_bef_regim=0;
        m_stateBt.m_wStop=true;
        emit stateBtChanged();
        break;
    case 1:
        m_stateBt.m_bef_regim=1;
        m_stateBt.m_wNadvig=true;
        emit  stateBtChanged();
        break;
    case 2:
        m_stateBt.m_bef_regim=2;
        m_stateBt.m_wPause=true;
        emit stateBtChanged();
        //        }
        break;
    case 10:
        qDebug()<<"Команда не задана";
        if(m_stateBt.m_bef_regim!=10){
            m_stateBt.m_bef_regim=10;
            emit stateBtChanged();
        }
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
    case 3:
        delOtcep(1);
        qmlRegimEditing(10);
        break;
    case 6:
        emit textInputChanged();
        qmlRegimEditing(10);
        break;
    case 7:
        clearAllOtcep();
        qmlRegimEditing(10);
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
    if(m_stateBt.m_bef_regim==4){
        addOtcep(m_qmlCurentIndex+1);
        qDebug()<<"отцеп №"<<m_qmlCurentIndex+1;
        qmlRegimEditing(6);
        setQmlCurrentItem(m_qmlCurentIndex);
        accept();
    }
    else if(m_stateBt.m_bef_regim==5){
        if(ViewOtcepsModel::instance().countEnabled()==0){
            addOtcep(m_qmlCurentIndex+1);
            qDebug()<<"отцеп №"<<m_qmlCurentIndex+1;
        }
        else{
            addOtcep(m_qmlCurentIndex+2);
            qDebug()<<"отцеп №"<<m_qmlCurentIndex+2;
            m_qmlCurentIndex++;
        }
        qmlRegimEditing(6);
        setQmlCurrentItem(m_qmlCurentIndex);
        accept();
    }
    else{qmlRegimEditing(6);}

    //    //    MVP_Import::instance()->setOtcepSP(m_qmlCurentIndex+1,numberPut);
    //    emit textInputChanged();

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
void ManageModel::keyDown(const DWORD &key, const bool &ctrl)
{

    qDebug()<<"vkCode"<<key ;
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
        //        m_stateBt.m_bef_putNadviga=1;
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
        //            case  65:
    case VK_DOWN:
        //DOWN
        keyUpDown(VK_DOWN);
        break;

    case VK_INSERT:

        if(ctrl){
            //Вставить после
            qmlRegimEditing(5);
            //            addOtcep(1);
            break;
        }
        //Вставить до
        qmlRegimEditing(4);
        //        addOtcep(0);
        break;
    case VK_DELETE:

        if(ctrl){
            //Удалить все
            qmlRegimEditing(7);

            break;
        }
        //Удалить
        qmlRegimEditing(3);
        break;
    case VK_ESCAPE:
        qmlRegimEditing(10);
        //        qmlRegim(10);
        //        qmlRegim(11);
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
}
