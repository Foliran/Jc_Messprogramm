#include "datapoint.h"
#include <memory>
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/keithleydatapoint.h"

//fertig

DataPoint::DataPoint()
    : ppmsdata(std::make_shared<const PpmsDataPoint>())
    , keithleyData(std::make_shared<const KeithleyDatapoint>())
{

}

std::shared_ptr<const PpmsDataPoint> DataPoint::getPpmsdata() const
{
    return ppmsdata;
}

void DataPoint::setPpmsData(const std::shared_ptr<const PpmsDataPoint>& value)
{
    ppmsdata = value;
}

std::shared_ptr<const KeithleyDatapoint> DataPoint::getKeithleyData() const
{
    return keithleyData;
}

void DataPoint::setKeithleyData(const std::shared_ptr<const KeithleyDatapoint>& value)
{
    keithleyData = value;
}
