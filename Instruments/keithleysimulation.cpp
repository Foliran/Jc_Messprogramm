#include "keithleysimulation.h"
#include "../Core/datapoint.h"
#include <QRandomGenerator>


KeithleySimulation::KeithleySimulation():
    current(0)
  , voltage(0)
  , pulseWidth(0.03)
  , ratio(0.5)
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
void KeithleySimulation::setPulseAndMeasure(double value, double pWidth, double r) {
    pulseWidth = pWidth;
    ratio = r;
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
