#include <string>
#include "ppmsdatapoint.h"

PpmsDataPoint::PpmsDataPoint()
    : tempSetpoint(300)
    , tempLive(300)
    , userTemp(300)
    , tempRate(1)
    , magFieldLive(0)
    , magSetpoint(0)
    , rotLive(0)
    , rotSetpoint(0)
    , chamberLevel(60)
    , samplePressure(0)
    , statusPpms("")
    , datamask(0)
{
}

double PpmsDataPoint::getTempSetpoint() const
{
    return tempSetpoint;
}

void PpmsDataPoint::setTempSetpoint(double value)
{
    tempSetpoint = value;
}

double PpmsDataPoint::getTempLive() const
{
    return tempLive;
}

void PpmsDataPoint::setTempLive(double value)
{
    tempLive = value;
}

double PpmsDataPoint::getTempRate() const
{
    return tempRate;
}

void PpmsDataPoint::setTempRate(double value)
{
    tempRate = value;
}

double PpmsDataPoint::getMagFieldLive() const
{
    return magFieldLive;
}

void PpmsDataPoint::setMagFieldLive(double value)
{
    magFieldLive = value;
}

double PpmsDataPoint::getRotLive() const
{
    return rotLive;
}

void PpmsDataPoint::setRotLive(double value)
{
    rotLive = value;
}

double PpmsDataPoint::getChamberLevel() const
{
    return chamberLevel;
}

void PpmsDataPoint::setChamberLevel(double value)
{
    chamberLevel = value;
}

std::string PpmsDataPoint::getStatusPpms() const
{
    return statusPpms;
}

void PpmsDataPoint::setStatusPpms(const std::string& pvStatusPpms)
{
    statusPpms = pvStatusPpms;
}

double PpmsDataPoint::getMagSetpoint() const
{
    return magSetpoint;
}

void PpmsDataPoint::setMagSetpoint(double value)
{
    magSetpoint = value;
}

double PpmsDataPoint::getRotSetpoint() const
{
    return rotSetpoint;
}

void PpmsDataPoint::setRotSetpoint(double value)
{
    rotSetpoint = value;
}

double PpmsDataPoint::getSamplePressure() const
{
    return samplePressure;
}

void PpmsDataPoint::setSamplePressure(double value)
{
    samplePressure = value;
}

double PpmsDataPoint::getUserTemp() const
{
    return userTemp;
}

void PpmsDataPoint::setUserTemp(double value)
{
    userTemp = value;
}

uint32_t PpmsDataPoint::getDatamask() const
{
    return datamask;;
}

void PpmsDataPoint::setDatamask(const std::uint32_t& mask)
{
    datamask = mask;
}
