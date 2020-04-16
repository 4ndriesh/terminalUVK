#include "mvp_import.h"
#include <QFileInfo>

MVP_Import::MVP_Import():QObject(nullptr)
{

    MVP.setGetGtBufferInterface(&udp);
}

bool MVP_Import::load(QString fn)
{
    if (!QFileInfo(fn).exists()){
        qDebug() << "file not found " << QFileInfo(fn).absoluteFilePath();
        return false;
    }
    QTimer *timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MVP_Import::slotTimer);
    QObject *O=MVP.loadObject(fn);
    gorka=qobject_cast<ModelGroupGorka *>(O);
    if (!gorka) {
        qDebug() << "load problem " << fn;
        return false;
        return  false;
    }
    return true;
}

void MVP_Import::slotTimer()
{
    gorka->updateStates();
}
