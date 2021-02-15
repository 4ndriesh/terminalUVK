#ifndef MBUTTON_H
#define MBUTTON_H

#include <QObject>

#include <qdebug.h>
#include <qdatetime.h>
#include <qbasictimer.h>
#include <qcoreapplication.h>

// Implements a "TimeModel" class with hour and minute properties
// that change on-the-minute yet efficiently sleep the rest
// of the time.

class MinuteTimer : public QObject
{
    Q_OBJECT
public:
    MinuteTimer(QObject *parent) : QObject(parent)
    {
    }

    void start();

    void stop();

    int hour() const { return time.hour(); }
    int minute() const { return time.minute(); }
    int second() const { return time.second(); }

signals:
    void timeChanged();

protected:
    void timerEvent(QTimerEvent *) override;

private:
    QTime time;
    QBasicTimer timer;
};

class TimeModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int hour READ hour NOTIFY timeChanged)
    Q_PROPERTY(int minute READ minute NOTIFY timeChanged)
    Q_PROPERTY(int second READ second NOTIFY timeChanged)

public:
    explicit TimeModel(QObject *parent = nullptr);
    virtual ~TimeModel(){timer->stop();}
    static TimeModel &instance(){
        static TimeModel *_instance=0;
        if(_instance ==0){
            _instance=new TimeModel();
        }
        return *_instance;
    }


//    TimeModel(QObject *parent=nullptr) : QObject(parent)
//    {
//        if (++instances == 1) {
//            if (!timer)
//                timer = new MinuteTimer(QCoreApplication::instance());
//            connect(timer, &MinuteTimer::timeChanged, this, &TimeModel::timeChanged);
//            timer->start();
//        }
//    }

//    ~TimeModel() override
//    {
//        if (--instances == 0) {
//            timer->stop();
//        }
//    }

    int minute() const { return timer->minute(); }
    int hour() const { return timer->hour(); }
    int second() const { return timer->second(); }

signals:
    void timeChanged();

private:
    QTime t;
    static MinuteTimer *timer;
    static int instances;
};




#include <QObject>
#include <QQmlExtensionPlugin>
#include <QtQml>
#include "mbutton.h"

class QExampleQmlPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
//    Q_PLUGIN_METADATA(IID "mbutton.json")
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri)
    {
    Q_ASSERT(uri == QLatin1String("Base"));
    qmlRegisterType<TimeModel>(uri, 1, 0, "MButton");
    }
};
#endif // MBUTTON_H
