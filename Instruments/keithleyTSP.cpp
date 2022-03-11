#include "keithleyTSP.h"
#include "keithleydatapoint.h"
#include<memory>
#include<iostream>
#include<QDebug>

//const int GPIBADDRESS = 26;
const int DELAYGPIB = 2; //in ms
const bool TERMCHAR = false;

KeithleyTSP::KeithleyTSP(std::shared_ptr<GPIB> gpibNew, int addressNew) :
    gpib(gpibNew)
    , address(addressNew)
{
    std::cout << "Initialize constructor" << std::endl;
    qDebug() << "Finished constructor";
    gpib->openDevice(address);
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
    return dPoint;
}

bool KeithleyTSP::isOpen() {
    bool check = false;
    std::string s = gpib->query(address, "print(tsplink.state)", DELAYGPIB, TERMCHAR);
    if (s == "online")
    {
        check = true;
    }
    qDebug() << QString::fromStdString(s);
    return check;
}

void KeithleyTSP::setPulseAndMeasure(double value, double pWidth, double ratio)
{
    qDebug() << "TSP::setPulseAndMeasure";
    if (!gpib->isOpen(address))
    {
        return;
    }
    pWidth = pWidth / 1000.0;
    ratio = ratio / 1000.0;
    //qDebug() << "TSP::setPulseAndMeasure";
    //+std::to_string(value)+
    gpib->cmd(address,
        " node[2].smua.trigger.source.listi({"+std::to_string(value)+"}) ",
        DELAYGPIB, TERMCHAR);
    gpib->cmd(address, " node[2].trigger.timer[1].delay = " + std::to_string(pWidth) +
        " node[2].trigger.timer[2].delay = " + std::to_string(ratio) +
        " node[2].smua.source.output = node[2].smua.OUTPUT_ON "

        " node[1].trigger.model.initiate() "
        " node[2].smua.trigger.initiate() "

        " waitcomplete() "
        " node[2].smua.source.output = node[2].smua.OUTPUT_OFF ",
        DELAYGPIB, TERMCHAR);

    current = std::stod(gpib->query(address, " print(node[2].smua.nvbuffer1.sourcevalues[1]) ", DELAYGPIB, TERMCHAR));
    voltage = std::stod(gpib->query(address, " print(node[1].defbuffer1.readings[1]) ", DELAYGPIB, TERMCHAR));
    gpib->cmd(address,
        " node[2].smua.nvbuffer1.clear() "
        " node[1].defbuffer1.clear() ",
        DELAYGPIB, TERMCHAR);
}

double KeithleyTSP::getVoltage()
{
    return voltage;
}

double KeithleyTSP::getCurrent()
{
    return current;
}
