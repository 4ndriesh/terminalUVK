#include "kbdllhooks.h"
#include <QDebug>
#include "viewotcepsmodel.h"
#include "mvp_import.h"
#include "managemodel.h"
#include "railchain.h"
#include "json.h"
#include "editotcepsmodel.h"

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
    static bool ctrl=false;
    if (wParam == WM_KEYDOWN)
    {
        KBDLLHOOKSTRUCT * pKBStruct = (KBDLLHOOKSTRUCT *)lParam;
        if(pKBStruct != nullptr) {
            if(pKBStruct->vkCode==VK_LCONTROL || pKBStruct->vkCode==VK_CONTROL){
                ctrl=true;
                return CallNextHookEx(NULL, nCode, wParam, lParam);
            }
            if(ManageModel::instance().m_selectHook==1){
                RailChain::instance().keyDown(pKBStruct->vkCode);
            }
            else if(ManageModel::instance().m_selectHook==2){
                EditOtcepsModel::instance().keyDown(pKBStruct->vkCode);
            }
            else {
                ManageModel::instance().keyDown(pKBStruct->vkCode,ctrl);
            }
        }
    }
    if (wParam == WM_KEYUP)
    {
        ctrl=false;
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
