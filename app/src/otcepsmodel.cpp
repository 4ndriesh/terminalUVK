#include "otcepsmodel.h"
#include <iostream>
#include <QTimer>
#include <QMapIterator>
#include "mvp_import.h"
#include <QMetaProperty>

#include "vagonsmodel.h"


//Всегда возвращает 1
//qmlStopPause=MVP_Import::instance()->gorka->STATE_REGIM();

/*
Видимость -  STATE_ENABLED

    КНОПКИ: ВВОД СЛ
            РОСПУСК1 ПАУЗА СТОП MVP_Import::instance()->gorka->STATE_REGIM                  РОСПУСК1/РОСПУСК2 - сделаю доп свойство gorka->PUT_NADVIG = 1..2

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

ManageModel &Mn = ManageModel::instance();
OtcepsModel::OtcepsModel(QObject *parent)
    : QAbstractListModel(parent)
    //    ,timer(new QTimer(this))

{
    QTimer *timer=new QTimer(this);

    int irole=Qt::UserRole+1;
    for (int idx = 0; idx < m_Otcep::staticMetaObject.propertyCount(); idx++) {
        QMetaProperty metaProperty = m_Otcep::staticMetaObject.property(idx);
        QString proprtyName=metaProperty.name();
        otcepRoles[irole++] = qPrintable(proprtyName);
    }

    if (MVP_Import::instance()->gorka!=nullptr){
        for (int i=0; i<MVP_Import::instance()->otceps->l_otceps.size();i++) {
            addDataObject(DataObject(MVP_Import::instance()->otceps->l_otceps[i]));
            connect(MVP_Import::instance()->otceps->l_otceps[i],&m_Otcep::stateChanged,this,&OtcepsModel::slotOtcepChanged);
        }
        connect(MVP_Import::instance()->gorka,&ModelGroupGorka::stateChanged,this,&OtcepsModel::slotOtcepChanged);
    }

    connect(MVP_Import::instance()->cmd,&GtCommandInterface::recv_accept,this,&OtcepsModel::uvk_cmd_accept);

    timer->setInterval(1000);
    connect(timer, &QTimer::timeout , this, &OtcepsModel::slotOtcepChanged);
    timer->start();

    connect(MVP_Import::instance(),&MVP_Import::sortirArrived,this, &OtcepsModel::sortirArrived);
    Mn.updateOtcep();

}

void OtcepsModel::slotOtcepChanged()
{
    Mn.m_stateBt.m_regim=MVP_Import::instance()->gorka->STATE_REGIM();
    //    if(countEnabled()==0 && Mn.m_stateBt.m_editing==0)
    //    Mn.setQmlCurrentItem(Mn.m_qmlCurentIndex);

    Mn.m_stateBt.m_regim_Finish=MVP_Import::instance()->gorka->STATE_GAC_FINISH();

    Mn.m_uvkLive=!MVP_Import::instance()->gorka->SIGNAL_ROSPUSK().is33();
    emit Mn.uvkLiveChanged();

    Mn.m_stateBt.m_putNadviga=MVP_Import::instance()->gorka->STATE_PUT_NADVIG();
    Mn.m_stateBt.m_bef_putNadviga=Mn.m_stateBt.m_putNadviga;
    emit Mn.stateBtChanged();

    emit dataChanged(createIndex(0,0), createIndex(98, 8));

    struct TUVK_status{
        time_t time;
    };
    static TUVK_status c;
    c.time=QDateTime().currentDateTime().toTime_t();

    MVP_Import::instance()->udp.sendData(3,"Term_UVK",QByteArray((const char*)&c,sizeof(c)));
}

int OtcepsModel::countEnabled()
{
    int countRow=99;
    do{
        countRow--;
        if(countRow==-1)break;
    }while (get(countRow)["STATE_ENABLED"]!=true && countRow!=-1);
    return countRow;
}

QVariantMap OtcepsModel::get(int row) const
{
    return ViewOtcepList[row].toMap();
}

void OtcepsModel::addDataObject(const DataObject &dataSourceObject)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    ViewOtcepList << dataSourceObject;    
    endInsertRows();
}
int OtcepsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return ViewOtcepList.count();
}

QVariant OtcepsModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= ViewOtcepList.count() || !index.isValid())
        return  QVariant();

    const DataObject &DataObject = ViewOtcepList[index.row()];

    if (otcepRoles.contains(role)){
        return DataObject.getState(otcepRoles[role]);
    }
    return QVariant();

}


bool OtcepsModel::setData(const QModelIndex &index, const QVariant &value, int role)
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


Qt::ItemFlags OtcepsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> OtcepsModel::roleNames() const
{

    auto  roles=QAbstractListModel::roleNames();

    foreach (auto key, otcepRoles.keys()) {
        roles.insert(key,otcepRoles[key]);
    }

    return  roles;
}

void OtcepsModel::sortirArrived(const tSl2Odo2 *srt)
{
    Mn.m_newList=true;

    // прверить что режим ввода установлен
    // если нет то запомнить и мигать кнопкой
    if(Mn.m_stateBt.m_bef_regim==12){
//    if(Mn.m_stateBt.m_editing==1){
        if (!loadSortirToUvk(srt)) {
            VagonsModel::instance().loadSortList(srt);
            MVP_Import::instance()->_Id=0;
            Mn.m_newList=false;
            Mn.updateOtcep();
            tmpSrt=nullptr;
        }
    }else tmpSrt=srt;
    Mn.m_stateBt.m_wGetList=false;
    emit Mn.newListChanged();
    return;
}

void OtcepsModel::uvk_cmd_accept(QMap<QString, QString> m)
{
    if (m["ACCEPT_SRC"]!="UVK") return;
    Mn.addMsg(m["ACCEPT_TXT"]);
}

bool OtcepsModel::loadSortirToUvk(const tSl2Odo2 *srt)
{
    return MVP_Import::instance()->loadSortirToUvk(srt);
}




