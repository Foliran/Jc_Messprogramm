#include <QVector>
#include "datafile.h"

QVector<double> Datafile::getVoltage()
{
    return voltage;
}

void Datafile::setVoltage(QVector<double>& value)
{
    voltage = value;
}

QVector<double> Datafile::getCurrent()
{
    return current;
}

void Datafile::setCurrent(QVector<double>& value)
{
    voltage = value;
}


QString Datafile::getInputText()
{
    return inputText;
}
void Datafile::setInputText(QString& name)
{
    inputText = name;
}

QString Datafile::getFileName()
{
    return filename;
}
void Datafile::setFileName(QString& name)
{
    filename = name;
}
