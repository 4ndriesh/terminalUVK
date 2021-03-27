#ifndef REDACTOTCEPLIST_H
#define REDACTOTCEPLIST_H

#include "vagonsobject.h"
#include <QAbstractListModel>
#include <QTimer>
#include <QDebug>
#include "manage_define.h"

class VagonsModel : public QAbstractListModel
{
    Q_OBJECT
    QTimer * timer;
signals:
    void qmlEditOtcepItemChanged();
    void qmlCurrentIndexChanged();
public:

    explicit VagonsModel(QObject *parent = nullptr);
    static VagonsModel &instance(){
        static VagonsModel *_instance=nullptr;
        if(_instance ==nullptr){
            _instance=new VagonsModel();
        }
        return *_instance;
    }
    Q_PROPERTY_RWN(int,qmlCurrentIndex);

    void slotOtcepChanged();
    void addDataObject(const VagonsObject &VagonsObject);
    QVariantMap get(int row) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QHash<int,QByteArray> roleNames() const override;

private:
    QList<VagonsObject> VagonsList;
    QHash<int, QByteArray> vagonsRoles;


};
#endif // REDACTOTCEPLIST_H
