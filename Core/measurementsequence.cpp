#include "measurementsequence.h"

MeasurementSequence::MeasurementSequence() : supraName("")
, fileName("")
, magneticField(0)
, coilAngle(0)
{
}

MeasurementSequence::~MeasurementSequence()
{
}

QString MeasurementSequence::getSupraName() const
{
    return supraName;
}

void MeasurementSequence::setSupraName(const QString name)
{
    supraName = name;
}

double MeasurementSequence::getMagneticField() const
{
    return magneticField;
}

void MeasurementSequence::setMagneticField(double field)
{
    magneticField = field;
}

double MeasurementSequence::getCoilAngle() const
{
    return coilAngle;
}

void MeasurementSequence::setCoilAngle(double angle)
{
    coilAngle = angle;
}

QString MeasurementSequence::getFileName() const
{
    return fileName;
}

void MeasurementSequence::setFileName(const QString name)
{
    fileName = name;
}

int MeasurementSequence::getPulseMode() const {
    //qDebug() << "MeasSeqJc pulseMode is " << pMode;
    return pMode;
}
void MeasurementSequence::setPulseMode(int newMode) {
    //qDebug() << "MeasSeqJc pulseMode is now " << newMode;
    pMode = newMode;
}


