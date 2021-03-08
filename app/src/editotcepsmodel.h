#ifndef REDACTOTCEPLIST_H
#define REDACTOTCEPLIST_H

#include "otcepsobject.h"
#include <QAbstractListModel>
#include <QTimer>
#include <QDebug>


struct ListOtcep
{
    int sp;
    int sl_vagon_cnt;
};
class EditOtcepsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(MyRoles)
    Q_PROPERTY(int qmlEditOtcepItem READ qmlEditOtcepItem WRITE setQmlEditOtcepItem NOTIFY qmlEditOtcepItemChanged)
    QTimer * timer;
public slots:
    void deleteFromEditOtcepList(int);
    void addToList();
signals:
    void qmlEditOtcepItemChanged();
public:
    enum MyRoles {
            SP = Qt::UserRole + 1,
            SL_VAGON_CNT,
        };
    explicit EditOtcepsModel(QObject *parent = nullptr);
    static EditOtcepsModel &instance(){
        static EditOtcepsModel *_instance=0;
        if(_instance ==0){
            _instance=new EditOtcepsModel();
        }
        return *_instance;
    }

    void deleteDataSourceObject();

    Q_INVOKABLE void clearAll();
    Q_INVOKABLE void insertOtcep(const int&);
    Q_INVOKABLE void addDataObject();
    Q_INVOKABLE void keyDown(const int &);
    Q_INVOKABLE void keyUpDown(const int &);
//    Q_INVOKABLE void addDataObject(const MyListItem &MyListItem);
    Q_INVOKABLE QVariantMap get(int row) const;

    //Управляет курсором рельсовых цепей
    int m_qmlEditOtcepItem=0;
    int qmlEditOtcepItem()const{return m_qmlEditOtcepItem;}
    void setQmlEditOtcepItem(const int &index)
    {
        qDebug()<<index;
        m_qmlEditOtcepItem = index;
//        emit qmlEditOtcepItemChanged();
    }
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;


    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int,QByteArray> roleNames() const override {
            return { { SP, "sp" },
                { SL_VAGON_CNT, "sl_vagon_cnt" }
            };
        }

private:
    QVector<ListOtcep> EditOtcepList;
};
#endif // REDACTOTCEPLIST_H
