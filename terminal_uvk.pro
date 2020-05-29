QT += charts qml quick

CONFIG += c++11
TARGET = kbHook
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        app/editotcepsmodel.cpp \
    app/kbdllhooks.cpp \
        app/otcepsobject.cpp \
        app/viewotcepsmodel.cpp \
    main.cpp \
    mvp_import.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    app/editotcepsmodel.h \
#    app/emitwinthread.h \
    app/kbdllhooks.h \
    app/otcepsobject.h \
    app/viewotcepsmodel.h \
    mvp_import.h

# SYB
DEFINES += NO_LIBRARY
MVP_ROOT=$$PWD/../fromSYB
#MVP_ROOT=$$PWD/libs

#https://github.com/yx500/mvp_classes.git
include($$MVP_ROOT/mvp_classes/mvp_model_gorka.pri)
#https://github.com/yx500/common_src.git
include($$MVP_ROOT/common_src/signalmanager/signalmanager.pri)
include($$MVP_ROOT/common_src/gtcommandinterface/gtcommandinterface.pri)

DISTFILES +=
