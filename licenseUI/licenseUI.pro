#-------------------------------------------------
#
# Project created by QtCreator 2016-12-08T13:45:57
#
#-------------------------------------------------

QT       += core gui
CONFIG 	 += static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = licenseUI
TEMPLATE = app


SOURCES += main.cpp\
        license.cpp \
    success.cpp \
    error.cpp \
    systemtray.cpp

HEADERS  += license.h \
    success.h \
    error.h \
    systemtray.h

FORMS    += license.ui \
    success.ui \
    error.ui

RESOURCES += \
    image.qrc
