#ifndef MOUSELOGGER_H
#define MOUSELOGGER_H

#include <QObject>
#include <windows.h>
#include "managemodel.h"

class KBdllhooks : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(KBdllhooks)
public:
    explicit KBdllhooks(QObject *parent = nullptr);
    virtual ~KBdllhooks(){}
    static KBdllhooks &instance(){
        static KBdllhooks *_instance=0;
        if(_instance ==0){
            _instance=new KBdllhooks();
        }
        return *_instance;
    }
    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

    bool bWinKey=true;
private:
    HHOOK   kbHook;
};

#endif // MOUSELOGGER_H
