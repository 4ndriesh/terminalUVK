#include "kbdllhooks.h"
#include <QDebug>
#include "viewotcepsmodel.h"
#include "mvp_import.h"
#include "managemodel.h"

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
    ManageModel &kbtouch = ManageModel::instance();
    if (wParam == WM_KEYDOWN)
    {

        KBDLLHOOKSTRUCT * pKBStruct = (KBDLLHOOKSTRUCT *)lParam;
        qDebug()<<pKBStruct->vkCode;
        if(pKBStruct != nullptr) {
            switch (pKBStruct->vkCode) {
            qDebug()<<pKBStruct->vkCode;
            case VK_TAB:

//                kbtouch.qmlVisibleObject=(kbtouch.qmlVisibleObject+1)%2;
//                emit kbtouch.qmlVisibleObjectChanged();
                if(kbtouch.m_stateBt.m_regim==1){
                    kbtouch.addMsg("Роспуск",1);
                }
                else{
                    kbtouch.m_stateBt.m_editing=(kbtouch.m_stateBt.m_editing+1)%2;
                    emit kbtouch.qmlCurrentItemChanged();
                    kbtouch.stateBtChanged();
                }

                break;
            case VK_RETURN:
                kbtouch.accept();
                break;
            case VK_LCONTROL:
                //Роспуск 1
                kbtouch.acceptRegim=1;
                kbtouch.m_stateBt.m_putNadviga=1;
                kbtouch.m_stateBt.m_wPause=false;
                kbtouch.m_stateBt.m_wStop=false;
                kbtouch.m_stateBt.m_wNadvig=true;
                kbtouch.stateBtChanged();
                break;

            case VK_RCONTROL:
                //Роспуск 2
                kbtouch.acceptRegim=3;
                kbtouch.m_stateBt.m_putNadviga=2;
                kbtouch.m_stateBt.m_wPause=false;
                kbtouch.m_stateBt.m_wStop=false;
                kbtouch.m_stateBt.m_wNadvig=true;
                kbtouch.stateBtChanged();
                break;
            case VK_LSHIFT:
                //            case 80:
                //Пауза
                kbtouch.acceptRegim=2;
                kbtouch.m_stateBt.m_wPause=true;
                kbtouch.m_stateBt.m_wStop=false;
                kbtouch.m_stateBt.m_wNadvig=false;
                kbtouch.stateBtChanged();
                break;
                //            case 83:
            case VK_RSHIFT:
                //Стоп
                kbtouch.acceptRegim=0;
                kbtouch.m_stateBt.m_wStop=true;
                kbtouch.m_stateBt.m_wPause=false;
                kbtouch.m_stateBt.m_wNadvig=false;
                kbtouch.stateBtChanged();

                break;
                //            case   81:
            case VK_UP:
                //UP

                if(kbtouch.m_stateBt.m_editing && kbtouch.qmlCurentIndex>-1)
                {
//                    if (kbtouch.qmlCurentIndex>-1)
//                        kbtouch.qmlCurentIndex=0;
                    kbtouch.qmlCurentIndex--;
                    emit kbtouch.qmlCurrentItemChanged();
                }
                break;
                //            case  65:
            case VK_DOWN:
                //DOWN
                if(kbtouch.m_stateBt.m_editing)
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

            case VK_F1:
                //del
                kbtouch.m_textInput=25;
                emit kbtouch.textInputChanged();
                break;
            default:
                break;
            }
//            emit instance().mouseEvent();
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
