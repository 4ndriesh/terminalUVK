#include "viewotcepsmodel.h"
#include <iostream>
#include <QTimer>
#include <QMapIterator>
#include "editotcepsmodel.h"
#include <QThread>

#include "m_otceps.h"

ViewOtcepsModel::ViewOtcepsModel(QObject *parent,m_Otceps *otceps)
    : QAbstractListModel(parent)
    ,timer(new QTimer(this))

{
    index=0;

    for (int i=0; i<otceps->l_otceps.size();i++) {
        addDataObject(DataObject(otceps->l_otceps[i]));
//        addDataObject(DataObject{i,
//                                 QString::number(i),
//                                 QString::number(i),
//                                 QString::number(i),
//                                 QString::number(i),
//                                 QString::number(i),
//                                 QString::number(i),
//                                 QString::number(i),
//                                 QString::number(i),
//                                 QString::number(i),
//                                 QString::number(i),
//                                 QString::number(i)
//                      });
    }

    timer->setInterval(1000);    
    connect(timer, &QTimer::timeout , this, &ViewOtcepsModel::getBySYB);
    timer->start();
}

void ViewOtcepsModel::getBySYB()
{
    std::cout << "getBySYB" << std::endl;
    //index++;
    if(index>=rowCount(QModelIndex())) {
        index=0;
    }
    emit setCurrentItem(index);

    if (index % 2 == 0)
        {
            emit showMessage("#FFFFE0","YELLOW");
        }
        else
        {
            emit showMessage("red","RED");
        }

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

//QVariant ViewOtcepsModel::data(const QModelIndex &index, int role) const
//{
//    if(index.row() < 0 || index.row() >= ViewOtcepList.count() || !index.isValid())
//        return  QVariant();

//    const DataObject &DataObject = ViewOtcepList[index.row()];

//    switch (role)
//    {
//    case nRole:
//        return DataObject.n();
//        break;

//    case marRole:
//        return DataObject.mar();
//        break;

//    case mar_fRole:
//        return DataObject.mar_f();
//        break;

//    case lenRole:
//        return DataObject.len();
//        break;
//    case len_fRole:
//        return DataObject.len_f();
//        break;

//    case katRole:
//        return DataObject.kat();
//        break;
//    case kat_fRole:
//        return DataObject.kat_f();
//        break;
//    case bazRole:
//        return DataObject.baz();
//        break;

//    case nagRole:
//        return DataObject.nag();
//        break;

//    case urRole:
//        return DataObject.ur();
//        break;

//    case VRole:
//        return DataObject.V();
//        break;

//    case kzpRole:
//        return DataObject.kzp();
//        break;
//    }
//    return QVariant();
//}

QVariant ViewOtcepsModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= ViewOtcepList.count() || !index.isValid())
        return  QVariant();

    const DataObject &DataObject = ViewOtcepList[index.row()];

    switch (role)
    {
    case nRole:
        return QString::number(DataObject.otcep->NUM());
        break;

    case marRole:
        return QString::number(DataObject.otcep->STATE_MAR());
        break;

    case mar_fRole:
        return QString::number(DataObject.otcep->STATE_MAR_F());
        break;

    case lenRole:
        return QString::number(DataObject.otcep->STATE_LEN());
        break;
    case len_fRole:
        return QString::number(DataObject.otcep->STATE_LEN());// ??
        break;

    case katRole:
        return QString::number(0);// ??
        break;
    case kat_fRole:
        return QString::number(0);// ??
        break;
    case bazRole:
        return QString::number(DataObject.otcep->STATE_BAZA());
        break;

    case nagRole:
        return QString::number(0);// ??
        break;

    case urRole:
        return QString::number(0);// ??
        break;

    case VRole:
        return QString::number(DataObject.otcep->STATE_V());
        break;

    case kzpRole:
        return QString::number(0);// ??
        break;
    }
    return QVariant();
}


bool ViewOtcepsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    DataObject &dataSourceObject = ViewOtcepList[index.row()];
    if (data(index, role) != value) {
        switch (role)
        {
        case nRole:
            dataSourceObject.setn(value.toInt());
            break;

        case marRole:
            dataSourceObject.setmar(value.toString());
            break;

        case mar_fRole:
            dataSourceObject.setmar_f(value.toString());
            break;

        case lenRole:
            dataSourceObject.setlen(value.toString());
            break;
        case len_fRole:
            dataSourceObject.setlen_f(value.toString());
            break;

        case katRole:
            dataSourceObject.setkat(value.toString());
            break;

        case kat_fRole:
            dataSourceObject.setkat_f(value.toString());
            break;

        case bazRole:
            dataSourceObject.setbaz(value.toString());
            break;

        case nagRole:
            dataSourceObject.setnag(value.toString());
            break;

        case urRole:
            dataSourceObject.setur(value.toString());
            break;

        case VRole:
            dataSourceObject.setV(value.toString());
            break;

        case kzpRole:
            dataSourceObject.setkzp(value.toString());
            break;
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

    QHash<int, QByteArray> roles;
    roles[nRole] = "n";
    roles[marRole] = "mar";
    roles[mar_fRole] = "mar_f";
    roles[lenRole] = "len";
    roles[len_fRole] = "len_f";
    roles[katRole] = "kat";
    roles[kat_fRole] = "kat_f";
    roles[bazRole] = "baz";
    roles[nagRole] = "nag";
    roles[urRole] = "ur";
    roles[VRole] = "V";
    roles[kzpRole] = "kzp";

    return  roles;
}
void ViewOtcepsModel::deleteFromList()
{

}
