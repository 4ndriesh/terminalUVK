TEMPLATE = lib
CONFIG += qt plugin
QT += qml

TARGET = timemodel
DESTDIR = ../app/uvk
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    timemodel.cpp

HEADERS += \
    timemodel.h

DISTFILES += \
    timemodel.qml

