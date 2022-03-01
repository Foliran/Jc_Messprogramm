#ifndef INSTRUMENTMANAGER_H
#define INSTRUMENTMANAGER_H
/*Aufgabe: Daten von Messequence an PPMS-Core
 * & Keithley-Core weiter zu geben!
 */
#include "ControlCore_global.h"
#include <memory>
#include <QTimer>

//fertig

 //Internal Classes
#include "../Core/datapoint.h"
//Die Klassendefinition hier ist glaub ich zum Verhindern von circular dependencies
class PpmsAbstract;
class KeithleyAbstract;
class GPIB;
//class LockInSens;

class CONTROLCORE_EXPORT InstrumentManager : public QObject
{
    Q_OBJECT

signals:
    void newData(std::shared_ptr<DataPoint> dataPoint);
    void newTempSP(double setpoint, double rate);
    void newMagSP(double magField, double magRate);
    void newAngleSP(double angle);
    void newRotstate(bool rotActive);
    void newValues(double current, double voltage);
    void newErrorMessage(QString ppmsError);

public:
    InstrumentManager();
    ~InstrumentManager() = default;
    void openDevice();
    void setTempSetpoint(double setpoint, double rate);
    void setPulseAndMeasure(double v, double p, double r);
    void setMagFieldSP(double magField, double magRate);
    void setAngle(double angle);
    void rotatorState(bool rotator);

private slots:
    void onPolling();

private:
    QTimer* timer;
    bool simulation = false;
    PpmsAbstract* ppms;
    KeithleyAbstract *keithley;
    //keithley2651Aabstract* k2651;
    //keithleyDMM6500abstract* kdmm;
    std::shared_ptr <GPIB> gpib;
};

#endif // INSTRUMENTMANAGER_H

