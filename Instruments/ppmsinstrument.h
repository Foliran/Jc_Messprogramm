#ifndef PPMSINSTRUMENT_H
#define PPMSINSTRUMENT_H

#include "Instruments_global.h"
#include <QObject>
#include <memory>
#include <QPair>
#include <string>
#include <locale>
#include <sstream>
#include <iomanip>
#include <iostream>

//Internal Classes
#include "gpib.h"
#include "../Core/datapoint.h"
#include "ppmsdatapoint.h"
#include "ppmsabstract.h"

/*
Die Klasse ist komplett aus dem InduMessprogramm übernommen
*/

class INSTRUMENTS_EXPORT PpmsInstrument : public PpmsAbstract
{
    Q_OBJECT
public:
    PpmsInstrument(std::shared_ptr<GPIB> gpib, int address);
    void openDevice() override;
    void setRotatorstate(bool rotator) override;
    bool isOpen() const override;

protected:
    void setTempSetpointCore(double setpoint, double rate) override;
    void setMagFieldCore(double magField, double magRate) override;
    void setAngleCore(double angle) override;
    QPair<double, double> getTempSetpointCore() override;
    QPair<double, double> getMagFieldCore() override;
    double getAngleCore() override;
    double getHeliumCore() override;
    PpmsDataPoint ppmsLogik() override;

private:
    std::string dtoStr(double number, int n);
    std::stringstream sstring;
    std::shared_ptr<GPIB> gpib;
    int address;
    bool rotState;
    std::int32_t dataMask;

};

#endif // PPMSCORE_H
