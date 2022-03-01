#include "keithleysimulation.h"
#include "../Core/datapoint.h"

#include <cstdlib>
#include <ctime>


KeithleySimulation::KeithleySimulation():
    currentSetpoint(0)
  , pulseWidth(0.03)
  , ratio(0.1)
{

}

bool KeithleySimulation::isOpen() {
    return true;
}

KeithleyDatapoint KeithleySimulation::keithleyLogik()
{
    srand((unsigned)time(0));
    KeithleyDatapoint dPoint;
    dPoint.setCurrent(rand()%10);
    dPoint.setVoltage(rand()%10);
    return dPoint;
}
std::pair<double, double> KeithleySimulation::setPulseAndMeasure(double value, double pWidth, double ratio) {
    srand((unsigned)time(0));
    double num1 = rand() % 10, num2 = rand() % 10;
    std::pair<double, double> randomPair = std::make_pair(num1, num2);
    return randomPair;
}

double KeithleySimulation::getVoltage()
{
    srand((unsigned)time(0));
    return (rand() % 10);
}

double KeithleySimulation::getCurrent()
{
    srand((unsigned)time(0));
    return (rand() % 10);
}
