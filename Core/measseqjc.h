#ifndef MEASSEQJC_H
#define MEASSEQJC_H

#endif // MEASSEQJC_H

#include "Core_global.h"
#include <QString>

//Internal Classes
//#include "measurementsequence.h"
/*
Speichert Parameter einer Jc-Messung, also Start-/Enstromstärke, aktuelle Stromstärke Schrittweite,
Temperatur, Pulsweite und Anteil der Pulsweite, nach der gemessen werden soll.
*/

class CORE_EXPORT MeasSeqJc// : public MeasurementSequence
{
public:
    MeasSeqJc();

    double getCurrentStart() const;
    void setCurrentStart(double currentStartNew);

    double getCurrentEnd() const;
    void setCurrentEnd(double currentEndNew);

    double getCurrentRate() const;
    void setCurrentRate(double currentRateNew);

    double getCurrentLive() const;
    void setCurrentLive(double currentLiveNew);

    double getTemperature() const;
    void setTemperature(double temperatureNew);

    double getPulsewidth() const;
    void setPulsewidth(double temperatureNew);

    double getNumberPulses() const;
    void setNumberPulses(double nPulsesNew);

    double getInterPulseTime() const;
    void setInterPulseTime(double newTime);

    double getRatio() const;
    void setRatio(double temperatureNew);

    double getVoltageCriterion() const;
    void setVoltageCriterion(double newCrit);

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
    QString supraName;
    QString fileName;

    //PPMS
    double magneticField;
    double coilAngle;
    int pMode; //Ich mag keinen enum class, deshalb hier mit int:
               //1 = LinearOnce, 2 = LogOnce,
               //3 = LinearReversed, 4 = LogReversed
    double currentStart;
    double currentEnd;
    double currentRate;
    double currentLive;
    double temperature;
    double pulsewidth;
    double interPulsesTime;
    double voltageCriterion;
    int nPulses;
    double ratio;
};
