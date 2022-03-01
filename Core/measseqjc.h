#ifndef MEASSEQJC_H
#define MEASSEQJC_H

#endif // MEASSEQJC_H

#include "Core_global.h"

//Internal Classes
#include "measurementsequence.h"
/*
Speichert Parameter einer Jc-Messung, also Start-/Enstromstärke, aktuelle Stromstärke Schrittweite,
Temperatur, Pulsweite und Anteil der Pulsweite, nach der gemessen werden soll.

Eigentlich ist die Klassse nicht mehr unbedingt nötig, die war im Induktionsmessprogramm
sinnvoll um zwischen Tc- und Jc-Messung zu unterscheiden. Da ese jetzt nur noch
die Jc-Messung gibt, würde meassurementsequence ausreichen. Das darf dann aber jemand
anders machen. Viel Spaß, zukünftiger jemand!
*/

class CORE_EXPORT MeasSeqJc : public MeasurementSequence
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

    double getRatio() const;
    void setRatio(double temperatureNew);

protected:
    double currentStart;
    double currentEnd;
    double currentRate;
    double currentLive;
    double temperature;
    double pulsewidth;
    double ratio;
};
