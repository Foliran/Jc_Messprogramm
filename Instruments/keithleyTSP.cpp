#include "keithleyTSP.h"
#include "keithleydatapoint.h"
#include<memory>
#include<iostream>
#include<QDebug>
#include<thread>
#include<cstdlib>
#include<iomanip>
#include<thread>
#include<chrono>
#include<QTime>

//const int GPIBADDRESS = 26;
const int DELAYGPIB = 0; //in ms
const bool TERMCHAR = false;

KeithleyTSP::KeithleyTSP(std::shared_ptr<GPIB> gpibNew, int addressNew) :
    gpib(gpibNew)
    , address(addressNew)
    , current(0.0)
    , voltage(0.0)
    , background(-1000.0)
{
    busy = false;
    busyBackground = false;
    gpib->openDevice(address);
    if(!gpib->isOpen(address)) {
        QString errormessage = "TSP-Link: ";
        if (gpib->getError().size() == 0)
        {
            errormessage.append("Not connected");
        }
        else
        {
            errormessage.append(gpib->getError().c_str());
        }
        emit newKeithleyError(errormessage);
    }
    else {
        qDebug() << "Keithley Connection is open";
    }
    gpib->cmd(address, "tsplink.reset(2)", DELAYGPIB, TERMCHAR);
}

void KeithleyTSP::openDevice()
{

}

KeithleyDatapoint KeithleyTSP::keithleyLogik()
{
    if(!gpib->isOpen(address))
    {
        return KeithleyDatapoint();
    }
    KeithleyDatapoint dPoint;
    dPoint.setCurrent(getCurrent());
    dPoint.setVoltage(getVoltage());
    dPoint.setBackground(background);
    return dPoint;
}

bool KeithleyTSP::isOpen() {
    bool check = false;
    std::string s = gpib->query(address, "print(tsplink.state)", DELAYGPIB, TERMCHAR);
    if (s == "online")
    {

        check = true;
    }
    return check;
}

void KeithleyTSP::initializeSettings(double pWidth, double ratio, int nPulses, double timeBetwPuls, bool reversed) {
    if (!gpib->isOpen(address))
    {
        return;
    }
    //reversed = true -> es wird in beide Richtungen gemessesn und die Absolutwerte gemittelt; false -> es wird nur in positive Richtung gemessen
    if(reversed) numberPulses = 2 * nPulses;
    else numberPulses = nPulses;
    pulseReversed = reversed;
    //resetRange();
    pulseWidth = pWidth / 1000.0;
    ratio = ratio / 1000.0;
    interPulseTime = timeBetwPuls / 1000.0;
    std::string pWidthString = " pWidth = " + std::to_string(pulseWidth) + " ";
    std::string ratioString = " measDelay = " + std::to_string(ratio) + " ";
    std::string nPulsesString = " nPulses = " + std::to_string(numberPulses) + " ";
    std::string interPulsTimeString = " interPulseTime = " + std::to_string(interPulseTime) + " ";
    //qDebug() << QString::fromStdString(interPulsTimeString + ", " + ratioString + ", " + nPulsesString);
    gpib->cmd(address, " reset() ", DELAYGPIB, TERMCHAR);
    gpib->cmd(address, " errorqueue.clear() " +
                       pWidthString + ratioString + nPulsesString + interPulsTimeString + " init.run() ", DELAYGPIB, TERMCHAR);
}

