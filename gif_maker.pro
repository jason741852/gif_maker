#-------------------------------------------------
#
# Project created by QtCreator 2017-03-27T16:22:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gif_maker
TEMPLATE = app
LIBS += `pkg-config opencv --libs`


SOURCES += main.cpp\
        mainwindow.cpp\
    helper.cpp \
    gif_maker.cpp

HEADERS  += mainwindow.h\
        helper.h \
    gif_maker.h

FORMS    += mainwindow.ui
