#ifndef MANAGEMENT_H
#define MANAGEMENT_H
//#include "otcepsobject.h"
#include <QtQml>
#include <qt_windows.h>
#include <QQuickItem>
#include <QKeyEvent>
#include "otcepsmodel.h"
#include "json.h"
#include "manage_define.h"

struct QML_ManagerButton
{
    Q_GADGET
    Q_PROPERTY(int putNadviga MEMBER m_putNadviga)
    Q_PROPERTY(int pull MEMBER m_pull)
    Q_PROPERTY(int bef_putNadviga MEMBER m_bef_putNadviga)
    Q_PROPERTY(int regim MEMBER m_regim)
    Q_PROPERTY(int bef_regim MEMBER m_bef_regim)
    Q_PROPERTY(int tmp_Cursor MEMBER m_tmp_Cursor)
    Q_PROPERTY(int regim_Finish MEMBER m_regim_Finish)
    Q_PROPERTY(bool wink_Cursor MEMBER m_wCursor)
    Q_PROPERTY(bool wink_Stop MEMBER m_wStop)
    Q_PROPERTY(bool wink_Pause MEMBER m_wPause)
    Q_PROPERTY(bool wink_Pull MEMBER m_wPull)
    Q_PROPERTY(bool wink_Nadvig MEMBER m_wNadvig)
    Q_PROPERTY(bool wink_GetList MEMBER m_wGetList)

public:
    int m_putNadviga=0;
    int m_bef_putNadviga=0;
    int m_bef_regim=10;
    int m_tmp_Cursor=0;
    int m_regim=0;
    int m_pull=1;
    int m_regim_Finish=0;
    bool m_wCursor=false;
    bool m_wStop=false;
    bool m_wPause=false;
    bool m_wPull=false;
    bool m_wNadvig=false;
    bool m_wGetList=false;
};Q_DECLARE_METATYPE(QML_ManagerButton)

struct StructProgressBar{
    Q_GADGET
    Q_PROPERTY(float set_value MEMBER m_set_value)
    Q_PROPERTY(int set_maximumValue MEMBER m_set_maximumValue)
    Q_PROPERTY(bool set_visible MEMBER m_set_visible)

public:
    float m_set_value=0.0;
    int m_set_maximumValue=0;
    bool m_set_visible=false;
};

class ManageModel: public QObject
{

    Q_OBJECT

    Q_DISABLE_COPY(ManageModel)

    Q_PROPERTY(QML_ManagerButton stateBt READ stateBt WRITE setStateBt NOTIFY stateBtChanged)

    Q_PROPERTY(StructProgressBar qmlStatusPB READ qmlStatusPB NOTIFY statusPBChanged)

    //Управляет фокусом
    Q_PROPERTY_RWN(int,focus);
    //Управляет курсором листвью
    Q_PROPERTY_RWN(int,qmlCurrentIndex);

    //Общая переменная для ввода с клавиатуры номера пути
    Q_PROPERTY_RWN(QString,textInput);

    //Управляет сообщениями
    Q_PROPERTY_RN(QStringList,listMsg);

    //Удаляем сообщения с формы об ошибках
    Q_PROPERTY_RN(bool,timerDelMsg);

    //Установить хук на окно
    Q_PROPERTY_RW(int,selectHook);

    //Наличие увк
    Q_PROPERTY_RN(bool,uvkLive);

    //Сообщение в Highlite на событие
    Q_PROPERTY_RWN(QString,msgEvent);

    //Оповещение о новом сортирововчном листке
    Q_PROPERTY_RN(bool,newList);

private:    
    void setRegim(const int &);
    void setCurrentOtcep();
    void setPutNadviga(const int &);
    enum enumRegim{
        Stop=0,
        Rospusk=1,
        Pause=2,
        DelOtcep=3,
        InsertUp=4,
        InsertDown=5,
        InputPut=6,
        DelAllOtcep=7,
        SetCurrentOtcep=8,
        InputVag=9,
        Escape=10,
        GetNewList=12,
        Pull=14
    };

public:
    explicit ManageModel(QObject *parent = nullptr);
    virtual ~ManageModel(){}
    static ManageModel &instance(){
        static ManageModel *_instance=nullptr;
        if(_instance == nullptr){
            _instance=new ManageModel();
        }
        return *_instance;
    }

signals:
    void focusChanged();
    void msgEventChanged();
    void openRChainChanged();
    void stateBtChanged();
    void textInputChanged();
    void uvkLiveChanged();
    void newListChanged();
    void qmlCurrentIndexChanged();
    void statusPBChanged();
    void listMsgChanged();
    void timerDelMsgChanged();

public:
    Q_INVOKABLE int setPositionVagons();
    Q_INVOKABLE void updateOtcep();
    Q_INVOKABLE void qmlRegim(const int&);
    Q_INVOKABLE void addOtcep(const int&);
    Q_INVOKABLE void delOtcep();
    Q_INVOKABLE void clearAllOtcep();
    Q_INVOKABLE void inputPut(const QString&);
    Q_INVOKABLE void keyDown(const int &, const bool &);
    Q_INVOKABLE void keyUpDown(const int&);
    Q_INVOKABLE void deleteMsg();
    //Подтверждает команду кнопкой ENTER
    Q_INVOKABLE void accept();
    Json *notice=nullptr;
    void addMsg(const QString &);

    QML_ManagerButton m_stateBt;
    QML_ManagerButton stateBt()const {return m_stateBt;}
    void setStateBt(const QML_ManagerButton &stateBt)
    {
        m_stateBt = stateBt;
        emit stateBtChanged();
    }

    StructProgressBar m_qmlStatusPB;
    StructProgressBar qmlStatusPB()const {return m_qmlStatusPB;}
};

#endif // MANAGEMENT_H
