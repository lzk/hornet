#-------------------------------------------------
#
# Project created by QtCreator 2018-07-19T13:44:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include("../pro.pri")
TARGET = $${TARGET_stmui}
TEMPLATE = app

DEFINES += "HORNET=1"

include("../jkinterface/jkinterface.pri")
include("../statusmonitor/statusmonitor.pri")
include(../common/common.pri)
include(jklib/jklib.pri)
SOURCES += \
    uiconfig.cpp

HEADERS  += \
    uiconfig.h

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    about.cpp \

HEADERS  += \
    mainwindow.h \
    about.h \

FORMS    += mainwindow.ui \
    about.ui

RESOURCES += \
    image.qrc


CONFIG(debug ,debug|release){
    DEFINES += LOG_TO_STDERR
    DEFINES += DEBUG_DEBUG
}else{
}
