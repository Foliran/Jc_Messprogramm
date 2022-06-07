QT -= gui

TEMPLATE = lib
DEFINES += CONTROLCORE_LIBRARY

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    instrumentmanager.cpp \
    measurementsmanager.cpp

HEADERS += \
    ControlCore_global.h \
    instrumentmanager.h \
    measurementsmanager.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Instruments/release/ -lInstruments
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Instruments/debug/ -lInstruments
else:unix: LIBS += -L$$OUT_PWD/../Instruments/ -lInstruments

INCLUDEPATH += $$PWD/../Instruments
DEPENDPATH += $$PWD/../Instruments
