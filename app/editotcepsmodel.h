#ifndef REDACTOTCEPLIST_H
#define REDACTOTCEPLIST_H

#include "otcepsobject.h"

#include <QAbstractListModel>
#include <QTimer>

class EditOtcepsModel : public QAbstractListModel
{
    Q_OBJECT
    QTimer * timer;
public slots:
    void deleteFromEditOtcepList(int);
    void addToList();
    void sendToSYB();
signals:
public:
    enum datasourceRoles {
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

    explicit EditOtcepsModel(QObject *parent = nullptr);

    void deleteDataSourceObject();

    void addDataObject(const DataObject &dataObject);
    Q_INVOKABLE QVariantMap get(int row) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;


    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;
    //bool checkIndex(const QModelIndex &index) const;

private:

    QList<DataObject> EditOtcepList;
};
#endif // REDACTOTCEPLIST_H
