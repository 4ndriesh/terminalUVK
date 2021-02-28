#include "railchain.h"
#include "mvp_import.h"
#include <QDebug>

RailChain::RailChain(QObject *parent) : QObject(parent)
{

}
//Ресет рельсовой цепи
void RailChain::resetRChain(const QString &valRChain)
{
    MVP_Import::instance()->resetDSOBusyRc(rch[valRChain]);
    return;
}
//Добавляем рельсовые цепи в список
void RailChain::addRChain()
{
    m_qmlRChain.clear();
    rch=MVP_Import::instance()->getDSOBusyRc();
    auto l=rch.keys();
    l.sort();
    int i=l.indexOf("ВСЕ");
    if (i>0) l.swapItemsAt(i,0);

    foreach (auto rc_name, l) {
        m_qmlRChain.append(rc_name);
    }
    //m_qmlRChain.sort();
    //std::reverse(m_qmlRChain.begin(), m_qmlRChain.end());
    emit qmlRChainChanged();
    return;
}

//Навигация по списку рельсовых цепей
void RailChain::keyUpDown(const int &updown)
{

    switch (updown) {
    case VK_UP:
        if(m_qmlChainItem>0)
        {
            m_qmlChainItem--;
            setQmlChainItem(m_qmlChainItem);
        }
        break;
    case VK_DOWN:
        if(m_qmlChainItem<rch.count()-1)
        {
            m_qmlChainItem++;
            setQmlChainItem(m_qmlChainItem);
        }
        break;
    }
    return;
}
void RailChain::accept()
{
    if(m_wink_reset)resetRChain(m_qmlRChain[m_qmlChainItem]);
    setWink_reset(false);
    return;
}
//Обработка клавы
void RailChain::keyDown(const DWORD &key)
{
    qDebug()<<"vkCode"<<key ;

    switch (key) {

    case VK_F5:
        emit closeRChainChanged();
        break;
    case VK_RETURN:
        accept();
        break;

    case VK_UP:
        //UP
        keyUpDown(VK_UP);
        break;
        //            case  65:
    case VK_DOWN:
        //DOWN
        keyUpDown(VK_DOWN);
        break;

    case VK_DELETE:
        //Удалить
        setWink_reset(true);
        break;
    }
    return;
}
