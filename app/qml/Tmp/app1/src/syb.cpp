#include "syb.h"
#include <QMetaProperty>

Syb::Syb(QObject *parent) : QObject(parent)
{

}
void Syb::slotOtcepChanged()
{
    qDebug()<<"STATE_REGIM"<<MVP_Import::instance()->gorka->STATE_REGIM();
    Mn.qmlPutNadviga.m_set_putnadviga=MVP_Import::instance()->gorka->PUT_NADVIG();
    qDebug()<<"PUT_NADVIG"<<MVP_Import::instance()->gorka->PUT_NADVIG();
    Mn.qmlRegim=MVP_Import::instance()->gorka->STATE_REGIM();
    emit Mn.qmlPutNadvigaChanged();
    emit Mn.qmRegimChanged();
    beginResetModel();
    endResetModel();
}

void Syb::sortirArrived(const tSl2Odo2 *srt)
{
    // прверить что режим ввода установлен
    // если нет то запомнить и мигать кнопкой
    if (!loadSortirToUvk(srt)) {
        MVP_Import::instance()->_Id=0;
    }
}

void Syb::uvk_cmd_accept(QMap<QString, QString> m)
{
    if (m["ACCEPT_SRC"]!="UVK") return;
    Mn.addMsg(m["ACCEPT_TXT"],1);
}

bool Syb::loadSortirToUvk(const tSl2Odo2 *srt)
{
    return MVP_Import::instance()->loadSortirToUvk(srt);
}
