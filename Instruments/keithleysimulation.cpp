#include "keithleysimulation.h"
#include "../Core/datapoint.h"


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

KeithleyDatapoint KeithleySimulation::keithleyLogik()
{
    srand((unsigned)time(0));
    KeithleyDatapoint dPoint;
    dPoint.setCurrent(current);
    dPoint.setVoltage(voltage);
    return dPoint;
}
std::pair<double, double> KeithleySimulation::setPulseAndMeasure(double value, double pWidth, double r) {
    pulseWidth = pWidth;
    ratio = r;
    std::pair<double, double> pair = std::make_pair(value, value);
    return pair;
}

double KeithleySimulation::getVoltage()
{
    return voltage;
}

double KeithleySimulation::getCurrent()
{
    return current;
}
