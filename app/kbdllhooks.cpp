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
    ViewOtcepsModel *keyboardtouch = ViewOtcepsModel::instance();
    if (wParam == WM_KEYDOWN)
    {
        KBDLLHOOKSTRUCT * pMouseStruct = (KBDLLHOOKSTRUCT *)lParam;
        qDebug()<<pMouseStruct->vkCode;
        if(pMouseStruct != nullptr) {
            switch (pMouseStruct->vkCode) {

            case 13:
                keyboardtouch->editSortir(instance().VisibleEditButton);
                instance().VisibleEditButton=(instance().VisibleEditButton+1)%2;
                qDebug()<<instance().VisibleEditButton;
                break;
            case 162:
                keyboardtouch->setPutNadviga(1);
                break;
            case 163:
                keyboardtouch->setPutNadviga(2);
                break;
            case 80:
                keyboardtouch->setStopPause(2);
                break;
            case 83:
                keyboardtouch->setStopPause(0);
                break;           
            default:
                break;
            }
            emit instance().mouseEvent();
        }
    }
    return CallNextHookEx(NULL, Code, wParam, lParam);
}
