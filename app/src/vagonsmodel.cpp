#include "vagonsmodel.h"
#include <iostream>
#include <QTimer>
#include <QDebug>
#include "mvp_import.h"
#include <QMetaProperty>
//#include "managemodel.h"

VagonsModel::VagonsModel(QObject *parent)
    : QAbstractListModel(parent)
{
    int irole=Qt::UserRole+1;
    for (int idx = 0; idx < m_Vagon::staticMetaObject.propertyCount(); idx++) {
        QMetaProperty metaProperty = m_Vagon::staticMetaObject.property(idx);
        QString proprtyName=metaProperty.name();
        vagonsRoles[irole++] = qPrintable(proprtyName);
    }

    if (MVP_Import::instance()->gorka!=nullptr){
        for (int i=0; i<MVP_Import::instance()->otceps->l_vagons.size();i++) {
            addDataObject(VagonsObject(MVP_Import::instance()->otceps->l_vagons[i]));
            connect(MVP_Import::instance()->otceps->l_vagons[i],&m_Vagon::stateChanged,this,&VagonsModel::slotOtcepChanged);
        }
        //                connect(MVP_Import::instance()->gorka,&ModelGroupGorka::stateChanged,this,&OtcepsModel::slotOtcepChanged);
    }
    m_qmlCurrentIndex=0;
}

void VagonsModel::slotOtcepChanged()
{

    emit dataChanged(createIndex(0,0), createIndex(98, 8));

}
QVariantMap VagonsModel::get(int row) const
{
    return VagonsList[row].toMap();
}
void VagonsModel::addDataObject(const VagonsObject &dataVagonsObject)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    VagonsList << dataVagonsObject;
    endInsertRows();
}


int VagonsModel::rowCount(const QModelIndex &parent) const
{
    Q_ASSERT(checkIndex(parent));
    if (parent.isValid())
        return 0;
    return VagonsList.count();
}

QVariant VagonsModel::data(const QModelIndex &index, int role) const
{
    //    Q_ASSERT(checkIndex(index, QAbstractItemModel::CheckIndexOption::IndexIsValid));

    //    if (!hasIndex(index.row(), index.column(), index.parent()) || !index.isValid())
    //        return false;
    //    const ListVagons &item = VagonsList.at(index.row());
    //    if (role == SL_VAGON_CNT) return item.SL_VAGON_CNT;
    //    return QVariant();

    if(index.row() < 0 || index.row() >= VagonsList.count() || !index.isValid())
        return  QVariant();

    const VagonsObject &VagonsObject = VagonsList[index.row()];

    if (vagonsRoles.contains(role)){
        return VagonsObject.getState(vagonsRoles[role]);
    }
    return QVariant();

}

Qt::ItemFlags VagonsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> VagonsModel::roleNames() const
{

    auto  roles=QAbstractListModel::roleNames();

    foreach (auto key, vagonsRoles.keys()) {
        roles.insert(key,vagonsRoles[key]);
    }

    return  roles;
}
