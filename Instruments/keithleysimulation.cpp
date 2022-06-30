#include "keithleysimulation.h"
#include "../Core/datapoint.h"
#include <QRandomGenerator>
#include <QDebug>


KeithleySimulation::KeithleySimulation():
    current(0)
  , voltage(0)
  , pulseWidth(0.03)
  , ratio(0.5)
  , background(-1000.0)
{
}

bool KeithleySimulation::isOpen() {
    return true;
}

void KeithleySimulation::openDevice()
{

}

KeithleyDatapoint KeithleySimulation::keithleyLogik()
{
    KeithleyDatapoint dPoint;
    dPoint.setCurrent(current);
    dPoint.setVoltage(voltage);
    return dPoint;
}

void KeithleySimulation::initializeSettings(double pWidth, double newRatio, int nPulses, double timeBetwPuls, bool reversed) {
    pulseWidth = pWidth;
    ratio = newRatio;
    Q_UNUSED(reversed)
    Q_UNUSED(nPulses)
    Q_UNUSED(timeBetwPuls)
}

void KeithleySimulation::setPulseAndMeasure(double value) {
    //qDebug() << "setPulsAndMeasure";

    current = value;
    voltage = value;
}


double KeithleySimulation::getVoltage()
{
    return voltage;
}

double KeithleySimulation::getCurrent()
{
    return current;
}

void KeithleySimulation::resetRange() {

}

void KeithleySimulation::getBackground(){
    background = 0;
}

void KeithleySimulation::setBusyBackground(bool x) {
    Q_UNUSED(x)
}

void KeithleySimulation::setBackground(double value){
    background = value;
}

void KeithleySimulation::checkForError() {

}

void KeithleySimulation::setOutputOff() {

}
