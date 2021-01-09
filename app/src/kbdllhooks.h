#ifndef MOUSELOGGER_H
#define MOUSELOGGER_H

#include <QObject>
#include <windows.h>


class KBdllhooks : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(KBdllhooks)
public:
    static KBdllhooks &instance();
    explicit KBdllhooks(QObject *parent = nullptr);
    virtual ~KBdllhooks(){}
    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

//signals:
//    void mouseEvent();

//public slots:

private:
//    int VisibleEditButton;
    HHOOK   kbHook;
};

#endif // MOUSELOGGER_H
