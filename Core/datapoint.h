#ifndef DATAPOINT_H
#define DATAPOINT_H

//fertig

#include "Core_global.h"
#include <chrono>
#include <memory>
//Internal Classes
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/keithleydatapoint.h"

class CORE_EXPORT DataPoint
{

public:
    DataPoint();

    std::shared_ptr<const PpmsDataPoint> getPpmsdata() const;
    void setPpmsData(const std::shared_ptr<const PpmsDataPoint>& ppmsdata);

    std::shared_ptr<const KeithleyDatapoint> getKeithleyData() const;
    void setKeithleyData(const std::shared_ptr<const KeithleyDatapoint>& value);

private:
    std::shared_ptr<const PpmsDataPoint> ppmsdata;
    std::shared_ptr<const KeithleyDatapoint> keithleyData;
};

#endif
