#ifndef INSTRUMENTMANAGER_H
#define INSTRUMENTMANAGER_H
#include "ControlCore_global.h"
#include <memory>
#include <QTimer>

#include "../Core/datapoint.h"
class PpmsAbstract;
class KeithleyAbstract;
class GPIB;

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
    void initializeSettings(double p, double r, int n, double t, bool reversed);
    void setPulseAndMeasure(double v);
    void measureBackground();
    void setBackground(double value);
    void setMagFieldSP(double magField, double magRate);
    void setAngle(double angle);
    void rotatorState(bool rotator);
    void shutdown();
    bool isBusyBackground();
    void setBusyBackground(bool x);
    QTimer* timer;

private slots:
    void onPolling();

private:
    int simulation;
    PpmsAbstract* ppms;
    KeithleyAbstract *keithley;
    std::shared_ptr <GPIB> gpib;
};

#endif // INSTRUMENTMANAGER_H

