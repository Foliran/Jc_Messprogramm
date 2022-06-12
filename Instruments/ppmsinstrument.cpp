#include "ppmsinstrument.h"
#include <memory>
#include <QDebug>
#include <string>
#include <QPair>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <bitset>

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
const int BITUSERTEMP = 1 << 24; // userTemp

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
    if (gpib == nullptr) {
         return;
     }
     qDebug()<<"openDevice PPMS";
     gpib->openDevice(address);

     std::string idn = gpib->query(address, "*IDN?", DELAYGPIB, TERMCHAR);
     if(idn.find("QUANTUM DESIGN") == std::string::npos)
     {
         gpib->closeDevice(address);
     }

     if(!gpib->isOpen(address))
     {
         QString errormessage = "Ppms: ";
         if(gpib->getError().size() == 0)
         {
             errormessage.append("Not connected");
         }
         else
         {
             errormessage.append(gpib->getError().c_str());
         }
         emit newErrorPPMS(errormessage);
         return;
     }
     //Das sind die Befehle aus der config-Datei, damit wird die Usertemp ausgelesen
     gpib->cmd(address,"Movecfg 1,0.0532,380,0", DELAYGPIB, TERMCHAR);
     gpib->cmd(address,"Bridge 1,999.023,100.000,0,0,9.0", DELAYGPIB, TERMCHAR);
     gpib->cmd(address,"Mapdat 24,4", DELAYGPIB, TERMCHAR);
     gpib->cmd(address,"TABLE 24,2,2 #0 184.237323,329.914870,187.944359,325.926236,193.756136,319.945840,198.871712,314.949706,204.237836,309.944897,215.750975,299.938116,228.469814,289.923725,242.510928,279.927556,258.147056,269.915850,275.557339,259.907429,295.029808,249.913502,316.960000,239.913846,341.762188,229.916262,369.940989,219.904999,402.102290,209.911729,439.116746,199.913767,482.017712,189.908053,532.059995,179.905572,591.030580,169.903622,661.114077,159.900267,745.217941,149.901201,847.615928,139.898894,974.054259,129.889562,1.132436e3,119.892077,1.334877e3,109.898180,1.600540e3,99.885400,1.765063e3,94.889559,1.958027e3,89.883539,2.185378e3,84.885868,2.456192e3,79.891780,2.783141e3,74.893140,3.182881e3,69.894115,3.679142e3,64.890540,4.305527e3,59.894191,5.113189e3,54.897780,6.180767e3,49.900606,6.706893e3,47.901289,7.634942e3,44.897895,8.774801e3,41.898663,1.019644e4,38.900916,1.200350e4,35.901677,1.434699e4,32.909221,1.642350e4,30.819392,1.860255e4,29.021187,2.090551e4,27.436012,2.364599e4,25.867645,2.696415e4,24.301623,3.110375e4,22.718146,3.621599e4,21.153520,4.044446e4,20.096277,4.489671e4,19.151326,5.008322e4,18.215723", DELAYGPIB, TERMCHAR);
     gpib->cmd(address,"TblMode 24,1;", DELAYGPIB, TERMCHAR);
     gpib->cmd(address,"USERTEMP 24 1.8 1.7 2 1;", DELAYGPIB, TERMCHAR);

     dataMask += BITSTATUS; // Stat
     dataMask += BITTEMP; // Temp
     dataMask += BITMAG; // Mag
     dataMask += BITPRESSURE; // pressure
     dataMask += BITUSERTEMP; // userTemp

     if(rotState == true)
     {
         dataMask += BITANGLE; // Angle
     }

     QString magcnf;

     magcnf = (QString::fromStdString(gpib->query(address,"MAGCNF?", DELAYGPIB, TERMCHAR)));
     auto list = magcnf.split(',',QString::SkipEmptyParts);

     maxPosMagField = list[0].toDouble();
     maxRateMag = MAXFIELDRATEPPMS14;
}