void KeithleyTSP::setPulseAndMeasure(double value)
{
    current = value;
    if (!gpib->isOpen(address))
    {
        return;
    }
    gpib->cmd(address, "res = 0", DELAYGPIB, TERMCHAR);

    int sleeptime = (int)((numberPulses + 1) * (pulseWidth + interPulseTime) * 1000);
    std::string valueString;
    if(pulseReversed) {
        valueString = " node[2].smua.trigger.source.listi({" + std::to_string(current) + ", " + std::to_string(-current) + "})";
    } else {
        valueString = " node[2].smua.trigger.source.listi({" + std::to_string(current) + "})";
    }
    gpib->cmd(address, valueString, DELAYGPIB, TERMCHAR);
    gpib->cmd(address, " node[1].trigger.model.initiate() "
    " node[2].smua.trigger.initiate() "
    " waitcomplete() "
    " res = 0 "
    " for i = 1, nPulses do res = res + math.abs(node[1].defbuffer1.readings[i]) end "
    " waitcomplete(2) "
    " volt = res / nPulses "
    " node[2].smua.nvbuffer1.clear() "
    " node[1].defbuffer1.clear() ", sleeptime, TERMCHAR);
    voltage = std::atof(gpib->query(address, " print(volt) ", DELAYGPIB, TERMCHAR).c_str());
    //current = std::atof(gpib->query(address, " print(node[2].smua.nvbuffer1.sourcevalues[1]) ", DELAYGPIB, TERMCHAR).c_str());
    qDebug() << voltage;
}

double KeithleyTSP::getVoltage()
{
    return voltage;
}

double KeithleyTSP::getCurrent()
{
    return current;
}

double KeithleyTSP::getBackground()
{
    background = -500.0;
    busyBackground = true;
    double count = 0;

    for (int i = 0; i < 10; i++) {
        setPulseAndMeasure(0.001);
        count += voltage;
    }
    busyBackground = false;
    background = count / (numberPulses * 10);
    return background;
}

void KeithleyTSP::resetRange() {
    gpib->cmd(address, " rangeDMM = node[1].dmm.measure.range ", DELAYGPIB, TERMCHAR);
    double rangeDMM = std::stod(gpib->query(address, " print(rangeDMM)", DELAYGPIB, TERMCHAR));
    //qDebug() << "Range DMM" << range;
    if (voltage >= (0.8 * rangeDMM)) {
        std::string newRangeDMM = "node[1].dmm.measure.range  = " + std::to_string(10 * rangeDMM);
        //qDebug() << "New range for DMM:" << QString::fromStdString(newRangeDMM);
        gpib->cmd(address, newRangeDMM, DELAYGPIB, TERMCHAR);
    }
    gpib->cmd(address, " rangeSMU = node[2].smua.source.rangei ", DELAYGPIB, TERMCHAR);
    double rangeSMU = std::stod(gpib->query(address, " print(rangeSMU)", DELAYGPIB, TERMCHAR));
    //qDebug() << "Range SMU" << rangeSMU;
    if (current >= (0.8 * rangeSMU)) {
        std::string newRangeSMU = "node[2].smua.source.rangei = " + std::to_string(10 * rangeSMU);
        //qDebug() << "New range for SMU:" << QString::fromStdString(newRangeSMU);
        gpib->cmd(address, newRangeSMU, DELAYGPIB, TERMCHAR);
    }
}

void KeithleyTSP::resetBackground() {
    background = -1000.0;
}

void KeithleyTSP::checkForError() {
    gpib->cmd(address, "countErrors = errorqueue.count", DELAYGPIB, TERMCHAR);
    int nErrors = std::stoi(gpib->query(address, "print(countErrors)", DELAYGPIB, TERMCHAR));
    if (nErrors > 0) {
        for(int i = 0; i < nErrors; i++) {
            gpib->cmd(address, "errorCode, message, severity, errorNode = errorqueue.next()", DELAYGPIB, TERMCHAR);
            std::string errorCode = gpib->query(address, "print(errorCode)", DELAYGPIB, TERMCHAR);
            std::string message = gpib->query(address, "print(message)", DELAYGPIB, TERMCHAR);
            std::string errorNode = gpib->query(address, "print(errorNode)", DELAYGPIB, TERMCHAR);
            std::string completeErrorMessage = "Error " + errorCode + " on Node " + errorNode + ": " + message;
            emit newKeithleyError(QString::fromStdString(completeErrorMessage));
        }
    }
    gpib->cmd(address, "errorqueue.clear()", DELAYGPIB, TERMCHAR);
}

void KeithleyTSP::setOutputOff() {
    gpib->cmd(address, "node[2].smua.source.output = node[2].smua.OUTPUT_OFF", DELAYGPIB, TERMCHAR);
}
