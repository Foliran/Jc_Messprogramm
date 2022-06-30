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
    void initializeSettings(double pWidth, double ratio, int nPulses, double timeBetwPuls, bool reversed) override;
    void setPulseAndMeasure(double value) override;
    double getVoltage() override;
    double getCurrent() override;
    void resetRange() override;
    void getBackground() override;
    void setBusyBackground(bool x) override;
    void setBackground(double value) override;
    void checkForError() override;
    void setOutputOff() override;
private:
    double current;
    double voltage;
    double pulseWidth;
    double ratio;
    double background;
};

#endif // KEITHLEYSIMULATION_H
