#-------------------------------------------------
#
# Project created by QtCreator 2016-01-07T00:32:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game_of_Life
TEMPLATE = app

QMAKE_CXXFLAGS += -openmp

SOURCES += main.cpp\
        displayjoc.cpp \
    gameoflife.cpp \
    matrix.cpp \
    about.cpp \
    license.cpp

HEADERS  += displayjoc.h \
    GameOfLife.h \
    matrix.h \
    about.h \
    license.h

FORMS    += displayjoc.ui
