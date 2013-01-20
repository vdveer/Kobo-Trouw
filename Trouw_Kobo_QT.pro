#-------------------------------------------------
#
# Project created by QtCreator 2012-12-15T23:42:55
#
#-------------------------------------------------

QT       += core gui

QT      += network


#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Trouw_Kobo_QT
TEMPLATE = app


SOURCES += main.cpp\
        trouwmain.cpp

HEADERS  += trouwmain.h

FORMS    += trouwmain.ui

LIBS+=-L/home/koen/kobo/fs/lib
INCLUDEPATH+=/home/koen/kobo/fs/include

unix:!macx: LIBS += -L$$PWD/quazip/ -lquazip

INCLUDEPATH += $$PWD/quazip
DEPENDPATH += $$PWD/quazip
