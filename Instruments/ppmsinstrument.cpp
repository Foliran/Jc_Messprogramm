#include "ppmsinstrument.h"
#include <memory>
#include <QDebug>
#include <string>
#include <QPair>
#include <sstream>
#include <iomanip>
#include <algorithm>

//Internal Classes
#include "../Core/datapoint.h"
//#include "../Control/instrumentmanager.h"
#include "ppmsdatapoint.h"
//#include "../Device_Control/lockindatapoint.h"

// Ich will ja nur das PPMS14 bedienen, daher werden die Sachen des PPMS 9 auskommentiert
//const double MAXFIELDPPMS9 = 90000; //in Oe
//const double MAXFIELDRATEPPMS9 = 190; //in Oe
const double MAXFIELDRATEPPMS14 = 120; //in Oe
const int DELAYGPIB = 100; //in ms
const bool TERMCHAR = false;

const int OE_IN_MT = 10;

const int BITSTATUS = 1 << 0; // Stat
const int BITTEMP = 1 << 1; // Temp
const int BITMAG = 1 << 2; // Mag
const int BITANGLE = 1 << 3; // Angle
const int BITPRESSURE = 1 << 19; // pressure
const int BITUSERTEMP = 1 << 23; // userTemp

PpmsInstrument::PpmsInstrument(std::shared_ptr<GPIB> gpibNew, int addressNew)
    : gpib(gpibNew)
    , address(addressNew)
    , rotState(false)
    , dataMask(0)
{
    sstring.imbue(std::locale::classic());
    sstring << std::fixed;
}

void PpmsInstrument::openDevice()
{
    if (gpib == nullptr)
    {
        return;
    }
    qDebug() << "openDevice PPMS";
    gpib->openDevice(address);

    gpib->query(address, "", DELAYGPIB, TERMCHAR);

    std::string idn = gpib->query(address, "*IDN?", DELAYGPIB, TERMCHAR);
    if (idn.find("QUANTUM DESIGN") == std::string::npos)
    {
        gpib->closeDevice(address);
    }

    if (!gpib->isOpen(address))
    {
        QString errormessage = "Ppms: ";
        if (gpib->getError().size() == 0)
        {
            errormessage.append("Not connected");
        }
        else
        {
            errormessage.append(gpib->getError().c_str());
        }
        emit newErrorPPMS(errormessage);
        return;
    } else {
        qDebug() << "PPMS Connection is open";
    }

    dataMask += BITSTATUS; // Stat
    dataMask += BITTEMP; // Temp
    dataMask += BITMAG; // Mag
    dataMask += BITPRESSURE; // pressure

    /*if(rotState_ == true)
    {
        dataMask_ += BITANGLE; // Angle
        dataMask_ += BITUSERTEMP; // userTemp
    }*/

    QString magcnf;

    magcnf = (QString::fromStdString(gpib->query(address, "MAGCNF?", DELAYGPIB, TERMCHAR)));
    auto list = magcnf.split(',', Qt::SkipEmptyParts);

    maxPosMagField = list[0].toDouble();
    maxRateMag = MAXFIELDRATEPPMS14;
    //maxRateMag = (maxPosMagField_ > MAXFIELDPPMS9) ? MAXFIELDRATEPPMS14 : MAXFIELDRATEPPMS9;
}

void PpmsInstrument::setRotatorstate(bool rotator)
{
    rotState = rotator;
    if (rotator == true)
    {
        gpib->cmd(address, "Bridge 1,999.023,100.000,0,0,9.0", DELAYGPIB, TERMCHAR);
        gpib->cmd(address, "USERTEMP 23 1.9 1.8 2 1", DELAYGPIB, TERMCHAR);
        dataMask += BITANGLE; // Angle
        dataMask += BITUSERTEMP; // userTemp

        qDebug() << gpib->query(address, "", DELAYGPIB, TERMCHAR).c_str();

        //qDebug()<<dataMask_;
        rotState = ppmsLogik().getDatamask() & BITUSERTEMP;
        if (rotState != rotator)
        {
            emit newErrorPPMS("Rotator not mounted");
        }
    }
    else
    {
        //TODO: Rotator Voltage aus?
        //gpib_->cmd(address_ ,"Bridge 0,999.023,100.000,0,0,9.0", DELAYGPIB, TERMCHAR);
        gpib->cmd(address, "USERTEMP 0", DELAYGPIB, TERMCHAR);
        dataMask -= BITANGLE; // Angle
        dataMask -= BITUSERTEMP; // userTemp
        //qDebug()<<dataMask_;
    }

    emit newRotstate(rotState);
}

bool PpmsInstrument::isOpen() const
{
    return gpib->isOpen(address);
}

void PpmsInstrument::setTempSetpointCore(double setpoint, double rate)
{
    if (!gpib->isOpen(address))
    {
        return;
    }
    std::string setTempSetpointStr = "TEMP " + dtoStr(setpoint, 3) + " " + dtoStr(rate, 3) + " 0";
    gpib->cmd(address, setTempSetpointStr, DELAYGPIB, TERMCHAR);
}

