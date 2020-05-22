#include "viewotcepsmodel.h"
#include <iostream>
#include <QTimer>
#include <QMapIterator>
#include "editotcepsmodel.h"
#include <QThread>


#include "mvp_import.h"
#include <QMetaProperty>




/*
    Видимость -  STATE_ENABLED
    цвет
    серый   STATE_LOCATION = 2(locationOnSpusk) && STATE_MAR==STATE_MAR_F
            или STATE_LOCATION = 3(locationOnPark)
    светло серый   STATE_LOCATION = 2(locationOnSpusk) && STATE_MAR!=STATE_MAR_F
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



ViewOtcepsModel::ViewOtcepsModel(QObject *parent)
    : QAbstractListModel(parent)
    ,timer(new QTimer(this))

{
    int irole=Qt::UserRole+1;
    for (int idx = 0; idx < m_Otcep::staticMetaObject.propertyCount(); idx++) {
        QMetaProperty metaProperty = m_Otcep::staticMetaObject.property(idx);
        QString proprtyName=metaProperty.name();
        otcepRoles[irole++] = qPrintable(proprtyName);
    }

    current_index=0;
    if (MVP_Import::instance()->gorka!=nullptr){

        m_Otceps *otceps=MVP_Import::instance()->gorka->findChildren<m_Otceps *>().first();
        for (int i=0; i<otceps->l_otceps.size();i++) {
            addDataObject(DataObject(otceps->l_otceps[i]));
            connect(otceps->l_otceps[i],&m_Otcep::stateChanged,this,&ViewOtcepsModel::slotOtcepChanged);
        }

    }

    timer->setInterval(1000);
    connect(timer, &QTimer::timeout , this, &ViewOtcepsModel::slotOtcepChanged);
    //timer->start();
    connect(MVP_Import::instance(),&MVP_Import::sortirArrived,this,&ViewOtcepsModel::sortirArrived);
}


void ViewOtcepsModel::slotOtcepChanged()
{
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
bool ViewOtcepsModel::loadSortirToUvk(const tSl2Odo2 *srt)
{
    m_Otceps *otceps=MVP_Import::instance()->gorka->findChildren<m_Otceps *>().first();

    QMap<QString,QString> m;
    m["DEST"]="UVK";
    m["CMD"]="OTCEPS";
    m["CLEAR_ALL"]="1";
    MVP_Import::instance()->cmd->send_cmd(m);
    qDebug()<< "sortir send clear " ;
    QElapsedTimer t;
    t.start();

    while ((!otceps->enabledOtceps().isEmpty())&&(t.elapsed()<1000)){
        QCoreApplication::processEvents();
    }
    if (!otceps->enabledOtceps().isEmpty()){
        // не прошла команда очистки
        qDebug()<< "error sortir send clear " ;
        return false;
    }
    bool errorLoad=false;
    foreach (const tSl2OdoRec2 &o, srt->vOtceps) {
        m.clear();
        m["DEST"]="UVK";
        m["CMD"]="SET_OTCEP_STATE";
        m["N"]=QString::number(o.NO);

        m["ENABLED"]=QString::number(1);
        m["ID_ROSP"]=QString::number(srt->Id);
        m["SP"]=QString::number(o.SP);
        m["SL_VAGON_CNT"]=QString::number(o.vVag.size());
        m["SL_OSY_CNT"]=QString::number(o.Osy);
        m["SL_LEN"]=QString::number(o.Ln);
        m["SL_VES"]=QString::number(o.ves_sl);
        m["SL_BAZA"]=QString::number(o.aDb);
        m["SL_UR"]=QString::number(o.Ne);
        m["SL_OSO"]=QString::number(o.OSO);
        MVP_Import::instance()->cmd->send_cmd(m);
        qDebug()<< "sortir send otcep " << o.NO;
        t.start();
        m_Otcep *otcep=otceps->otcepByNum(o.NO);
        if (otcep==nullptr){
            errorLoad=true;

            break;
        }
        while ((otcep->STATE_SP()!=o.SP)&&(t.elapsed()<1000)){
            QCoreApplication::processEvents();
        }
        if ((otcep->STATE_SP()!=o.SP)){
            // не прошла команда на отцеп
            errorLoad=true;
            qDebug()<< "error sortir send otcep " << o.NO;
            break;
        }

        foreach (const tSlVagon &v, o.vVag) {

            m.clear();
            m["DEST"]="UVK";
            m["CMD"]="ADD_OTCEP_VAG";
            m["N"]=QString::number(o.NO);
            QVariantHash vm=tSlVagon2Map(v);
            foreach (QString key, vm.keys()) {
                m[key]=vm[key].toString();
            }

            MVP_Import::instance()->cmd->send_cmd(m);
            qDebug()<< "sortir send otcep vagon" << o.NO << v.IV;
            t.start();
            while (((otcep->vVag.isEmpty())||(otcep->vVag.last().IV!=v.IV))&&(t.elapsed()<1000)){
                QCoreApplication::processEvents();
            }
            if ((otcep->vVag.isEmpty())||(otcep->vVag.last().IV!=v.IV)){
                // не прошла команда на вагон
                errorLoad=true;
                qDebug()<< "error sortir send otcep vagon" << o.NO << v.IV;
                break;
            }
        }
        if (errorLoad) break;
    }
    if (errorLoad){
        // чистим все
        m.clear();
        m["DEST"]="UVK";
        m["CMD"]="OTCEPS";
        m["CLEAR_ALL"]="1";
        MVP_Import::instance()->cmd->send_cmd(m);
    }
    return errorLoad;
}


void ViewOtcepsModel::deleteFromList()
{

}
