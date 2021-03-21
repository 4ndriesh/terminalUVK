#ifndef RAILCHAIN_H
#define RAILCHAIN_H

#include <QObject>
#include "mvp_import.h"
#include "manage_define.h"

class RailChain : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(RailChain)
    //Управляет миганием рельсовых цепей
    Q_PROPERTY_RWN(bool,wink_reset);
    //Управляет курсором рельсовых цепей
    Q_PROPERTY_RWN(int,qmlChainItem);
    //Список Рельсовых цепей
    Q_PROPERTY_RWN(QStringList,qmlRChain);
public:
    explicit RailChain(QObject *parent = nullptr);
    virtual ~RailChain(){}
    static RailChain &instance(){
        static RailChain *_instance=nullptr;
        if(_instance ==nullptr){
            _instance=new RailChain();
        }
        return *_instance;
    }
    //Подтверждает команду кнопкой ENTER
    void accept();
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
};

#endif // RAILCHAIN_H
