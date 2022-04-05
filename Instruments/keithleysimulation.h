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
    void openDevice() override;
    KeithleyDatapoint keithleyLogik() override;
    void setPulseAndMeasure(double value, double pWidth, double ratio) override;
    double getVoltage() override;
    double getCurrent() override;
    void resetRange() override;
    double getBackground() override;
    void resetBackground() override;
    void checkForError() override;
private:
    double current;
    double voltage;
    double pulseWidth;
    double ratio;
    double background;
};

#endif // KEITHLEYSIMULATION_H
