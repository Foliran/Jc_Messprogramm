#include "instrumentmanager.h"
#include <QDebug>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <memory>

//fertig

#include "../Instruments/ppmssimulation.h"
#include "../Instruments/ppmsabstract.h"
#include "../Instruments/ppmsinstrument.h"
#include "../Instruments/gpib.h"
#include "../Instruments/keithleyabstract.h"
#include "../Instruments/keithleysimulation.h"
#include "../Instruments/keithleyTSP.h"

const int PPMSADDRESS = 15;
const int KEITHLEYADDRESS = 26;


InstrumentManager::InstrumentManager()
    : timer(new QTimer(this))
    , gpib(std::make_shared<GPIB>())
{
    connect(timer, &QTimer::timeout,
        this, &InstrumentManager::onPolling);

    timer->start(1000);

    if (simulation)
    {
        ppms = new PpmsSimulation();
        keithley = new KeithleySimulation();
    }
    else
    {
        ppms = new PpmsInstrument(gpib, PPMSADDRESS);
        keithley = new KeithleyTSP(gpib, KEITHLEYADDRESS);
    }

    connect(ppms, &PpmsAbstract::newTempSP,
        this, &InstrumentManager::newTempSP);
    connect(ppms, &PpmsAbstract::newMagSP,
        this, &InstrumentManager::newMagSP);
    connect(ppms, &PpmsAbstract::newAngleSP,
        this, &InstrumentManager::newAngleSP);
    connect(ppms, &PpmsAbstract::newErrorPPMS,
        this, &InstrumentManager::newErrorMessage);
    connect(ppms, &PpmsAbstract::newRotstate,
        this, &InstrumentManager::newRotstate);
    connect(keithley, &KeithleyAbstract::newValues,
        this, &InstrumentManager::newValues);
}

void InstrumentManager::openDevice()
{
    ppms->openDevice();
}

void InstrumentManager::setTempSetpoint(double setpoint, double rate)
{
    ppms->setTempSetpoint(setpoint, rate);
}

void InstrumentManager::setMagFieldSP(double magField, double magRate)
{
    ppms->setMagField(magField, magRate);

}

void InstrumentManager::setAngle(double angle)
{
    ppms->setAngle(angle);
}

void InstrumentManager::setPulseAndMeasure(double v, double p, double r)
{
    keithley->setPulseAndMeasure(v, p, r);
}

void InstrumentManager::rotatorState(bool rotator)
{
    ppms->setRotatorstate(rotator);
}

void InstrumentManager::onPolling()
{
    DataPoint dataPoint;
    dataPoint.setPpmsData(std::make_shared<const PpmsDataPoint>(ppms->ppmsLogik()));
    dataPoint.setKeithleyData(std::make_shared<const KeithleyDatapoint>(keithley->keithleyLogik()));
    auto dPoint = std::make_shared<DataPoint>(dataPoint);
    emit newData(dPoint);
}
