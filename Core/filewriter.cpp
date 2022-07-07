#include "filewriter.h"
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QDir>
#include "measurementsequence.h"
//#include "measseqtc.h"
#include "measseqjc.h"
#include "datapoint.h"
#include "QDateTime"

//fertig


FileWriter::FileWriter(QObject* parent)
    : QObject(parent)
{
}



QString FileWriter::createFileName(std::shared_ptr<const MeasSeqJc> measurementSequence)
{
    //auto seqTc = std::dynamic_pointer_cast<const MeasSeqTc> (measurementSequence);
    auto seqJc = std::dynamic_pointer_cast<const MeasSeqJc> (measurementSequence);
    if (seqJc != nullptr)
    {
        /*QString filename = "Jc_";
        filename.append(measurementSequence->getFileName());
        return filename;*/
        QString filename;
        filename.append(measurementSequence->getSupraName()+"_U(I)_");
        QString temp = QString::number(measurementSequence->getTemperature());
        if(temp.contains('.')) {
            temp.replace(".", ",");
            temp.append("K_");
        } else {
            temp.append(",0K_");
        }
        QString mag = QString::number(measurementSequence->getMagneticField());
        if(mag.contains('.')) {
            mag.replace(".", ",");
            mag.append("mT_");
        } else {
            mag.append(",0mT_");
        }
        filename.append(temp);
        filename.append(mag);
        filename.append("000,0Deg"); //Das hier kommt nur hinten dran, damit JcCalc die Dateien lesen kann, fuer das Programm muss der Dateinamen naemlich exakt das Format hier haben
        return filename;
    }
    else { return "No filename"; }
}

void FileWriter::append(std::shared_ptr<DataPoint> datapoint)
{
    if (!file->isOpen())
    {
        return;
    }
    if (measurementState == MeasurementsManager::State::ApproachEndJc)
    {
        /*file->write(QString::number(datapoint->getKeithleyData()->getCurrent()).toUtf8() +
            "     " + QString::number(datapoint->getKeithleyData()->getVoltage()).toUtf8() +
            "     " + QString::number(datapoint->getPpmsdata()->getTempLive()).toUtf8() + "\n");*/
        file->write(QString::number(datapoint->getPpmsdata()->getDatamask()).toUtf8() + "\t" +
                    QString::number(datapoint->getPpmsdata()->getTempLive()).toUtf8() + "\t" +
                    QString::number(datapoint->getPpmsdata()->getUserTemp()).toUtf8() + "\t" +
                    QString::number(datapoint->getPpmsdata()->getMagFieldLive()).toUtf8() + "\t" +
                    QString::number(datapoint->getPpmsdata()->getSamplePressure()).toUtf8() + "\t" +
                    QString::number(datapoint->getKeithleyData()->getCurrent()).toUtf8() + "\t" +
                    QString::number(datapoint->getKeithleyData()->getVoltage()).toUtf8() + "\t" +
                    QString::number(datapoint->getKeithleyData()->getVoltage() / datapoint->getKeithleyData()->getCurrent()).toUtf8() + "\t" +
                    QString::number(QDateTime::currentDateTime().toSecsSinceEpoch()).toUtf8() + "\n");
    }
}

QString FileWriter::openFile(std::shared_ptr<const MeasSeqJc> measurementSequence)
{
    QString path("Messergebnisse/");
    QDir dir;  // ich erstelle QString mit dem Ordner, danach die direction
    if (!dir.exists(path))
    { // Wenn nötig wird der Ordner erstellt
        dir.mkpath(path);
    }

    QString filepath = createFileName(measurementSequence);
    // der Filename und path wird gesezt, außerdem wird der name mit (i) verändert, wenn es die Txt datei schon  gibt
    QFile file2(path + filepath + ".txt");
    for (int i = 1; file2.exists(); i++)
    {
        if (file2.exists())
        {
            file2.setFileName(path + filepath + "_(" + QString::number(i) + ")" ".txt");
        }
    }

    file2.open(QIODevice::WriteOnly);
    file = std::make_shared<QFile>(file2.fileName());

    file->open(QIODevice::WriteOnly | QIODevice::Text);
    file->write("PPMS\tT\tT\tB\tP\tI\tU\tTimestamp\n-\tK\tK\tmT\tPa\tA\tV\tOhm\ts\nPPMS\tRod\tSample\t-\tchamber\tMean\tMean\tMean\t-\n");

    if (!file->isOpen())
    {
        return QString();
    }
    if (!file->isWritable())
    {
        return QString();
    }
    return file->fileName();
}

void FileWriter::closeFile()
{
    file->close();
}

void FileWriter::MeasurementState(MeasurementsManager::State newState)
{
    measurementState = newState;
}
