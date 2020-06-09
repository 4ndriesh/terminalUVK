#include "viewotcepsmodel.h"
#include <iostream>
#include <QTimer>
#include <QMapIterator>
#include "editotcepsmodel.h"
#include <QThread>


#include "mvp_import.h"
#include <QMetaProperty>

//Всегда возвращает 1
//qmlStopPause=MVP_Import::instance()->gorka->STATE_REGIM();

/*
    Видимость -  STATE_ENABLED
    цвет
    серый   STATE_LOCATION = 2(locationOnSpusk) && STATE_SP==STATE_SP_F
            или STATE_LOCATION = 3(locationOnPark)
    светло серый   STATE_LOCATION = 2(locationOnSpusk) && STATE_SP!=STATE_SP_F
    желтый         STATE_LOCATION = 2 &&   STATE_ZKR_PROGRESS==1
    красный STATE_ERROR==1
    белый STATE_LOCATION = 1(locationOnPrib)
    в остальный случаях темно серый

    КНОПКИ: ВВОД СЛ
            РОСПУСК1 ПАУЗА СТОП MVP_Import::instance()->gorka->STATE_REGIM
            РОСПУСК1/РОСПУСК2 - сделаю доп свойство gorka->PUT_NADVIG = 1..2

    РЕЖИМ ВВОД СЛ - появляется курсор
    так же вход в режим при щелкани мышью по отцепу
    выход - по кнопке любой
    правой кнмн на РОСПУСК1 - выбор РОСПУСК1/РОСПУСК2

    команды в увк
    РОСПУСК: CMD=SET_RIGIME  REGIME=ROSPUSK
    ПАУЗА: CMD=SET_RIGIME  REGIME=PAUSE
    СТОП: CMD=SET_RIGIME  REGIME=STOP
    РОСПУСК1/РОСПУСК2: CMD=SET_ACT_ZKR  ACT_ZKR =1/2

 */


ViewOtcepsModel* ViewOtcepsModel::model = nullptr;
ViewOtcepsModel::ViewOtcepsModel(QObject *parent)
    : QAbstractListModel(parent)
    ,timer(new QTimer(this))

{
    for(int msg=0; msg<10;msg++)
        addMsg("Hello Word",msg);

    qmlPutNadviga.m_set_putnadviga=MVP_Import::instance()->gorka->PUT_NADVIG();

    qmlRegim=MVP_Import::instance()->gorka->STATE_REGIM();
    qmlX=1;
    qmlVisibleObject=false;
    qmlCurentIndex=0;
    int irole=Qt::UserRole+1;
    for (int idx = 0; idx < m_Otcep::staticMetaObject.propertyCount(); idx++) {
        QMetaProperty metaProperty = m_Otcep::staticMetaObject.property(idx);
        QString proprtyName=metaProperty.name();
        otcepRoles[irole++] = qPrintable(proprtyName);
    }

    //    qmlCurentIndex=0;
    if (MVP_Import::instance()->gorka!=nullptr){

        for (int i=0; i<MVP_Import::instance()->otceps->l_otceps.size();i++) {

            addDataObject(DataObject(MVP_Import::instance()->otceps->l_otceps[i]));
            connect(MVP_Import::instance()->otceps->l_otceps[i],&m_Otcep::stateChanged,this,&ViewOtcepsModel::slotOtcepChanged);
        }
        connect(MVP_Import::instance()->gorka,&ModelGroupGorka::stateChanged,this,&ViewOtcepsModel::slotOtcepChanged);


    }
    connect(MVP_Import::instance()->cmd,&GtCommandInterface::recv_accept,this,&ViewOtcepsModel::uvk_cmd_accept);


    //    timer->setInterval(1000);
    //    connect(timer, &QTimer::timeout , this, &ViewOtcepsModel::slotOtcepChanged);
    //timer->start();

    connect(MVP_Import::instance(),&MVP_Import::sortirArrived,this,&ViewOtcepsModel::sortirArrived);
//    connect(MVP_Import::instance(),&MVP_Import::sendStartProgressBar,this,&ViewOtcepsModel::slotStartProgressBar);
//    connect(MVP_Import::instance(),&MVP_Import::sendStopProgressBar,this,&ViewOtcepsModel::slotStopProgressBar);
}
ViewOtcepsModel *ViewOtcepsModel::instance()
{
    if (model == nullptr) // avoid creation of new instances
        model = new ViewOtcepsModel;
    return model;
}

void ViewOtcepsModel::slotOtcepChanged()
{        
    qDebug()<<"STATE_REGIM"<<MVP_Import::instance()->gorka->STATE_REGIM();
    qmlPutNadviga.m_set_putnadviga=MVP_Import::instance()->gorka->PUT_NADVIG();
    qDebug()<<"PUT_NADVIG"<<MVP_Import::instance()->gorka->PUT_NADVIG();
    qmlRegim=MVP_Import::instance()->gorka->STATE_REGIM();
    emit qmlPutNadvigaChanged();
    emit qmRegimChanged();
    beginResetModel();
    endResetModel();
}


QVariantMap ViewOtcepsModel::get(int row) const
{
    return ViewOtcepList[row].toMap();
}


void ViewOtcepsModel::addDataObject(const DataObject &dataSourceObject)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    ViewOtcepList << dataSourceObject;
    endInsertRows();
}
int ViewOtcepsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return ViewOtcepList.count();
}



