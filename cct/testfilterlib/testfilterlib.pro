#-------------------------------------------------
#
# Project created by QtCreator 2019-07-16T09:21:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include("../pro.pri")
TARGET = testfilterlib
INCLUDEPATH += $${PATH_common}/testfilterlib/
LIBS += -L$${OUT_PWD}/../libhxpl3z -lhxpl3z

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include("../../common/filterlib/filterlib.pri")

SOURCES += \
        ../../common/testfilterlib/main.cpp \
        ../../common/testfilterlib/mainwindow.cpp

HEADERS += \
        ../../common/testfilterlib/mainwindow.h

FORMS += \
        ../../common/testfilterlib/mainwindow.ui

CONFIG(debug ,debug|release){
    DEFINES += LOG_TO_STDERR
    DEFINES += DEBUG_DEBUG
}else{
    DEFINES += LOG_TO_STDERR
}
