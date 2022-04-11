#ifndef MEASUREMENTSEQUENCE_H
#define MEASUREMENTSEQUENCE_H

#include "Core_global.h"
#include <QString>

class CORE_EXPORT MeasurementSequence
{
public:
    MeasurementSequence();
    virtual ~MeasurementSequence() = 0;
    enum class pulseMode {LinearOnce, LogOnce, LinearReversed, LogReversed};

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

protected:
     //allgemein
    QString supraName;
    QString fileName;

    //PPMS
    double magneticField;
    double coilAngle;

    pulseMode mode;
};

#endif

