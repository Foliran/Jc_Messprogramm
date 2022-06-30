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
    void initializeSettings(double pWidth, double ratio, int nPulses, double timeBetwPuls, bool reversed) override;
    void setPulseAndMeasure(double value) override;
    double getVoltage() override;
    double getCurrent() override;
    void getBackground() override;
    void setBusyBackground(bool x) override;
    void resetRange() override;
    void setBackground(double value) override;
    void checkForError() override;
    void setOutputOff() override;
    bool busyBackground;
    bool measuredBackground;

private:
    std::shared_ptr<GPIB> gpib;
    int address;
    int numberPulses;
    double current;
    double voltage;
    double background;
    double pulseWidth;
    double interPulseTime;
    bool pulseReversed;
};

#endif // KEITHLEYTSP_H
