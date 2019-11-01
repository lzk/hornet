include("../jkinterface/jkinterface.pri")
include(../common/common.pri)
include(../statusmonitor/statusmonitor.pri)
INCLUDEPATH += $${PWD}


HEADERS += \
    $${PWD}/filterlib.h \
    $$PWD/filtercommon.h \
    $$PWD/filterjobhistory.h


SOURCES += \
    $$PWD/filtercommon.cpp \
    $$PWD/filterjobhistory.cpp
