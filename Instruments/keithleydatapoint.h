#ifndef KEITHLEYDATAPOINT_H
#define KEITHLEYDATAPOINT_H

#include "Instruments_global.h"


class INSTRUMENTS_EXPORT KeithleyDatapoint
{
public:
    KeithleyDatapoint();
    double getCurrent() const;
    void setCurrent(double value);
    double getCurrentRate() const;
    void setCurrentRate(double value);
    double getVoltage() const;
    void setVoltage(double value);

private:
    double current;
    double currentRate;
    double voltage;
};

#endif // KEITHLEYDATAPOINT_H
