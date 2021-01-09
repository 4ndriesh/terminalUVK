#include "fromsyb.h"
#include "QDebug"
#include "mvp_import.h"
#include "management.h"
#include "viewotcepsmodel.h"

Management &Mn = Management::instance();
FromSyb::FromSyb(QObject *parent) : QObject(parent)
{

}


void FromSyb::sortirArrived(const tSl2Odo2 *srt)
{
    // прверить что режим ввода установлен
    // если нет то запомнить и мигать кнопкой
    if (!loadSortirToUvk(srt)) {
        MVP_Import::instance()->_Id=0;
    }
}

void FromSyb::uvk_cmd_accept(QMap<QString, QString> m)
{
    if (m["ACCEPT_SRC"]!="UVK") return;
    Mn.addMsg(m["ACCEPT_TXT"],1);
}

bool FromSyb::loadSortirToUvk(const tSl2Odo2 *srt)
{
    return MVP_Import::instance()->loadSortirToUvk(srt);
}