void PpmsInstrument::setMagFieldCore(double magField, double magRate)
{
    if (!gpib->isOpen(address))
    {
        return;
    }
    std::string setMagFieldStr = "FIELD " + dtoStr(magField, 0) + " " + dtoStr(magRate, 0);
    gpib->cmd(address, setMagFieldStr, DELAYGPIB, TERMCHAR);
}

void PpmsInstrument::setAngleCore(double angle)
{
    if (!gpib->isOpen(address) || rotState == false)
    {
        return;
    }
    std::string angleStr = "MOVE " + std::to_string(angle);
    gpib->cmd(address, angleStr, DELAYGPIB, TERMCHAR);
}

QPair<double, double> PpmsInstrument::getTempSetpointCore()
{
    if (!gpib->isOpen(address))
    {
        return (QPair<double, double>(0, 0));
    }

    QString string = gpib->query(address, "TEMP?", DELAYGPIB, TERMCHAR).c_str();
    //QString besteht z.b aus (300,20.0)
    auto list = string.split(',', Qt::SkipEmptyParts);
    //nur die erste Zahl die herausgegebn wird ist für uns wichtig
    return (QPair<double, double>(list[0].toDouble(), list[1].toDouble()));
}

QPair<double, double> PpmsInstrument::getMagFieldCore()
{
    if (!gpib->isOpen(address))
    {

        return QPair<double, double>(0, 0);
    }
    QString string = gpib->query(address, "FIELD?", DELAYGPIB, TERMCHAR).c_str();
    //QString = String den uns Ppms gibt
    auto list = string.split(',', Qt::SkipEmptyParts);
    //nur die erste Zahl die herausgegebn wird ist für uns wichtig
    return QPair<double, double>(list[0].toDouble() / OE_IN_MT, list[1].toDouble() / OE_IN_MT); // inklusive Umrechnung in Oe
}

double PpmsInstrument::getAngleCore()
{
    if (!gpib->isOpen(address) || rotState == false)
    {
        return 0;
    }
    QString string = gpib->query(address, "MOVE?", DELAYGPIB, TERMCHAR).c_str();
    //QString = String den uns Ppms gibt
    auto list = string.split(',', Qt::SkipEmptyParts);
    //nur die erste Zahl die herausgegebn wird ist für uns wichtig
    return list[0].toDouble();
}

double PpmsInstrument::getHeliumCore()
{
    if (!gpib->isOpen(address))
    {
        return 0;
    }
    QString string = gpib->query(address, "LEVEL?", DELAYGPIB, TERMCHAR).c_str();
    //QString = String den uns Ppms gibt
    auto list = string.split(',', Qt::SkipEmptyParts);
    //nur die erste Zahl die herausgegebn wird ist für uns wichtig
    ppmsHelium = list[0].toDouble();
    return ppmsHelium;
}

PpmsDataPoint PpmsInstrument::ppmsLogik()
{
    if (!gpib->isOpen(address))
    {
        return PpmsDataPoint();
    }
    PpmsDataPoint ppmsDpoint;
    //ACHTUNG: Hier wurde früher einfach der int32_t in QString::number(dataMask).toStdString
    //gesteckt. Scheinbar geht das aber mit diesem Datentyp nicht mehr, also hab ich das erst in nen int
    //und dann direkt in einen string umgewandelt. Hoffe das funktioniert
    int intDataMask = dataMask;
    std::string dataMask = std::to_string(intDataMask);
    std::string getDatStr = "GETDAT? " + dataMask + " 0";
    QString getdat = (gpib->query(address, getDatStr, DELAYGPIB, TERMCHAR).c_str());

    auto Datavector = getdat.split(',');
    if (Datavector.size() < 5)
    {
        return ppmsDpoint;
    }
    ppmsDpoint.setDatamask(Datavector[0].toInt());
    ppmsDpoint.setStatusPpms(Datavector[2].toStdString());
    ppmsDpoint.setTempLive(Datavector[3].toDouble());
    ppmsDpoint.setMagFieldLive(Datavector[4].toDouble() / OE_IN_MT);
    ppmsDpoint.setSamplePressure(Datavector[5].toDouble());

    if (ppmsDpoint.getDatamask() & BITUSERTEMP && rotState == true && Datavector.size() > 7)
    {
        ppmsDpoint.setRotLive(Datavector[5].toDouble());
        ppmsDpoint.setSamplePressure(Datavector[6].toDouble());
        ppmsDpoint.setUserTemp(Datavector[7].toDouble());
    }

    ppmsDpoint.setChamberLevel(getHeliumCore());

    return ppmsDpoint;
}

std::string PpmsInstrument::dtoStr(double number, int dec)
{
    sstring.str(std::string());
    sstring << std::setprecision(dec) << number;
    return sstring.str();
}









