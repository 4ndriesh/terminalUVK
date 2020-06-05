#ifndef DATASOURCEMODEL_H
#define DATASOURCEMODEL_H

#include "otcepsobject.h"

#include <QAbstractListModel>
#include <QTimer>

struct tSl2Odo2;

struct StructPutNadviga {
    Q_GADGET
    Q_PROPERTY(int set_putnadviga MEMBER m_set_putnadviga)
    Q_PROPERTY(int select_putnadviga MEMBER m_select_putnadviga)
public:
    int m_set_putnadviga;
    int m_select_putnadviga;

};
Q_DECLARE_METATYPE(StructPutNadviga)
class ViewOtcepsModel : public QAbstractListModel
{

    Q_OBJECT
    Q_PROPERTY(int qmlCurentIndex READ getCurrentItem WRITE setCurrentItem NOTIFY qmlCurrentItemChanged)

    Q_PROPERTY(int qmlVisibleObject READ getEditSortir WRITE setEditSortir NOTIFY qmlVisibleObjectChanged)

    Q_PROPERTY(int qmlRegim READ getRegim WRITE setRegim NOTIFY qmRegimChanged)

    Q_PROPERTY(StructPutNadviga qmlPutNadviga READ getPutNadviga WRITE setPutNadviga NOTIFY qmlPutNadvigaChanged)

    QTimer * timer;
public slots:
    void deleteFromList();
    //    void setPutNadviga(int);
    //    int getPutNadviga();
    //    void setStopPause(int);
    //    int getStopPause();
    //    void editSortir(bool qmlVisivle);
    void getRndChart();
    void addOtcepUP(int);
    void addOtcepDown(int);
    void addOtcepClearAll();
    void slotStartProgressBar(){emit sendStartProgressBar();}
    void slotStopProgressBar(){emit sendStopProgressBar();}

signals:
    void showMessage(QString colorMessage, QString textMessage);
    void qmlVisibleObjectChanged();
    void qmlCurrentItemChanged();
    void qmRegimChanged();
    void qmlPutNadvigaChanged();

    void setColorPutNadviga(int qmlPUT_NADVIG);
    void setColorStop(int qmlRegim);
    void setColorPause(int qmlRegim);
    //    void setEnabledEdit(bool qmlVisible);
    void setRndChart(int qmlX, int qmlY);
    void sendStartProgressBar();
    void sendStopProgressBar();


public:
    int qmlCurentIndex;
    int getCurrentItem()const;
    void setCurrentItem(const int &);

    int qmlVisibleObject;
    int getEditSortir()const;
    void setEditSortir(const int &);

    int qmlRegim;
    int getRegim()const;
    void setRegim(const int &);

    StructPutNadviga qmlPutNadviga;
//    int qmlPUT_NADVIG;
    StructPutNadviga getPutNadviga()const;
    void setPutNadviga(const StructPutNadviga &);

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
    static ViewOtcepsModel *instance();
    explicit ViewOtcepsModel(QObject *parent=nullptr);

    QVariantMap get(int row) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;
    //bool checkIndex(const QModelIndex &index) const;

    bool loadSortirToUvk(const tSl2Odo2 *srt);
    void deleteDataSourceObject();
    void addDataObject(const DataObject &DataObject);

private:
    static ViewOtcepsModel* model;


    bool qmlVisible;
    int qmlX;
    int qmlY;

    QList<DataObject> ViewOtcepList;
    QHash<int, QByteArray> otcepRoles;
public slots:

    void slotOtcepChanged();
    void sortirArrived(const tSl2Odo2 *srt);

};
#endif // DATASOURCEMODEL_H
