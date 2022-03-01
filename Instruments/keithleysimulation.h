#ifndef KEITHLEYSIMULATION_H
#define KEITHLEYSIMULATION_H

#include "Instruments_global.h"
#include "keithleyabstract.h"
#include "../Core/datapoint.h"
#include "keithleydatapoint.h"

class INSTRUMENTS_EXPORT KeithleySimulation : public KeithleyAbstract
{
public:
    KeithleySimulation();
    bool isOpen() override;
    KeithleyDatapoint keithleyLogik() override;
    std::pair<double, double> setPulseAndMeasure(double value, double pWidth, double ratio) override;
    double getVoltage() override;
    double getCurrent() override;
private:
    double currentSetpoint;
    double pulseWidth;
    double ratio;
};

#endif // KEITHLEYSIMULATION_H
