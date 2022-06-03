#include "measseqjc.h"
#include <QDebug>

MeasSeqJc::MeasSeqJc()
    : currentStart(0.1)
    , currentEnd(1)
    , currentRate(0.1)
    , currentLive(0.1)
    , temperature(77)
    , pulsewidth(30)
    , nPulses(1)
    , interPulsesTime(0.0)
    , ratio(0.5)
    , supraName("")
    , fileName("")
    , magneticField(0)
    , coilAngle(0)
    , voltageCriterion(0.0)
{
}

QString MeasSeqJc::getSupraName() const
{
    return supraName;
}

void MeasSeqJc::setSupraName(const QString name)
{
    supraName = name;
}

double MeasSeqJc::getMagneticField() const
{
    return magneticField;
}

void MeasSeqJc::setMagneticField(double field)
{
    magneticField = field;
}

double MeasSeqJc::getCoilAngle() const
{
    return coilAngle;
}

void MeasSeqJc::setCoilAngle(double angle)
{
    coilAngle = angle;
}

QString MeasSeqJc::getFileName() const
{
    return fileName;
}

void MeasSeqJc::setFileName(const QString name)
{
    fileName = name;
}

int MeasSeqJc::getPulseMode() const {
    //qDebug() << "MeasSeqJc pulseMode is " << pMode;
    return pMode;
}
void MeasSeqJc::setPulseMode(int newMode) {
    //qDebug() << "MeasSeqJc pulseMode is now " << newMode;
    pMode = newMode;
}

double MeasSeqJc::getCurrentStart() const
{
    return currentStart;
}

void MeasSeqJc::setCurrentStart(double currentStartNew)
{
    currentStart = currentStartNew;
}

double MeasSeqJc::getCurrentEnd() const
{
    return currentEnd;
}

void MeasSeqJc::setCurrentEnd(double currentEndNew)
{
    currentEnd = currentEndNew;
}

double MeasSeqJc::getCurrentRate() const
{
    return currentRate;
}

void MeasSeqJc::setCurrentRate(double currentRateNew)
{
    currentRate = currentRateNew;
}


double MeasSeqJc::getCurrentLive() const
{
    return currentLive;
}

void MeasSeqJc::setCurrentLive(double currentLiveNew)
{
    currentLive = currentLiveNew;
}

double MeasSeqJc::getTemperature() const
{
    return temperature;
}

void MeasSeqJc::setTemperature(double temperatureNew)
{
    temperature = temperatureNew;
}

double MeasSeqJc::getPulsewidth() const
{
    return pulsewidth;
}

void MeasSeqJc::setPulsewidth(double pulsewidthNew)
{
    pulsewidth = pulsewidthNew;
}

double MeasSeqJc::getRatio() const
{
    return ratio;
}

double MeasSeqJc::getNumberPulses() const
{
    return nPulses;
}

void MeasSeqJc::setNumberPulses(double nPulsesNew)
{
    nPulses = nPulsesNew;
}

void MeasSeqJc::setRatio(double ratioNew)
{
    ratio = ratioNew;
}

double MeasSeqJc::getInterPulseTime() const {
    return interPulsesTime;
}

void MeasSeqJc::setInterPulseTime(double newTime) {
    interPulsesTime = newTime;
}

double MeasSeqJc::getVoltageCriterion() const {
    return voltageCriterion;
}

void MeasSeqJc::setVoltageCriterion(double newCrit) {
    voltageCriterion = newCrit;
}
