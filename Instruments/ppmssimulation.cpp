#include "ppmssimulation.h"
#include <memory>
#include <QDebug>

//Internal Classes
#include "../ControlCore/instrumentmanager.h"
#include "../Instruments/ppmsdatapoint.h"

PpmsSimulation::PpmsSimulation()
     :
       tempSetpoint_(300)
     , tempRate_(10)
     , fieldSetpoint_(0)
     , fieldRate_(10)
     , tempNow_(300)
     , magFieldSP_(0)
     , magRate_(0)
     , magFieldNow_(0)
     , angle_(0)
{
    maxPosMagField = 9000;
    maxRateMag = 100;
    ppmsHelium = 60;
}

void PpmsSimulation::openDevice()
{

}

void PpmsSimulation::setRotatorstate(bool rot)
{
    if(rot == true)
    {
        qDebug()<<"true";
    }
    else
    {
        qDebug()<<"false";
    }
}

bool PpmsSimulation::isOpen() const
{
    return true;
}
void PpmsSimulation::setTempSetpointCore(double setpoint, double rate)
{
    tempSetpoint_ = setpoint;
    tempRate_ = rate;

}

void PpmsSimulation::setMagFieldCore(double magField, double magRate)
{
    magFieldSP_ = magField;
    magRate_ = magRate;

}

void PpmsSimulation::setAngleCore(double angle)
{
    angle_ = angle;
}

QPair<double, double> PpmsSimulation::getTempSetpointCore()
{
    return QPair(tempSetpoint_, tempRate_);
}

QPair<double, double> PpmsSimulation::getMagFieldCore()
{
    if(magFieldSP_>9000)
    {
        emit newErrorPPMS("Magnetfeld zu hoch");
    }
    return QPair(magFieldSP_, magRate_);
}

double PpmsSimulation::getAngleCore()
{
    return angle_;
}

double PpmsSimulation::getHeliumCore()
{
    return ppmsHelium;
}

PpmsDataPoint PpmsSimulation::ppmsLogik()
{
    PpmsDataPoint ppmsDpoint;
    if(std::abs(tempSetpoint_ - tempNow_) < tempRate_ && tempRate_ > 0.1)
    {
        tempRate_ = 0.1*tempRate_;
    }
    if (tempNow_ < tempSetpoint_)
    {
        tempNow_ = tempNow_ + tempRate_;
    }
    if (tempNow_ > tempSetpoint_)
    {
        tempNow_ = tempNow_ - tempRate_;
    }
    if(std::abs(magFieldSP_ - magFieldNow_) < magRate_ && magRate_ > 0.1)
    {
        magRate_ = 0.1*magRate_;
    }

    if (magFieldNow_ < magFieldSP_)
    {
        magFieldNow_ = magFieldNow_ + magRate_;
    }
    if (magFieldNow_ > magFieldSP_)
    {
        magFieldNow_ = magFieldNow_ - magRate_;
    }

    ppmsDpoint.setTempLive(tempNow_);
    ppmsDpoint.setMagFieldLive(magFieldNow_);
    ppmsDpoint.setRotLive(angle_);
    ppmsDpoint.setSamplePressure(1);
    ppmsDpoint.setStatusPpms("4369");
    ppmsDpoint.setUserTemp(300);

    return ppmsDpoint;
}

void PpmsSimulation::shutdown() {

}


