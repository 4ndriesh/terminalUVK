#ifndef DATASOURCEMODEL_H
#define DATASOURCEMODEL_H

#include "otcepsobject.h"

#include <QAbstractListModel>
#include <QTimer>


class ViewOtcepsModel : public QAbstractListModel
{
    Q_OBJECT
    QTimer * timer;
public slots:
    void deleteFromList();

signals:
    void showMessage(QString colorMessage, QString textMessage);
    void setCurrentItem(int index);


public:
    enum dataRoles {
        nRole = Qt::UserRole ,
        marRole,
        mar_fRole,
        lenRole,
        len_fRole,
        katRole,
        kat_fRole,
        bazRole,
        nagRole,
        urRole,
        VRole,
        kzpRole


    };
    void getBySYB();
    explicit ViewOtcepsModel(QObject *parent = nullptr);
    void deleteDataSourceObject();
    void addDataObject(const DataObject &DataObject);
    QVariantMap get(int row) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;


    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;
    //bool checkIndex(const QModelIndex &index) const;

private:
    int index;
    QList<DataObject> ViewOtcepList;
};
#endif // DATASOURCEMODEL_H
