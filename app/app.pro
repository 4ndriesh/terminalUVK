QT += qml \
      quick \
      core \
      svg
QTPLUGIN += qsvg qsvgicon
CONFIG += c++17
#TEMPLATE = lib
TARGET = terminal_uvk
DESTDIR = ../../terminal_uvk
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
    src/json.cpp \
    src/kbdllhooks.cpp \
    src/managemodel.cpp \
    src/otcepsobject.cpp \
    src/railchain.cpp \
    src/viewotcepsmodel.cpp \
    src/mvp_import.cpp \
    main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH += C:\work_dir\C++\terminal_uvk
#QML2_IMPORT_PATH += $$PWD/qml/vkeyboard
#QML3_IMPORT_PATH += $$PWD/../test
# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

INCLUDEPATH += $$PWD/src

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/json.h \
    src/kbdllhooks.h \
    src/managemodel.h \
    src/otcepsobject.h \
    src/mvp_import.h \
    src/railchain.h \
    src/viewotcepsmodel.h

# SYB
#DEFINES += NO_LIBRARY
#MVP_ROOT=$$PWD/
MVP_ROOT=$$_PRO_FILE_PWD_/../../libs

#https://github.com/yx500/mvp_classes.git

include($$MVP_ROOT/mvp_classes/mvp_model_gorka.pri)
#https://github.com/yx500/common_src.git
include($$MVP_ROOT/common_src/signalmanager/signalmanager.pri)
include($$MVP_ROOT/common_src/gtcommandinterface/gtcommandinterface.pri)

DISTFILES += \
    qmldir \
    settings.json
