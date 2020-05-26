#ifndef DATASOURCEMODEL_H
#define DATASOURCEMODEL_H

#include "otcepsobject.h"

#include <QAbstractListModel>
#include <QTimer>

struct tSl2Odo2;

class ViewOtcepsModel : public QAbstractListModel
{

    Q_OBJECT
    QTimer * timer;
public slots:
    void deleteFromList();
    void setPutNadviga(int);
    int getPutNadviga();
    void setStopPause(int);
    int getStopPause();
    void editSortir(bool qmlVisivle);
    void getRndChart();

signals:
    void showMessage(QString colorMessage, QString textMessage);
    void setCurrentItem(int index);
    void setColorPutNadviga(int qmlPUT_NADVIG);
    void setColorStop(int qmlStopPause);
    void setColorPause(int qmlStopPause);
    void setEnabledEdit(bool qmlVisible);
    void setRndChart(int qmlX, int qmlY);
    void sendStartProgressBar();
    void sendStopProgressBar();


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
    explicit ViewOtcepsModel(QObject *parent=nullptr);
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
    bool loadSortirToUvk(const tSl2Odo2 *srt);

private:
    int qmlPUT_NADVIG;
    int qmlStopPause;
    bool qmlVisible;
    int qmlX;
    int qmlY;
//    bool qmlEnabled;
    int current_index;
    QList<DataObject> ViewOtcepList;
    QHash<int, QByteArray> otcepRoles;
public slots:
    void slotOtcepChanged();
    void sortirArrived(const tSl2Odo2 *srt);

};
#endif // DATASOURCEMODEL_H
