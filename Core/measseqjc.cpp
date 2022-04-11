#include "measseqjc.h"

MeasSeqJc::MeasSeqJc()
    : currentStart(0.1)
    , currentEnd(1)
    , currentRate(0.1)
    , currentLive(0.1)
    , temperature(77)
    , pulsewidth(30)
    , nPulses(1)
    , ratio(0.5)
{
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

MeasurementSequence::pulseMode MeasSeqJc::getPulseMode() const {
    return mode;
}
void MeasSeqJc::setPulseMode(MeasurementSequence::pulseMode newMode) {
    mode = newMode;
}

double MeasSeqJc::getInterPulseTime() const {
    return interPulsesTime;
}

void MeasSeqJc::setInterPulseTime(double newTime) {
    interPulsesTime = newTime;
}
