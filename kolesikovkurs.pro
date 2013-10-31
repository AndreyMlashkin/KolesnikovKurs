#-------------------------------------------------
#
# Project created by QtCreator 2013-10-08T13:12:00
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kolesikovkurs
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           task.cpp \
           complextask.cpp \
           simpletask.cpp \
           experimentmananger.cpp \
           qcustomplot/qcustomplot.cpp \
    experimentseriesmananger.cpp

HEADERS += mainwindow.h \
           task.h \
           complextask.h \
           simpletask.h \
           experimentmananger.h \
           qcustomplot/qcustomplot.h \
    experimentseriesmananger.h \
    modelapi.h

FORMS    += mainwindow.ui
