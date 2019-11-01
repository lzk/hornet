#-------------------------------------------------
#
# Project created by QtCreator 2019-07-19T15:48:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

include("../pro.pri")
TARGET = $${TARGET_filterui}
INCLUDEPATH += $${PATH_common}/filterui/


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../../common/filterlib/filterlib.pri)

SOURCES += \
        ../../common/filterui/main.cpp \
        ../../common/filterui/mainwindow.cpp \
    cusermanage.cpp

HEADERS += \
        ../../common/filterui/mainwindow.h \
    ../../common/filterui/cusermanage.h \
    ../../common/filterui/appconfig.h

FORMS += \
        ../../common/filterui/mainwindow.ui

CONFIG(debug ,debug|release){
    DEFINES += LOG_TO_STDERR
    DEFINES += DEBUG_DEBUG
}else{
}
