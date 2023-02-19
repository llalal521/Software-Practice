#-------------------------------------------------
#
# Project created by QtCreator 2016-03-21T19:09:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake
TEMPLATE = app


SOURCES += main.cpp\
    gamewidget2.cpp \
        widget.cpp \
    gamewidget.cpp

HEADERS  += widget.h \
    gamewidget.h \
    gamewidget2.h

RESOURCES += \
    image.qrc
