#ifndef keithleyTSP_H
#define keithleyTSP_H
#include "gpib.h"
#include <memory>
#include "Instruments_global.h"
#include "keithleyabstract.h"
#include "keithleydatapoint.h"


class INSTRUMENTS_EXPORT KeithleyTSP : public KeithleyAbstract
{

public:
    KeithleyTSP(std::shared_ptr<GPIB> gpibNew, int addressNew);
    bool isOpen() override;
    void openDevice() override;
    KeithleyDatapoint keithleyLogik() override;
    std::pair<double, double> setPulseAndMeasure(double value, double pWidth, double ratio) override;
    double getVoltage() override;
    double getCurrent() override;

private:
    std::shared_ptr<GPIB> gpib;
    int address;
    int handle;
    double current;
    double voltage;
};

#endif // KEITHLEYTSP_H
