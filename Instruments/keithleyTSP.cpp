#include "keithleyTSP.h"
#include "keithleydatapoint.h"
#include<memory>
#include<iostream>
#include<QDebug>
#include<chrono>
#include<thread>

//const int GPIBADDRESS = 26;
const int DELAYGPIB = 2; //in ms
const bool TERMCHAR = false;

KeithleyTSP::KeithleyTSP(std::shared_ptr<GPIB> gpibNew, int addressNew) :
    gpib(gpibNew)
    , address(addressNew)
    , current(0.0)
    , voltage(0.0)
    , background(-1000.0)
    , isMeasuringBackground(false)
{
    std::cout << "Initialize constructor" << std::endl;
    qDebug() << "Finished constructor";
    gpib->openDevice(address);
    if(!gpib->isOpen(address)) {
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
    }
    gpib->cmd(address, "initializeSettings.run()", DELAYGPIB, TERMCHAR);
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

void KeithleyTSP::setPulseAndMeasure(double value, double pWidth, double ratio)
{
    //qDebug() << "TSP::setPulseAndMeasure";
    if (!gpib->isOpen(address))
    {
        return;
    }
    resetRange();
    pWidth = pWidth / 1000.0;
    //ratio = ratio / 1000.0;
    ratio = 100 / 1000.0;
    std::string valueString = " value = " + std::to_string(value);
    std::string pWidthString = " pWidth = " + std::to_string(pWidth);
    std::string ratioString = " ratio = " + std::to_string(ratio);
    gpib->cmd(address, valueString, DELAYGPIB, TERMCHAR);
    gpib->cmd(address, pWidthString, DELAYGPIB, TERMCHAR);
    gpib->cmd(address, ratioString, DELAYGPIB, TERMCHAR);
    gpib->cmd(address, "setPulseAndMeasure.run()", DELAYGPIB, TERMCHAR);
    current = std::stod(gpib->query(address, " print(node[2].smua.nvbuffer1.sourcevalues[1]) ", DELAYGPIB, TERMCHAR));
    voltage = std::stod(gpib->query(address, " print(node[1].defbuffer1.readings[1]) ", DELAYGPIB, TERMCHAR));
    gpib->cmd(address, " node[2].smua.nvbuffer1.clear() "
                       " node[1].defbuffer1.clear() ", DELAYGPIB, TERMCHAR);

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
    std::string valueString = " value = 0.000";
    std::string pWidthString = " pWidth = 30 / 1000.0";
    std::string ratioString = " ratio = 100.0/1000.0";
    gpib->cmd(address, valueString, DELAYGPIB, TERMCHAR);
    gpib->cmd(address, pWidthString, DELAYGPIB, TERMCHAR);
    gpib->cmd(address, ratioString, DELAYGPIB, TERMCHAR);
    gpib->cmd(address, "node[1].dmm.measure.autorange = node[1].dmm.ON", DELAYGPIB, TERMCHAR);
    double voltGes = 0;
    for (int i = 0; i < 10; i++)
    {
        gpib->cmd(address, "setPulseAndMeasure.run()", DELAYGPIB, TERMCHAR);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        voltGes += std::stod(gpib->query(address, " print(node[1].defbuffer1.readings[1]) ", DELAYGPIB, TERMCHAR));
        gpib->cmd(address, " node[1].defbuffer1.clear() ", DELAYGPIB, TERMCHAR);
    }
    background = voltGes / 10.0;
    //std::cout << background << std::endl;
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
