QT -= gui

TEMPLATE = lib
DEFINES += INSTRUMENTS_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gpib.cpp \
    keithleyabstract.cpp \
    keithleyTSP.cpp \
    keithleydatapoint.cpp \
    keithleysimulation.cpp \
    ppmsabstract.cpp \
    ppmsdatapoint.cpp \
    ppmsinstrument.cpp \
    ppmssimulation.cpp \
    status.cpp

HEADERS += \
    Instruments_global.h \
    gpib.h \
    keithleyTSP.h \
    keithleyabstract.h \
    keithleydatapoint.h \
    keithleysimulation.h \
    ni488.h \
    ppmsabstract.h \
    ppmsdatapoint.h \
    ppmsinstrument.h \
    ppmssimulation.h \
    status.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
