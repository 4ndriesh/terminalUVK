#ifndef DATASOURCEMODEL_H
#define DATASOURCEMODEL_H

#include "otcepsobject.h"

#include <QAbstractListModel>
#include <QTimer>


struct tSl2Odo2;
class ViewOtcepsModel : public QAbstractListModel
{

    QTimer * timer;

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
public:
    static ViewOtcepsModel &instance();
    explicit ViewOtcepsModel(QObject *parent=nullptr);

    void slotOtcepChanged();

    QVariantMap get(int row) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;
    //bool checkIndex(const QModelIndex &index) const;
    void addDataObject(const DataObject &DataObject);
    bool loadSortirToUvk(const tSl2Odo2 *srt);
    void deleteDataSourceObject();


private:
    static ViewOtcepsModel* model;


    bool qmlVisible;
    int qmlX;
    int qmlY;

    QList<DataObject> ViewOtcepList;
    QHash<int, QByteArray> otcepRoles;
public slots:

    void sortirArrived(const tSl2Odo2 *srt);
    void uvk_cmd_accept(QMap<QString,QString> m);


};
#endif // DATASOURCEMODEL_H
