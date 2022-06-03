#include "instrumentmanager.h"
#include <QDebug>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <memory>

#include <iostream>
#include <functional>
#include <chrono>
#include <thread>

#include "../Instruments/ppmssimulation.h"
#include "../Instruments/keithleysimulation.h"
#include "../Instruments/ppmsabstract.h"
#include "../Instruments/keithleyabstract.h"
#include "../Instruments/ppmsinstrument.h"
#include "../Instruments/keithleyTSP.h"
#include "../Instruments/gpib.h"

const int PPMSADDRESS = 15;
const int KEITHLEYADDRESS = 26;

InstrumentManager::InstrumentManager()
    : timer(new QTimer(this))
    , simulation(1) //0 -> beide Geräte Simulation; 1 -> PPMS Simulation, Keihtley angeschlossen, 2 ->  beide angeschlossen
    , gpib(std::make_shared<GPIB>())
{
    connect(timer, &QTimer::timeout,
        this, &InstrumentManager::onPolling);

    timer->start(1000);
    if (simulation == 0)
    {
        ppms = new PpmsSimulation;
        keithley = new KeithleySimulation;
    }
    else if(simulation == 1)
    {
        ppms = new PpmsSimulation;
        keithley = new KeithleyTSP(gpib, KEITHLEYADDRESS);
    }
    else if(simulation == 2)
    {
        ppms = new PpmsInstrument(gpib, PPMSADDRESS);
        keithley = new KeithleyTSP(gpib, KEITHLEYADDRESS);
    }

    connect(ppms, &PpmsAbstract::newTempSP, this, &InstrumentManager::newTempSP);
    connect(ppms, &PpmsAbstract::newMagSP, this, &InstrumentManager::newMagSP);
    connect(ppms, &PpmsAbstract::newAngleSP, this, &InstrumentManager::newAngleSP);
    connect(keithley, &KeithleyAbstract::newValues, this, &InstrumentManager::newValues);
    connect(ppms, &PpmsAbstract::newErrorPPMS, this, &InstrumentManager::newErrorMessage);
    connect(keithley, &KeithleyAbstract::newKeithleyError, this, &InstrumentManager::newErrorMessage);
    connect(ppms, &PpmsAbstract::newRotstate, this, &InstrumentManager::newRotstate);
}

void InstrumentManager::openDevice()
{
    ppms->openDevice();
    keithley->openDevice();
    if(keithley->isOpen()) std::cout << "Keithley-Verbindung offen \n";
    else std::cout << "Keithley-Verbindung nicht offen \n";
    if(ppms->isOpen()) std::cout << "PPMS-Verbindung offen \n";
    else std::cout << "PPMS-Verbindung nicht offen \n";
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

void InstrumentManager::initializeSettings(double p, double r, int n, double t, bool reversed) {
    keithley->initializeSettings(p, r, n, t, reversed);
}

void InstrumentManager::setPulseAndMeasure(double v) {
    keithley->setPulseAndMeasure(v);
}

void InstrumentManager::measureBackground() {
    keithley->getBackground();
}

void InstrumentManager::resetBackground() {
    keithley->resetBackground();
}

void InstrumentManager::rotatorState(bool rotator)
{
    ppms->setRotatorstate(rotator);
}

bool InstrumentManager::isBusyBackground() {
    return keithley->busyBackground;
}
void InstrumentManager::onPolling()
{
    DataPoint dataPoint;
    dataPoint.setPpmsData(std::make_shared<const PpmsDataPoint>(ppms->ppmsLogik()));
    dataPoint.setKeithleyData(std::make_shared<const KeithleyDatapoint>(keithley->keithleyLogik()));
    auto dPoint = std::make_shared<DataPoint>(dataPoint);
    emit newData(dPoint);
}
