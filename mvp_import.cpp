#include "mvp_import.h"
#include <QFileInfo>

MVP_Import::MVP_Import()
{

    MVP.setGetGtBufferInterface(&udp);
}

bool MVP_Import::load(QString fn)
{
    if (!QFileInfo(fn).exists()){
        qDebug() << "file not found " << QFileInfo(fn).absoluteFilePath();
        return false;
    }
    QObject *O=MVP.loadObject(fn);
    gorka=qobject_cast<ModelGroupGorka *>(O);
    if (!gorka) {
        qDebug() << "load problem " << fn;
        return false;
        return  false;
    }
    return true;
}
