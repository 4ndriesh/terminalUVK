#include "kbdllhooks.h"
#include <QDebug>
#include "viewotcepsmodel.h"
#include "mvp_import.h"
#include "management.h"

KBdllhooks &KBdllhooks::instance()
{
    static KBdllhooks _instance;
    return _instance;
}

KBdllhooks::KBdllhooks(QObject *parent) : QObject(parent)
{
//    VisibleEditButton=1;
    HINSTANCE hInstance = GetModuleHandle(NULL);

    kbHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, 0);
    if (kbHook == NULL) {
        qWarning() << "KeyBoard Hook failed";
    }

}

LRESULT CALLBACK KBdllhooks::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    Q_UNUSED(nCode)
    Management &kbtouch = Management::instance();
    if (wParam == WM_KEYDOWN)
    {

        KBDLLHOOKSTRUCT * pKBStruct = (KBDLLHOOKSTRUCT *)lParam;
        qDebug()<<pKBStruct->vkCode;
        if(pKBStruct != nullptr) {
            switch (pKBStruct->vkCode) {
            qDebug()<<pKBStruct->vkCode;
            case VK_RETURN:
                kbtouch.qmlVisibleObject=(kbtouch.qmlVisibleObject+1)%2;
                emit kbtouch.qmlVisibleObjectChanged();
                emit kbtouch.qmlCurrentItemChanged();
                break;
            case VK_LCONTROL:

                kbtouch.qmlPutNadviga.m_set_putnadviga=1;
                kbtouch.qmlPutNadviga.m_select_putnadviga=0;
                kbtouch.setPutNadviga( kbtouch.qmlPutNadviga);
                kbtouch.setRegim(1);
                //                emit kbtouch.qmlPutNadvigaChanged();

                break;

            case VK_RCONTROL:

                kbtouch.qmlPutNadviga.m_set_putnadviga=2;
                kbtouch.qmlPutNadviga.m_select_putnadviga=1;
                kbtouch.setPutNadviga( kbtouch.qmlPutNadviga);
                kbtouch.setRegim(1);
                //                emit kbtouch.qmlPutNadvigaChanged();
                break;
            case VK_LSHIFT:
                //            case 80:
                //Пауза
                kbtouch.setRegim(2);
                break;
                //            case 83:
            case VK_RSHIFT:
                //Стоп
                kbtouch.setRegim(0);
                break;
                //            case   81:
            case VK_UP:
                //UP

                if(kbtouch.qmlVisibleObject)
                {
                    if (kbtouch.qmlCurentIndex<0)
                        kbtouch.qmlCurentIndex=0;
                    kbtouch.qmlCurentIndex--;
                    emit kbtouch.qmlCurrentItemChanged();
                }
                break;
                //            case  65:
            case VK_DOWN:
                //DOWN
                if(kbtouch.qmlVisibleObject)
                {
                    kbtouch.qmlCurentIndex++;
                    emit kbtouch.qmlCurrentItemChanged();
                }
                break;

            case VK_INSERT:
                //insert
                qDebug()<<"inser";
                break;
            case VK_DELETE:
                //del
                qDebug()<<"del";
                break;
            default:
                break;
            }
//            emit instance().mouseEvent();
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