QVariant ViewOtcepsModel::data(const QModelIndex &index, int role) const
{

    if(index.row() < 0 || index.row() >= ViewOtcepList.count() || !index.isValid())
        return  QVariant();

    const DataObject &DataObject = ViewOtcepList[index.row()];

    if (otcepRoles.contains(role)){
        return DataObject.getState(otcepRoles[role]);
    }
    return QVariant();

}


bool ViewOtcepsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    DataObject &dataSourceObject = ViewOtcepList[index.row()];
    if (data(index, role) != value) {
        if (otcepRoles.contains(role)){
            dataSourceObject.setState(otcepRoles[role],value);
        } else {
            QAbstractListModel::setData(index,value,role);
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}


Qt::ItemFlags ViewOtcepsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> ViewOtcepsModel::roleNames() const
{

    auto  roles=QAbstractListModel::roleNames();

    foreach (auto key, otcepRoles.keys()) {
        roles.insert(key,otcepRoles[key]);
    }

    return  roles;
}

void ViewOtcepsModel::sortirArrived(const tSl2Odo2 *srt)
{
    // прверить что режим ввода установлен
    // если нет то запомнить и мигать кнопкой
    if (!loadSortirToUvk(srt)) {
        MVP_Import::instance()->_Id=0;
    }
}

void ViewOtcepsModel::uvk_cmd_accept(QMap<QString, QString> m)
{
    if (m["ACCEPT_SRC"]!="UVK") return;
    addMsg(m["ACCEPT_TXT"],1);
}

bool ViewOtcepsModel::loadSortirToUvk(const tSl2Odo2 *srt)
{
    return MVP_Import::instance()->loadSortirToUvk(srt);
}


void ViewOtcepsModel::deleteFromList()
{

}

void ViewOtcepsModel::getRndChart()
{
    //    qmlStopPause=MVP_Import::instance()->gorka->STATE_REGIM();
    qmlX+=1;
    qmlY=qrand() % 10;
    emit setRndChart(qmlX,qmlY);
}

void ViewOtcepsModel::addOtcepUP(int index)
{
    if(index!=-1)
    {
        qDebug()<<"addup"<<index;
    }
}

void ViewOtcepsModel::addOtcepDown(int index)
{
    if(index!=-1)
        qDebug()<<"addDown"<<index;
}

void ViewOtcepsModel::addOtcepClearAll()
{
    qDebug()<<"addupClearAll";
    QMap<QString,QString> m;
    m.clear();
    m["DEST"]="UVK";
    m["CMD"]="OTCEPS";
    m["CLEAR_ALL"]="1";
    MVP_Import::instance()->cmd->send_cmd(m);
}

void ViewOtcepsModel::setStatusPB(const StructProgressBar &set_statusPB)
{

    //  qmlPutNadviga.m_putnadviga=MVP_Import::instance()->gorka->PUT_NADVIG();
    qmlStatusPB=set_statusPB;
    emit statusPBChanged();

}
StructProgressBar ViewOtcepsModel::getStatusPB() const
{

    //  qmlPutNadviga.m_putnadviga=MVP_Import::instance()->gorka->PUT_NADVIG();
    return qmlStatusPB;
}


void ViewOtcepsModel::setPutNadviga(const StructPutNadviga &set_putnadviga)
{

    qmlPutNadviga = set_putnadviga;
    qDebug()<<"qmlPutNadviga.m_set_putnadviga"<<qmlPutNadviga.m_set_putnadviga;
//    if(qmlPutNadviga.m_chg_putnadviga==false)
    MVP_Import::instance()->setPutNadvig(qmlPutNadviga.m_set_putnadviga);

    qmlPutNadviga.m_set_putnadviga=MVP_Import::instance()->gorka->PUT_NADVIG();
    emit qmlPutNadvigaChanged();

}

StructPutNadviga ViewOtcepsModel::getPutNadviga()const
{
    return qmlPutNadviga;
}

//Управляет кнопкой стоп
int ViewOtcepsModel::getRegim()const
{
    return qmlRegim;
}
void ViewOtcepsModel::setRegim(const int &regim)
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
int ViewOtcepsModel::getCurrentItem()const
{
    return qmlCurentIndex;
}
void ViewOtcepsModel::setCurrentItem(const int &index)
{
    qmlCurentIndex = index;
//    emit qmlCurrentItemChanged();
}

//Управляет визиблами для редактирования
int ViewOtcepsModel::getEditSortir()const
{
    return qmlVisibleObject;
}
void ViewOtcepsModel::setEditSortir(const int &visible)
{
    qmlVisibleObject = visible;
    emit qmlVisibleObjectChanged();
}
//-------------------------------------------------
//Управляет сообщениями
QStringList ViewOtcepsModel::getListMsg()const
{
    return m_listMsg;
}
//Удаляем сообщения об ошибках по таймеру
void ViewOtcepsModel::addMsg(const QString &valMsg, int msg)
{
    if(m_listMsg.isEmpty()){
        qDebug()<<"Start Timer";
        timerDelMsg=true;
        emit timerDelMsgChanged();
    }
    m_listMsg.append(valMsg+QString::number(msg));
    emit listMsgChanged();
}

void ViewOtcepsModel::deleteMsg()
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

bool ViewOtcepsModel::getTimerDelMsg() const
{
    return timerDelMsg;
}

