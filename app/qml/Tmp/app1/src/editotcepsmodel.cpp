#include "editotcepsmodel.h"
#include "viewotcepsmodel.h"
#include <iostream>
#include <QTimer>
#include <QThread>
#include <QDebug>
//#include "mvp_import.h"
#include <QMetaProperty>

EditOtcepsModel::EditOtcepsModel(QObject *parent)
    : QAbstractListModel(parent)
{




}


QVariantMap EditOtcepsModel::get(int row) const
{
    return EditOtcepList[row].toMap();
}

void EditOtcepsModel::addDataObject(const DataObject &DataObject)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    EditOtcepList << DataObject;
    endInsertRows();
}
int EditOtcepsModel::rowCount(const QModelIndex &parent) const
{
    Q_ASSERT(checkIndex(parent));
    if (parent.isValid())
        return 0;
    return EditOtcepList.count();
}

QVariant EditOtcepsModel::data(const QModelIndex &index, int role) const
{
//    Q_ASSERT(checkIndex(index, QAbstractItemModel::CheckIndexOption::IndexIsValid));

//    if(index.row() < 0 || index.row() >= EditOtcepList.count() || !index.isValid())
//        return  QVariant();

//    const DataObject &DataObject = EditOtcepList[index.row()];


//    return QVariant();
}

bool EditOtcepsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    DataObject &dataSourceObject = EditOtcepList[index.row()];

    if (data(index, role) != value) {

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags EditOtcepsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> EditOtcepsModel::roleNames() const
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


void EditOtcepsModel::deleteFromEditOtcepList(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    EditOtcepList.removeAt(index);
    endRemoveRows();

    //    ViewOtcepsModel model;
    //    QMap<QString, QVariant> map;
    //    map=get(2);
    //    QMapIterator<QString, QVariant> i(map);

    //    while (i.hasNext()) {
    //        i.next();

    //    i.hasNext();

    //    model.deleteFromList();

    //    model.addDataSourceObject(DataSourceObject{i.next().value().toInt(),
    //                                                    QString::number(i.next().value().toInt()),
    //                                                    QString::number(i.next().value().toInt()),
    //                                                    QString::number(i.next().value().toInt()),
    //                                                    QString::number(i.next().value().toInt()),
    //                                                    QString::number(i.next().value().toInt()),
    //                                                    QString::number(i.next().value().toInt())
    //                                   });
    //        std::cout << i.key().toStdString()<<i.value().toInt() << std::endl;
    //    }

}
void EditOtcepsModel::addToList()
{

}

