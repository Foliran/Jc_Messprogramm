#ifndef DATAFILE_H
#define DATAFILE_H

#include <QVector>
#include <memory>
//Internal Classes
#include "Core_global.h"
#include "measurementsequence.h"
#include "measseqjc.h"
/*
Die Klasse ist wohl hauptsächlich dafür da, im Filereader genutzt zu werden. Glaube es speichert
halt ne komplett Messung, also I- und U-Werte
*/

class CORE_EXPORT Datafile
{
public:
    QVector<double> getVoltage();
    void setVoltage(QVector<double>& value);
    QVector<double> getCurrent();
    void setCurrent(QVector<double>& value);
    QString getInputText();
    void setInputText(QString& name);
    QString getFileName();
    void setFileName(QString& name);
private:
    QVector<double> voltage;
    QVector<double> current;
    QString inputText;
    QString filename;

    //attribute
    std::shared_ptr<MeasSeqJc>  MeasurementPointer;

};
#endif
