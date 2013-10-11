#-------------------------------------------------
#
# Project created by QtCreator 2013-10-08T13:12:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kolesikovkurs
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           task.cpp \
           modelmananger.cpp \
           complextask.cpp \
           simpletask.cpp

HEADERS += mainwindow.h \
           task.h \
           modelmananger.h \
           complextask.h \
           simpletask.h

FORMS    += mainwindow.ui
