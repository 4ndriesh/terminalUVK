TEMPLATE = lib
CONFIG += qt plugin
QT += qml

TARGET = clock
DESTDIR = ../../terminal_uvk
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \
    clock.cpp

HEADERS += \
    clock.h

DISTFILES += \
    clock.qml

