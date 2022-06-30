#ifndef KEITHLEYABSTRACT_H
#define KEITHLEYABSTRACT_H

#include <QObject>
#include "Instruments_global.h"
#include "keithleydatapoint.h"

class INSTRUMENTS_EXPORT KeithleyAbstract : public QObject
{
    Q_OBJECT
public:
    virtual bool isOpen() = 0;
    virtual KeithleyDatapoint keithleyLogik() = 0;
    virtual void openDevice() = 0;
    virtual void initializeSettings(double pWidth, double ratio, int nPulses, double timeBetwPuls, bool reversed) = 0;
    virtual void setPulseAndMeasure(double value) = 0;
    virtual double getVoltage() = 0;
    virtual double getCurrent() = 0;
    virtual void resetRange() = 0;
    virtual void getBackground() = 0;
    virtual void setBusyBackground(bool x) = 0;
    virtual void setBackground(double value) = 0;
    virtual void checkForError() = 0;
    virtual void setOutputOff() = 0;
    bool busy;
    bool busyBackground;

signals:
    void newValues(double current, double voltage);
    void newKeithleyError(QString KeithleyError);
};

#endif // KEITHLEYABSTRACT_H
