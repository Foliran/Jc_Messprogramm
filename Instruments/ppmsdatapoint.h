#ifndef PPMSDATAPOINT_H
#define PPMSDATAPOINT_H

#include <string>

#include "Instruments_global.h"



class INSTRUMENTS_EXPORT PpmsDataPoint
{
public:
    PpmsDataPoint();


    double getTempSetpoint() const;
    void setTempSetpoint(double value);

    double getTempLive() const;
    void setTempLive(double value);

    double getTempRate() const;
    void setTempRate(double value);

    double getMagFieldLive() const;
    void setMagFieldLive(double value);

    double getRotLive() const;
    void setRotLive(double value);

    double getChamberLevel() const;
    void setChamberLevel(double value);

    std::string getStatusPpms() const;
    void setStatusPpms(const std::string& pvStatusPpms);

    double getMagSetpoint() const;
    void setMagSetpoint(double value);

    double getRotSetpoint() const;
    void setRotSetpoint(double value);

    double getSamplePressure() const;
    void setSamplePressure(double value);

    double getUserTemp() const;
    void setUserTemp(double value);

    uint32_t getDatamask() const;
    void setDatamask(const uint32_t& datamask);

private:
    //PpmsTemp
    double tempSetpoint;
    double tempLive;
    double userTemp;
    double tempRate;

    //PpmsMag
    double magFieldLive;
    double magSetpoint;

    //PpmsRot
    double rotLive;
    double rotSetpoint;

    //PPmsHeliumChamber
    double chamberLevel;
    double samplePressure;

    std::string statusPpms;
    uint32_t datamask;
};

#endif