void PpmsInstrument::setRotatorstate(bool rotator)
{
    //qDebug() << "SetRotatorState";
    rotState = rotator;
    if (rotator == true)
    {
        gpib->cmd(address, "Bridge 1,999.023,100.000,0,0,9.0", DELAYGPIB, TERMCHAR);
        gpib->cmd(address, "USERTEMP 23 1.9 1.8 2 1", DELAYGPIB, TERMCHAR);
        dataMask += BITANGLE; // Angle
        //dataMask += BITUSERTEMP; // userTemp

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
        //dataMask -= BITUSERTEMP; // userTemp
    }

    emit newRotstate(rotState);
}

bool PpmsInstrument::isOpen() const
{
    //qDebug() << "isOpen";
    return gpib->isOpen(address);
}

void PpmsInstrument::setTempSetpointCore(double setpoint, double rate)
{

    //qDebug() << "setTempSetpointCore";
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
    //qDebug() << "setAngleCore";
    if (!gpib->isOpen(address) || rotState == false)
    {
        return;
    }
    std::string angleStr = "MOVE " + std::to_string(angle);
    gpib->cmd(address, angleStr, DELAYGPIB, TERMCHAR);
}

QPair<double, double> PpmsInstrument::getTempSetpointCore()
{
    //qDebug() << "getTempSetpointCore";
    if (!gpib->isOpen(address))
    {
        return (QPair<double, double>(0, 0));
    }
    //HIER DIE ZWEITE VERSION; NACHDEM WIR JETZT JA USERTEMP UND NICHT MEHR TEMP AUSLESEN WOLLEN
    //QString string = gpib->query(address, "GETDAT? 16777216", DELAYGPIB, TERMCHAR).c_str();
    QString string = gpib->query(address, "TEMP?", DELAYGPIB, TERMCHAR).c_str();
    //QString besteht z.b aus (300,20.0)
    auto list = string.split(',', Qt::SkipEmptyParts);
    //nur die erste Zahl die herausgegebn wird ist für uns wichtig
    return (QPair<double, double>(list[0].toDouble(), list[1].toDouble()));
}

QPair<double, double> PpmsInstrument::getMagFieldCore()
{
    //qDebug() << "getMagFieldCore";
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
    //qDebug() << "getAngleCore";
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
    //qDebug() << "getHeliumCore";
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
    //qDebug() << "ppmsLogik";
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
    //std::bitset<32> x(std::stoi(dataMask));

    auto Datavector = getdat.split(',');
    //qDebug() << "Length of Datavector: " << Datavector.size();
    if (Datavector.size() < 5)
    {
        qDebug() << "Datavector.size is smaller than 5";
        return ppmsDpoint;
    }
    //std::bitset<32> y(Datavector[0].toInt());

    //qDebug() << "Datamask is " << QString::fromStdString(x.to_string());
    //qDebug() << "Returned data is " << getdat;

    //qDebug() << "Returned value 0 is " << QString::fromStdString(y.to_string());
    ppmsDpoint.setDatamask(Datavector[0].toInt());
    ppmsDpoint.setStatusPpms(Datavector[2].toStdString());
    ppmsDpoint.setTempLive(Datavector[6].toDouble());
    ppmsDpoint.setMagFieldLive(Datavector[4].toDouble() / OE_IN_MT);
    ppmsDpoint.setSamplePressure(Datavector[5].toDouble());

    if (ppmsDpoint.getDatamask() & BITUSERTEMP && rotState == true && Datavector.size() > 7)
    {
        //qDebug() << "Second if";
        ppmsDpoint.setRotLive(Datavector[5].toDouble());
        ppmsDpoint.setSamplePressure(Datavector[6].toDouble());
        ppmsDpoint.setUserTemp(Datavector[7].toDouble());
        ppmsDpoint.setTempLive(Datavector[7].toDouble());
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

void PpmsInstrument::shutdown() {
    gpib->cmd(address, " SHUTDOWN ", DELAYGPIB, TERMCHAR);
}
