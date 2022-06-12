#ifndef PPMSSIMULATION_H
#define PPMSSIMULATION_H
#include "Instruments_global.h"
#include <QObject>
#include <memory>
#include <QPair>

//Internal Classes
#include "ppmsabstract.h"
#include "../Core/datapoint.h"
#include "ppmsdatapoint.h"


class INSTRUMENTS_EXPORT PpmsSimulation : public PpmsAbstract
{
    Q_OBJECT
public:
    PpmsSimulation();
    void openDevice() override;
    void setRotatorstate(bool rot) override;
    bool isOpen() const override;
    void shutdown() override;

protected:
    void setTempSetpointCore(double setpoint, double rate) override;
    void setMagFieldCore(double magField, double magRate) override;
    void setAngleCore(double angle) override;
    QPair<double,double> getTempSetpointCore() override;
    QPair<double, double> getMagFieldCore() override;
    double getAngleCore() override;
    double getHeliumCore() override;
    PpmsDataPoint ppmsLogik() override;

private:
    double tempSetpoint_;
    double tempRate_;
    double fieldSetpoint_;
    double fieldRate_;
    double tempNow_;
    double magFieldSP_;
    double magRate_;
    double magFieldNow_;
    double angle_;
};

#endif // PPMSSIMULATION_H
