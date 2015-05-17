#-------------------------------------------------
#
# Project created by QtCreator 2015-05-17T09:53:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = flyZ
TEMPLATE = app


SOURCES += main.cpp\
        SettingsDialog.cpp \
    Field.cpp \
    Hive.cpp \
    Fly.cpp

HEADERS  += SettingsDialog.h \
    Field.h \
    Hive.h \
    Fly.h

FORMS    += SettingsDialog.ui \
    Field.ui
