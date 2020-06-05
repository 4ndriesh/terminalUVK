#include "kbdllhooks.h"
#include <QDebug>
#include "app/viewotcepsmodel.h"

KBdllhooks &KBdllhooks::instance()
{
    static KBdllhooks _instance;
    return _instance;
}

KBdllhooks::KBdllhooks(QObject *parent) : QObject(parent)
{
    VisibleEditButton=1;
    HINSTANCE hInstance = GetModuleHandle(NULL);

    kbHook = SetWindowsHookEx(WH_KEYBOARD_LL, mouseProc, hInstance, 0);
    if (kbHook == NULL) {
        qWarning() << "KeyBoard Hook failed";
    }

}

LRESULT CALLBACK KBdllhooks::mouseProc(int Code, WPARAM wParam, LPARAM lParam)
{
    Q_UNUSED(Code)
    ViewOtcepsModel *kbtouch = ViewOtcepsModel::instance();
    if (wParam == WM_KEYDOWN)
    {
        KBDLLHOOKSTRUCT * pMouseStruct = (KBDLLHOOKSTRUCT *)lParam;
        qDebug()<<pMouseStruct->vkCode;
        if(pMouseStruct != nullptr) {
            switch (pMouseStruct->vkCode) {
            qDebug()<<pMouseStruct->vkCode;
            case 13:
                kbtouch->qmlVisibleObject=(kbtouch->qmlVisibleObject+1)%2;
                emit kbtouch->qmlVisibleObjectChanged();
                break;
            case 162:
                kbtouch->qmlPutNadviga.m_set_putnadviga=1;
                kbtouch->qmlPutNadviga.m_select_putnadviga=0;
                kbtouch->setPutNadviga( kbtouch->qmlPutNadviga);

                break;

            case 163:
                kbtouch->qmlPutNadviga.m_set_putnadviga=2;
                kbtouch->qmlPutNadviga.m_select_putnadviga=1;
                kbtouch->setPutNadviga( kbtouch->qmlPutNadviga);
                break;
            case 80:
                kbtouch->qmlRegim=2;
                emit kbtouch->qmRegimChanged();
                break;
            case 83:
                //
                kbtouch->qmlRegim=0;
                emit kbtouch->qmRegimChanged();
                break;
            case   81:
                //            case 38:
                //UP
                if(kbtouch->qmlVisibleObject)
                {
                    if (kbtouch->qmlCurentIndex<0)
                        kbtouch->qmlCurentIndex=0;
                    kbtouch->qmlCurentIndex--;
                    emit kbtouch->qmlCurrentItemChanged();
                }
                break;
            case  65:
                //            case 40:
                //DOWN
                if(kbtouch->qmlVisibleObject)
                {
                    kbtouch->qmlCurentIndex++;
                    emit kbtouch->qmlCurrentItemChanged();
                }
                break;
            default:
                break;
            }
            emit instance().mouseEvent();
        }
    }
    return CallNextHookEx(NULL, Code, wParam, lParam);
}
