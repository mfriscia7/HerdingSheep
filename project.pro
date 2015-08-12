#-------------------------------------------------
#
# Project created by QtCreator 2015-01-30T14:56:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    quitwidget.cpp \
    gameboard.cpp \
    Qsquare.cpp \
    add_new_score.cpp \
    no_new_score.cpp \
    pausewindow.cpp \
    level_complete.cpp

HEADERS  += mainwindow.h \
    gameboard.h \
    quitwidget.h \
    QSquare.h \
    add_new_score.h \
    no_new_score.h \
    pausewindow.h \
    level_complete.h

FORMS    += mainwindow.ui

RESOURCES += \
    pics.qrc \
    instructions.qrc

CONFIG += c++11

DISTFILES +=
