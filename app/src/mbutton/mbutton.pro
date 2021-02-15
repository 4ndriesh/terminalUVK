TEMPLATE = lib
CONFIG += qt plugin
QT += qml

TARGET = mbutton
DESTDIR = ../../../../terminal_uvk
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \
    mbutton.cpp

HEADERS += \
    mbutton.h

DISTFILES += \
    mbutton.qml

