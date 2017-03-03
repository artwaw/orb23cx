#-------------------------------------------------
#
# Project created by QtCreator 2017-03-02T11:36:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = orb2cx
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32:RC_ICONS += winIcon.ico
QMAKE_TARGET_COMPANY += Health Bridge Ltd.
QMAKE_TARGET_DESCRIPTION += Orbtalk to 3CX cost table converter
QMAKE_TARGET_COPYRIGHT += 2017 HBL
VERSION += 1.0

DISTFILES += \
    README.md
