QT -= gui

TEMPLATE = lib
DEFINES += MEASUREMENTS_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=

HEADERS += Measurements_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PPMS/release/ -lPPMS \
                                            -L$$OUT_PWD/../KeithleyDMM6500/release/ -lKeithleyDMM6500 \
                                            -L$$OUT_PWD/../Keithley2651A/release/ -lKeithley2651A

else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PPMS/debug/ -lPPMS \
                                            -L$$OUT_PWD/../KeithleyDMM6500/debug/ -lKeithleyDMM6500 \
                                            -L$$OUT_PWD/../Keithley2651A/debug/ -lKeithley2651A

else:unix: LIBS += -L$$OUT_PWD/../PPMS/ -lPPMS \
                -L$$OUT_PWD/../KeithleyDMM6500/ -lKeithleyDMM6500 \
                -L$$OUT_PWD/../Keithley2651A/ -lKeithley2651A

INCLUDEPATH += $$PWD/../PPMS \
            $$PWD/../KeithleyDMM6500 \
            $$PWD/../Keithley2651A

DEPENDPATH += $$PWD/../PPMS \
            $$PWD/../KeithleyDMM6500 \
            $$PWD/../Keithley2651A
