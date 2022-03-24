#include "keithleydatapoint.h"

KeithleyDatapoint::KeithleyDatapoint()
{
    current = 0;
    currentRate = 0;
    voltage = 0;
}

double KeithleyDatapoint::getCurrent() const {
    return current;
}

void KeithleyDatapoint::setCurrent(double value) {
    current = value;
}

double KeithleyDatapoint::getCurrentRate() const {
    return currentRate;
}

void KeithleyDatapoint::setCurrentRate(double value){
    currentRate = value;
}

double KeithleyDatapoint::getVoltage() const {
    return voltage;
}

void KeithleyDatapoint::setVoltage(double value) {
    voltage = value;
}

double KeithleyDatapoint::getBackground() const {
    return background;
}

void KeithleyDatapoint::setBackground(double value) {
    background = value;
}
