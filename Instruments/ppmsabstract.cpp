#include "ppmsabstract.h"
#include <QDebug>

const double MAXTEMP = 350;
const double MINTEMP = 1.9;
const double MAXRATE = 20;
const double MINRATE = 0.1;

const double MAXANGLE = 360;
const double MINANGLE = 0;

void PpmsAbstract::setTempSetpoint(double setpoint, double rate)
{
    if (!isOpen())
    {
        return;
    }

    if (setpoint > MAXTEMP)
    {
        setpoint = MAXTEMP;
    }
    if (setpoint < MINTEMP)
    {
        setpoint = MINTEMP;
    }
    if (rate > MAXRATE)
    {
        rate = MAXRATE;
    }
    if (rate < MINRATE)
    {
        rate = MINRATE;
    }

    setTempSetpointCore(setpoint, rate);
    auto setpointReport = getTempSetpointCore();
    emit newTempSP(setpointReport.first, setpointReport.second);
}

void PpmsAbstract::setMagField(double magField, double magRate)
{
    //Q_UNUSED(magRate);

    if (!isOpen())
    {
        return;
    }

    magField *= 10;
    if (maxPosMagField < magField)
    {
        magField = maxPosMagField;
        QString errorMag = ("The maximum magField is too high and will automaticly be reduced to: ");
        errorMag.append(QString::number(maxPosMagField));
        emit newErrorPPMS(errorMag);
    }
    if (ppmsHelium < 60)
    {
        magField = 0;
        QString errorhel = ("Helium is too low for Magnetic Field!");
        emit newErrorPPMS(errorhel);
    }

    setMagFieldCore(magField, magRate);
    auto setpointReport = getMagFieldCore();
    emit newMagSP(setpointReport.first, setpointReport.second);
}

void PpmsAbstract::setAngle(double angle)
{
    if (!isOpen())
    {
        return;
    }

    if (angle > MAXANGLE)
    {
        angle = MAXANGLE;
    }
    if (angle < MINANGLE)
    {
        angle = MINANGLE;
    }

    setAngleCore(angle);
    auto angleReport = getAngleCore();
    emit newAngleSP(angleReport);
}


