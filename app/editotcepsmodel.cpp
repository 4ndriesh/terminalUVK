#include "editotcepsmodel.h"
#include "viewotcepsmodel.h"
#include <iostream>
#include <QTimer>
#include <QThread>
#include <QDebug>

EditOtcepsModel::EditOtcepsModel(QObject *parent)
    : QAbstractListModel(parent)
{

    for (int i=1; i<5;i++) {
        addDataObject(DataObject{i,
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i)
                      });
    }


}

void EditOtcepsModel::sendToSYB()
{
    std::cout << "sendToSYB" << std::endl;
    QMapIterator<QString, QVariant> i(EditOtcepList[1].toMap());
    while (i.hasNext()) {
               i.next();
               std::cout << i.key().toStdString()<<"    "<<i.value().toInt() << std::endl;

}

//    for (int i=0; i<rowCount();i++) {
//    qDebug() << EditOtcepList[i].toMap()["mar"];
//    }
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
    Q_ASSERT(checkIndex(index, QAbstractItemModel::CheckIndexOption::IndexIsValid));

    if(index.row() < 0 || index.row() >= EditOtcepList.count() || !index.isValid())
        return  QVariant();

    const DataObject &DataObject = EditOtcepList[index.row()];

    switch (role)
    {
    case nRole:
        return DataObject.n();
        break;
    case marRole:
        return DataObject.mar();
        break;
    case mar_fRole:
        return DataObject.mar_f();
        break;
    case lenRole:
        return DataObject.len();
        break;
    case len_fRole:
        return DataObject.len_f();
        break;
    case katRole:
        return DataObject.kat();
        break;
    case kat_fRole:
        return DataObject.kat_f();
        break;
    case bazRole:
        return DataObject.baz();
        break;
    case nagRole:
        return DataObject.nag();
        break;
    case urRole:
        return DataObject.ur();
        break;
    case VRole:
        return DataObject.V();
        break;
    case kzpRole:
        return DataObject.kzp();
        break;
    }
    return QVariant();
}

bool EditOtcepsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    DataObject &dataSourceObject = EditOtcepList[index.row()];

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
    //    beginInsertRows(QModelIndex(), index, index);
    //    endInsertRows();
    for (int i=0; i<1;i++) {
        addDataObject(DataObject{i,
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i),
                                 QString::number(i)
                      });


    }
}

