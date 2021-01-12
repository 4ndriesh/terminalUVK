#ifndef MANAGEMENT_H
#define MANAGEMENT_H
#include "otcepsobject.h"
#include <QQmlExtensionPlugin>
#include <QtQml>


struct QML_ManagerButton
{
    Q_GADGET
    Q_PROPERTY(int putNadviga MEMBER m_putNadviga)
    Q_PROPERTY(int editing MEMBER m_editing)
    Q_PROPERTY(int regim MEMBER m_regim)
    Q_PROPERTY(bool wink_Stop MEMBER m_wStop)
    Q_PROPERTY(bool wink_Pause MEMBER m_wPause)
    Q_PROPERTY(bool wink_Nadvig MEMBER m_wNadvig)

public:
    int m_putNadviga;
    int m_editing=0;
    int m_regim;
    bool m_wStop=false;
    bool m_wPause=false;
    bool m_wNadvig=false;
};
Q_DECLARE_METATYPE(QML_ManagerButton)

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

class ManageModel: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QML_ManagerButton stateBt READ stateBt WRITE setStateBt NOTIFY stateBtChanged)

    Q_PROPERTY(int qmlCurentIndex READ getCurrentItem WRITE setCurrentItem NOTIFY qmlCurrentItemChanged)

    Q_PROPERTY(int textInput READ textInput WRITE setTextInput NOTIFY textInputChanged)

    Q_PROPERTY(QStringList listMsg READ getListMsg NOTIFY listMsgChanged)

    Q_PROPERTY(bool timerDelMsg READ getTimerDelMsg NOTIFY timerDelMsgChanged)

    Q_PROPERTY(StructProgressBar qmlStatusPB READ getStatusPB WRITE setStatusPB NOTIFY statusPBChanged)
public:
    explicit ManageModel(QObject *parent = nullptr);
    virtual ~ManageModel(){}
public:
    static ManageModel &instance(){
        static ManageModel *_instance=0;
        if(_instance ==0){
            _instance=new ManageModel();
        }
        return *_instance;
    }

public slots:
    void addMsg(const QString &, int);
    void deleteFromList();
    void deleteMsg();
    void getRndChart();
    void addOtcepUP(int);
    void addOtcepDown(int);
    void addOtcepClearAll();
signals:
    void stateBtChanged();
    void maximumValuePBChanged();
    void showMessage(QString colorMessage, QString textMessage);
    void textInputChanged();
    void qmlCurrentItemChanged();
    void statusPBChanged();
    void listMsgChanged();
    void timerDelMsgChanged();
    void setRndChart(int qmlX, int qmlY);

public:
    QML_ManagerButton m_stateBt;
    QML_ManagerButton stateBt()const {return m_stateBt;}
    void setStateBt(const QML_ManagerButton &stateBt)
    {
        m_stateBt = stateBt;
        emit stateBtChanged();
    }

    int m_textInput;
    int textInput()const {return m_textInput;}
    void setTextInput(const int &Put)
    {
        m_textInput = Put;
        emit textInputChanged();
    }

    int acceptRegim;
    void accept();

    bool timerDelMsg;
    bool getTimerDelMsg()const;

    //Управляет сообщениями
    QStringList m_listMsg;
    QStringList getListMsg()const{return m_listMsg;}

    //Управляет курсором листвью
    int qmlCurentIndex;
    int getCurrentItem()const{return qmlCurentIndex;}
    void setCurrentItem(const int &index){
        qmlCurentIndex = index;
        //    emit qmlCurrentItemChanged();
    }


    void setRegim(const int &);
    void setPutNadviga(const int &);

    StructProgressBar qmlStatusPB;
    StructProgressBar getStatusPB()const;
    void setStatusPB(const StructProgressBar &);

};

#endif // MANAGEMENT_H
