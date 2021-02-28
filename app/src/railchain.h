#ifndef RAILCHAIN_H
#define RAILCHAIN_H

#include <QObject>
#include "mvp_import.h"

class RailChain : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(RailChain)
    Q_PROPERTY(bool wink_reset READ wink_reset WRITE setWink_reset NOTIFY wink_resetChanged)
    Q_PROPERTY(int qmlChainItem READ qmlChainItem WRITE setQmlChainItem NOTIFY qmlChainItemChanged)
    Q_PROPERTY(QStringList qmlRChain READ qmlRChain NOTIFY qmlRChainChanged)
public:
    explicit RailChain(QObject *parent = nullptr);
    virtual ~RailChain(){}
    static RailChain &instance(){
        static RailChain *_instance=0;
        if(_instance ==0){
            _instance=new RailChain();
        }
        return *_instance;
    }
signals:
    void qmlRChainChanged();
    void qmlChainItemChanged();
    void wink_resetChanged();
    void closeRChainChanged();

public:
    Q_INVOKABLE void resetRChain(const QString&);
    Q_INVOKABLE void addRChain();
    Q_INVOKABLE void keyDown(const DWORD &);
    Q_INVOKABLE void keyUpDown(const int&);

    QMap<QString, QString> rch;

    //Подтверждает команду кнопкой ENTER
    void accept();

    //Рельсовые цепи
    QStringList m_qmlRChain;
    QStringList qmlRChain()const{return m_qmlRChain;}

    //Управляет миганием рельсовых цепей
    bool m_wink_reset=0;
    bool wink_reset()const{return m_wink_reset;}
    void setWink_reset(const bool &index)
    {
        m_wink_reset = index;
        emit wink_resetChanged();
    }

    //Управляет курсором рельсовых цепей
    int m_qmlChainItem=0;
    int qmlChainItem()const{return m_qmlChainItem;}
    void setQmlChainItem(const int &index)
    {
        m_qmlChainItem = index;
        if(m_wink_reset)m_wink_reset=false;
        setWink_reset(m_wink_reset);
        emit qmlChainItemChanged();
    }

};

#endif // RAILCHAIN_H
