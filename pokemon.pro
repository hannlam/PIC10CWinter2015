#-------------------------------------------------
#
# Project created by QtCreator 2015-03-09T23:49:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pokemon
TEMPLATE = app


SOURCES += main.cpp\
        gameboard.cpp \
    instructions.cpp \
    mainwindow.cpp \
    gameover.cpp \
    theend.cpp

HEADERS  += gameboard.h \
    instructions.h \
    LCDnumber.h \
    mainwindow.h \
    gameover.h \
    theend.h

FORMS    += gameboard.ui \
    instructions.ui \
    LCDnumber.ui \
    mainwindow.ui \
    gameover.ui \
    theend.ui

CONFIG += c++11

RESOURCES += \
    resources.qrc
