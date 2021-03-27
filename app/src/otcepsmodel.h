#ifndef DATASOURCEMODEL_H
#define DATASOURCEMODEL_H
#include "otcepsobject.h"
#include "managemodel.h"
#include <QAbstractListModel>
#include <QTimer>

struct tSl2Odo2;

class OtcepsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_DISABLE_COPY(OtcepsModel)

    QTimer * timer;

public:
    explicit OtcepsModel(QObject *parent=nullptr);
    virtual ~OtcepsModel(){}
    static OtcepsModel &instance(){
        static OtcepsModel *_instance=nullptr;
        if(_instance == nullptr){
            _instance=new OtcepsModel();
        }
        return *_instance;
    }

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
    int row_Count=0;
    int rowVag_Count=0;
private:    
    QList<DataObject> ViewOtcepList;
    QHash<int, QByteArray> otcepRoles;


public slots:
    int countEnabled();
    void sortirArrived(const tSl2Odo2 *srt);
    void uvk_cmd_accept(QMap<QString,QString> m);
};
#endif // DATASOURCEMODEL_H
