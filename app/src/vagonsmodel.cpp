#include "vagonsmodel.h"
#include "otcepsmodel.h"
#include <iostream>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include "mvp_import.h"
#include <QMetaProperty>
#include <otcepsmodel.h>
#include "managemodel.h"


VagonsModel::VagonsModel(QObject *parent)
    : QAbstractListModel(parent)
{    
}

void VagonsModel::loadSortList(const tSl2Odo2 *srt)
{
    beginResetModel();
    if(srt){
        auto index = VagonsList.begin();
        foreach (const tSl2OdoRec2 &o, srt->vOtceps){
            foreach (const tSlVagon &v, o.vVag)
                index=VagonsList.insert(index,{v.NumV});
        }
    }
    endResetModel();
}

int VagonsModel::rowCount(const QModelIndex &parent) const
{
    Q_ASSERT(checkIndex(parent));
    if (parent.isValid())
        return 0;
    return VagonsList.size();
}

QVariant VagonsModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(checkIndex(index, QAbstractItemModel::CheckIndexOption::IndexIsValid));

    if (!hasIndex(index.row(), index.column(), index.parent()) || !index.isValid())
        return false;
    const ListVagons &item = VagonsList.at(index.row());
    if (role == SL_VAGON_CNT) return item.SL_VAGON_CNT;
    return QVariant();
}


Qt::ItemFlags VagonsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable; // FIXME: Implement me!
}

