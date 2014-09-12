#-------------------------------------------------
#
# Project created by QtCreator 2014-09-12T15:51:13
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = organizer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    goodsdialog.cpp \
    purchaserdialog.cpp

HEADERS  += mainwindow.h \
    goodsdialog.h \
    utility.h \
    purchaserdialog.h

FORMS    += mainwindow.ui \
    goods.ui \
    purchaser.ui
