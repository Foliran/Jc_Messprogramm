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
    virtual void setPulseAndMeasure(double value, double pWidth, double ratio) = 0;
    virtual double getVoltage() = 0;
    virtual double getCurrent() = 0;
    virtual void resetRange() = 0;
    virtual double getBackground() = 0;
    virtual void resetBackground() = 0;
    virtual void checkForError() = 0;

signals:
    void newValues(double current, double voltage);
    void newKeithleyError(QString KeithleyError);
};

#endif // KEITHLEYABSTRACT_H
