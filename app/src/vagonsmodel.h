#ifndef REDACTOTCEPLIST_H
#define REDACTOTCEPLIST_H

#include "otcepsobject.h"
#include <QAbstractListModel>
#include <QTimer>
#include <QDebug>

struct tSl2Odo2;
struct ListVagons
{
    quint32 SL_VAGON_CNT;
};
class VagonsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(MyRoles)
    QTimer * timer;
signals:
    void qmlEditOtcepItemChanged();
public:
    enum MyRoles {
        SL_VAGON_CNT = Qt::UserRole + 1
    };
    explicit VagonsModel(QObject *parent = nullptr);
    static VagonsModel &instance(){
        static VagonsModel *_instance=nullptr;
        if(_instance ==nullptr){
            _instance=new VagonsModel();
        }
        return *_instance;
    }

    void loadSortList(const tSl2Odo2 *srt);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QHash<int,QByteArray> roleNames() const override {
        return {
            { SL_VAGON_CNT, "SL_VAGON_CNT" }
        };
    }

private:
    QHash<int, QByteArray> vagonsRoles;
    QVector<ListVagons> VagonsList;
};
#endif // REDACTOTCEPLIST_H
