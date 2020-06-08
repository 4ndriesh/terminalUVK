#ifndef DATASOURCEMODEL_H
#define DATASOURCEMODEL_H

#include "otcepsobject.h"

#include <QAbstractListModel>
#include <QTimer>

struct tSl2Odo2;

struct StructProgressBar{
    Q_GADGET
    Q_PROPERTY(float set_value MEMBER m_set_value)
    Q_PROPERTY(int set_maximumValue MEMBER m_set_maximumValue)
    Q_PROPERTY(bool set_visible MEMBER m_set_visible)

public:
    float m_set_value;
    int m_set_maximumValue;
    bool m_set_visible;

};
Q_DECLARE_METATYPE(StructProgressBar)
struct StructPutNadviga {
    Q_GADGET
    Q_PROPERTY(int set_putnadviga MEMBER m_set_putnadviga)
    Q_PROPERTY(int select_putnadviga MEMBER m_select_putnadviga)
    Q_PROPERTY(bool chg_putnadviga MEMBER m_chg_putnadviga)

public:
    bool m_chg_putnadviga;
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

    Q_PROPERTY(QStringList listMsg READ getListMsg NOTIFY listMsgChanged)

    Q_PROPERTY(bool timerDelMsg READ getTimerDelMsg NOTIFY timerDelMsgChanged)

    Q_PROPERTY(StructProgressBar qmlStatusPB READ getStatusPB WRITE setStatusPB NOTIFY statusPBChanged)

    QTimer * timer;
public slots:
    void addMsg(const QString &, int);
    void deleteFromList();
    void deleteMsg();
    void getRndChart();
    void addOtcepUP(int);
    void addOtcepDown(int);
    void addOtcepClearAll();
    //    void slotStartProgressBar(){emit sendStartProgressBar();}
    //    void slotStopProgressBar(){emit sendStopProgressBar();}

signals:
    void maximumValuePBChanged();
    void showMessage(QString colorMessage, QString textMessage);
    void qmlVisibleObjectChanged();
    void qmlCurrentItemChanged();
    void qmRegimChanged();
    void qmlPutNadvigaChanged();
    void statusPBChanged();
    void listMsgChanged();
    void timerDelMsgChanged();
    void setRndChart(int qmlX, int qmlY);
    //    void sendStartProgressBar();
    //    void sendStopProgressBar();


public:
    bool timerDelMsg;
    bool getTimerDelMsg()const;

    QStringList m_listMsg;
    QStringList getListMsg()const;

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
    StructPutNadviga getPutNadviga()const;
    void setPutNadviga(const StructPutNadviga &);

    StructProgressBar qmlStatusPB;
    StructProgressBar getStatusPB()const;
    void setStatusPB(const StructProgressBar &);

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
    void uvk_cmd_accept(QMap<QString,QString> m);


};
#endif // DATASOURCEMODEL_H
