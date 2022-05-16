#ifndef MEASUREMENTSEQUENCE_H
#define MEASUREMENTSEQUENCE_H

#include "Core_global.h"
#include <QString>

class CORE_EXPORT MeasurementSequence
{
public:
    MeasurementSequence();
    virtual ~MeasurementSequence() = 0;

    //allgemein
    QString getSupraName() const;
    void setSupraName(const QString supraName);

    //PPMS
    double getMagneticField() const;
    void setMagneticField(double magneticField);

    double getCoilAngle() const;
    void setCoilAngle(double coilAngle);

    QString getFileName() const;
    void setFileName(const QString fileName);

    int getPulseMode() const;
    void setPulseMode(int newMode);

protected:
     //allgemein
    QString supraName;
    QString fileName;

    //PPMS
    double magneticField;
    double coilAngle;
    int pMode; //Ich mag keinen enum class, deshalb hier mit int:
               //1 = LinearOnce, 2 = LogOnce,
               //3 = LinearReversed, 4 = LogReversed


    //pulseMode mode;
};

#endif

