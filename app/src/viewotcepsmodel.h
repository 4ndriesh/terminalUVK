#ifndef DATASOURCEMODEL_H
#define DATASOURCEMODEL_H

#include "otcepsobject.h"

#include <QAbstractListModel>
#include <QTimer>


struct tSl2Odo2;

class ViewOtcepsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_DISABLE_COPY(ViewOtcepsModel)

    QTimer * timer;

public:
    static ViewOtcepsModel &instance();
    explicit ViewOtcepsModel(QObject *parent=nullptr);
    const tSl2Odo2 *tmpSrt=nullptr;
    void slotOtcepChanged();

    Q_INVOKABLE QVariantMap get(int row) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;
    void addDataObject(const DataObject &DataObject);
    bool loadSortirToUvk(const tSl2Odo2 *srt);

private:
    QList<DataObject> ViewOtcepList;
    QHash<int, QByteArray> otcepRoles;

public slots:
    int countEnabled();
    void sortirArrived(const tSl2Odo2 *srt);
    void uvk_cmd_accept(QMap<QString,QString> m);


};
#endif // DATASOURCEMODEL_H
