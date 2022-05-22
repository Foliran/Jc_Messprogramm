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
    void setPulseAndMeasure(double value, double pWidth, double ratio, int nPulses, double timeBetwPuls, bool reversed) override;
    double getVoltage() override;
    double getCurrent() override;
    double getBackground() override;
    void resetRange() override;
    void resetBackground() override;
    void checkForError() override;
    void setOutputOff() override;

private:
    std::shared_ptr<GPIB> gpib;
    int address;
    double current;
    double voltage;
    double background;
};

#endif // KEITHLEYTSP_H
