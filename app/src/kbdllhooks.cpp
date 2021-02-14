#include "kbdllhooks.h"
#include <QDebug>
#include "viewotcepsmodel.h"
#include "mvp_import.h"
#include "managemodel.h"
#include "railchain.h"
#include "json.h"

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
        KBDLLHOOKSTRUCT * pKBStruct = (KBDLLHOOKSTRUCT *)lParam;
        if(pKBStruct != nullptr) {
            qDebug()<<"ManageModel::instance().selectHoook->>"<<ManageModel::instance().m_selectHook;
            if(ManageModel::instance().m_selectHook==1){
                RailChain::instance().keyDown(pKBStruct->vkCode);
            }
            else {
                ManageModel::instance().keyDown(pKBStruct->vkCode);
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
