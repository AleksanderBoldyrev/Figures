#-------------------------------------------------
#
# Project created by QtCreator 2012-03-25T21:14:03
#
#-------------------------------------------------

QT       += core gui xml widgets

TARGET = figures
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    figure.cpp \
    customizedialog.cpp

HEADERS  += mainwindow.h \
    figure.h \
    customizedialog.h

FORMS    += mainwindow.ui \
    customizedialog.ui

DISTFILES +=

RESOURCES += \
    icon.qrc
