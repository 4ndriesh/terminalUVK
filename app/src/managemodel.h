#ifndef MANAGEMENT_H
#define MANAGEMENT_H
#include "otcepsobject.h"
#include <QQmlExtensionPlugin>
#include <QtQml>
#include <qt_windows.h>
#include <QQuickItem>
#include <QKeyEvent>
#include "viewotcepsmodel.h"

struct QML_ManagerButton
{
    Q_GADGET
    Q_PROPERTY(int putNadviga MEMBER m_putNadviga)
    Q_PROPERTY(int bef_putNadviga MEMBER m_bef_putNadviga)
    Q_PROPERTY(int editing MEMBER m_editing)
    Q_PROPERTY(int regim MEMBER m_regim)
    Q_PROPERTY(int bef_regim MEMBER m_bef_regim)
    Q_PROPERTY(bool wink_Stop MEMBER m_wStop)
    Q_PROPERTY(bool wink_Pause MEMBER m_wPause)
    Q_PROPERTY(bool wink_Nadvig MEMBER m_wNadvig)

public:
    int m_putNadviga;
    int m_bef_putNadviga;
    int m_bef_regim=10;
    int m_regim;
    int m_editing=0;
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

    Q_DISABLE_COPY(ManageModel)

    Q_PROPERTY(QML_ManagerButton stateBt READ stateBt WRITE setStateBt NOTIFY stateBtChanged)

    Q_PROPERTY(int qmlCurentIndex READ qmlCurrentItem WRITE setQmlCurrentItem NOTIFY qmlCurrentItemChanged)

    Q_PROPERTY(int textInput READ textInput WRITE setTextInput NOTIFY textInputChanged)

    Q_PROPERTY(int uvkLive READ uvkLive NOTIFY uvkLiveChanged)

    Q_PROPERTY(int newList READ newList WRITE setNewList NOTIFY newListChanged)

    Q_PROPERTY(QStringList qmlRChain READ qmlRChain NOTIFY qmlRChainChanged)

    Q_PROPERTY(QStringList listMsg READ getListMsg NOTIFY listMsgChanged)

    Q_PROPERTY(bool timerDelMsg READ getTimerDelMsg NOTIFY timerDelMsgChanged)

    Q_PROPERTY(StructProgressBar qmlStatusPB READ qmlStatusPB NOTIFY statusPBChanged)

private:

public:
    explicit ManageModel(QObject *parent = nullptr);
    virtual ~ManageModel(){}
    static ManageModel &instance(){
        static ManageModel *_instance=0;
        if(_instance ==0){
            _instance=new ManageModel();
        }
        return *_instance;
    }

public slots:
    void addMsg(const QString &, int);
    void deleteMsg();
    void getRndChart();
    void addRChain();


signals:
    void qmlRChainChanged();
    void stateBtChanged();
    void maximumValuePBChanged();
    void showMessage(QString colorMessage, QString textMessage);
    void textInputChanged();
    void uvkLiveChanged();
    void newListChanged();
    void qmlCurrentItemChanged();
    void statusPBChanged();
    void listMsgChanged();
    void timerDelMsgChanged();
    void setRndChart(int qmlX, int qmlY);

public:
    Q_INVOKABLE void qmlRegim(const int&);
    Q_INVOKABLE void addOtcep(const int&);
    Q_INVOKABLE void delOtcep(const int&);
    Q_INVOKABLE void clearAllOtcep();
    Q_INVOKABLE void inputPut(const int&);
    Q_INVOKABLE void resetRChain(const QString&);
    Q_INVOKABLE void keyDown(const DWORD &);
    Q_INVOKABLE void setRegimEdit();
    Q_INVOKABLE void keyUpDown(const DWORD&);

    QMap<QString, QString> m;

    QML_ManagerButton m_stateBt;
    QML_ManagerButton stateBt()const {return m_stateBt;}


    bool bWinKey=true;

    void controlWindow(DWORD vkKeyCode);

    void setStateBt(const QML_ManagerButton &stateBt)
    {
        m_stateBt = stateBt;
        emit stateBtChanged();
    }


    //Общая переменная для ввода с клавиатуры номера пути
    int m_textInput;
    int textInput()const {return m_textInput;}
    void setTextInput(const int &index){
        m_textInput = index;
        emit textInputChanged();
    }

    //Рельсовые цепи
    QStringList m_qmlRChain;
    QStringList qmlRChain()const{return m_qmlRChain;}

    //Наличие увк
    int m_uvkLive;
    int uvkLive()const {return m_uvkLive;}

    //Оповещение о новом сортирововчном листке
    int m_newList;
    int newList()const {return m_newList;}
    void setNewList(const int &index){
        m_newList = index;
        emit newListChanged();

    }

    //Подтверждает команду кнопкой ENTER
    void accept();

    //Удаляем сообщения с формы об ошибках
    bool timerDelMsg;
    bool getTimerDelMsg()const;

    //Управляет сообщениями
    QStringList m_listMsg;
    QStringList getListMsg()const{return m_listMsg;}

    //Управляет курсором листвью
    int m_qmlCurentIndex=0;
    int qmlCurrentItem()const{
//        qDebug()<<"getCurrent"<<m_qmlCurentIndex;
        return m_qmlCurentIndex;}

    void setQmlCurrentItem(const int &index){
        m_qmlCurentIndex = index;
//        qDebug()<<"setCurrent"<<m_qmlCurentIndex;
        emit qmlCurrentItemChanged();

    }

    void setRegim(const int &);
    void setPutNadviga(const int &);

    StructProgressBar m_qmlStatusPB;
    StructProgressBar qmlStatusPB()const {return m_qmlStatusPB;}

};

#endif // MANAGEMENT_H
