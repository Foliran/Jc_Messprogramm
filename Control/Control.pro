QT += core gui charts

#TEMPLATE = lib
#DEFINES += GUI_LIBRARY
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
#CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += graphdiagram.cpp \
    mainWindow.cpp \
    mainWindow_main.cpp \
    measurementstable.cpp \
    openfilewindow.cpp \
    ppmswidget.cpp \
    startdialog.cpp \
    startdialogmulti.cpp \
    startdialogmulti_b.cpp

HEADERS += graphdiagram.h \
    mainWindow.h \
    measurementstable.h \
    openfilewindow.h \
    ppmswidget.h \
    startdialog.h \
    startdialogmulti.h \
    startdialogmulti_b.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += mainWindow.ui \
    openfilewindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Instruments/release/ -lInstruments
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Instruments/debug/ -lInstruments
else:unix: LIBS += -L$$OUT_PWD/../Instruments/ -lInstruments

INCLUDEPATH += $$PWD/../Instruments
DEPENDPATH += $$PWD/../Instruments

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ControlCore/release/ -lControlCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ControlCore/debug/ -lControlCore
else:unix: LIBS += -L$$OUT_PWD/../ControlCore/ -lControlCore

INCLUDEPATH += $$PWD/../ControlCore
DEPENDPATH += $$PWD/../ControlCore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core

RESOURCES += \
    Ressourcen.qrc
