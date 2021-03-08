#include "editotcepsmodel.h"
#include "viewotcepsmodel.h"
#include <iostream>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include "mvp_import.h"
#include <QMetaProperty>

EditOtcepsModel::EditOtcepsModel(QObject *parent)
    : QAbstractListModel(parent)
{

}


QVariantMap EditOtcepsModel::get(int row) const
{
    //    return EditOtcepList[row].toMap();
}

void EditOtcepsModel::insertOtcep(const int & index)
{
    EditOtcepList.insert(index,{2, 1});
    beginResetModel();
    endResetModel();
}
void EditOtcepsModel::addDataObject()
{
    EditOtcepList.append({1, 1});
    beginResetModel();
    endResetModel();
}
void EditOtcepsModel::clearAll()
{
    EditOtcepList.clear();
    beginResetModel();
    endResetModel();
}
//void EditOtcepsModel::addDataObject()
//{
//    EditOtcepList.insert(2,{"heading 34", "description 1", 1});//
//    beginInsertRows(QModelIndex(), 2, 2);
////    beginInsertRows(QModelIndex(), rowCount(), rowCount());
//    endInsertRows();
//}
int EditOtcepsModel::rowCount(const QModelIndex &parent) const
{
    Q_ASSERT(checkIndex(parent));
    if (parent.isValid())
        return 0;
    return EditOtcepList.size();
}

QVariant EditOtcepsModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(checkIndex(index, QAbstractItemModel::CheckIndexOption::IndexIsValid));

    if (!hasIndex(index.row(), index.column(), index.parent()) || !index.isValid())
        return false;

    //    const DataObject &DataObject = EditOtcepList[index.row()];
    const ListOtcep &item = EditOtcepList.at(index.row());
    if (role == SP) return item.sp;
    if (role == SL_VAGON_CNT) return item.sl_vagon_cnt;


    return QVariant();
}

bool EditOtcepsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
        return false;

    ListOtcep &item = EditOtcepList[index.row()];
    if (role == SP) item.sp = value.toInt();
    else if (role == SL_VAGON_CNT) item.sl_vagon_cnt = value.toInt();
//    else return false;

    emit dataChanged(index, index, { role } );

    return true ;
}

Qt::ItemFlags EditOtcepsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable; // FIXME: Implement me!
}

void EditOtcepsModel::deleteFromEditOtcepList(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    EditOtcepList.removeAt(index);
    endRemoveRows();
}
void EditOtcepsModel::addToList()
{

}
//Навигация по списку рельсовых цепей
void EditOtcepsModel::keyUpDown(const int &updown)
{

    switch (updown) {
    case VK_UP:
        if(m_qmlEditOtcepItem>0)
        {
            m_qmlEditOtcepItem--;
        }
        break;
    case VK_DOWN:
        if(m_qmlEditOtcepItem<rowCount())
        {
            m_qmlEditOtcepItem++;

        }
        break;
    }

    emit qmlEditOtcepItemChanged();
    return;
}
//Обработка клавы
void EditOtcepsModel::keyDown(const int &key)
{
    qDebug()<<"vkCode"<<key ;

    switch (key) {

    case VK_F5:
        setQmlEditOtcepItem(0);
//        emit closeRChainChanged();
        break;
    case VK_RETURN:
//        accept();
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

    case VK_DELETE:
        //Удалить
//        emit setQmlEditOtcepItem();
        break;
    }
    return;
}
