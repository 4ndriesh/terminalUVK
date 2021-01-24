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
    HINSTANCE hInstance = GetModuleHandle(NULL);

    kbHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, 0);
    if (kbHook == NULL) {
        qWarning() << "KeyBoard Hook failed";
    }

}

LRESULT CALLBACK KBdllhooks::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    Q_UNUSED(nCode)
    if (wParam == WM_KEYDOWN)
    {
        ManageModel &kbtouch = ManageModel::instance();
        KBDLLHOOKSTRUCT * pKBStruct = (KBDLLHOOKSTRUCT *)lParam;
        qDebug()<<pKBStruct->vkCode;
        if(pKBStruct != nullptr) {
            switch (pKBStruct->vkCode) {
            qDebug()<<pKBStruct->vkCode;
            case VK_TAB:

                if(kbtouch.m_stateBt.m_regim==1){
                    kbtouch.addMsg("Роспуск",1);
                }
                else{
                    kbtouch.m_stateBt.m_editing=!kbtouch.m_stateBt.m_editing;
                    if(kbtouch.m_stateBt.m_editing==1)
                        kbtouch.qmlCurentIndex=0;
                    emit kbtouch.qmlCurrentItemChanged();
                    kbtouch.stateBtChanged();
                }

                break;
            case VK_RETURN:
                kbtouch.accept();
                break;
            case VK_LCONTROL:
                //Роспуск 1
                kbtouch.qmlRegim(1);
                kbtouch.m_stateBt.m_bef_putNadviga=1;
                break;

            case VK_RCONTROL:
                //Роспуск 2
                kbtouch.qmlRegim(1);
                kbtouch.m_stateBt.m_bef_putNadviga=2;
                break;
            case VK_LSHIFT:
                //            case 80:
                //Пауза
                kbtouch.qmlRegim(2);
                break;
                //            case 83:
            case VK_RSHIFT:
                //Стоп
                kbtouch.qmlRegim(0);
                break;
                //            case   81:
            case VK_UP:
                //UP

                if(kbtouch.m_stateBt.m_editing && kbtouch.qmlCurentIndex>-1)
                {
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

            case VK_NEXT:
                //Вставить до
                if(kbtouch.m_stateBt.m_editing && kbtouch.qmlCurentIndex>-1)
                    kbtouch.addOtcep(kbtouch.qmlCurentIndex-1);
                break;
            case VK_PRIOR:
                //Вставить после
                if(kbtouch.m_stateBt.m_editing && kbtouch.qmlCurentIndex>-1)
                    kbtouch.addOtcep(kbtouch.qmlCurentIndex+1);
                break;
            case VK_DELETE:
                //Удалить все
                kbtouch.clearAllOtcep();
                break;
            case VK_BACK:
                //Удалить
                kbtouch.delOtcep(kbtouch.qmlCurentIndex);
                break;

            case VK_F1:
                kbtouch.m_textInput=25;
                emit kbtouch.textInputChanged();
                break;
            case VK_LEFT:
                kbtouch.qmlCurentIndex--;
                emit kbtouch.qmlCurrentItemChanged();
                break;
            case VK_RIGHT:
                kbtouch.qmlCurentIndex++;
                emit kbtouch.qmlCurrentItemChanged();
                break;
            default:
                break;

            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
