#include "filewriter.h"
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QDir>
#include "measurementsequence.h"
//#include "measseqtc.h"
#include "measseqjc.h"
#include "datapoint.h"

//fertig


FileWriter::FileWriter(QObject* parent)
    : QObject(parent)
{
}

QString FileWriter::writeHeader(std::shared_ptr<const MeasurementSequence> measurementSequence)
{
    //auto seqTc = std::dynamic_pointer_cast<const MeasSeqTc> (measurementSequence);
    auto seqJc = std::dynamic_pointer_cast<const MeasSeqJc> (measurementSequence);
    if (seqJc != nullptr)
    {
        QString header;
        header.append("Material: ");
        header.append(measurementSequence->getSupraName());
        header.append("\n Temperature: ");
        header.append(QString::number(seqJc->getTemperature()));
        //header.append(" T \n Frequency: ");
        //header.append(QString::number(measurementSequence->frequency()));
        header.append("\n Magnetic Field: ");
        header.append(QString::number(measurementSequence->getMagneticField()));
        header.append(" mT \n Starting Current: ");
        header.append(QString::number(seqJc->getCurrentStart()));
        header.append(" A \n Ending Current: ");
        header.append(QString::number(seqJc->getCurrentEnd()));
        header.append(" A \n Current Rate: ");
        header.append(QString::number(seqJc->getCurrentRate()));
        header.append(" A/s");
        header.append("\n CoilAngle: ");
        header.append(QString::number(measurementSequence->getCoilAngle()));
        header.append(" degrees \n");
        return header;
    }
    else { return "unable to write header"; }
}

QString FileWriter::createFileName(std::shared_ptr<const MeasurementSequence> measurementSequence)
{
    //auto seqTc = std::dynamic_pointer_cast<const MeasSeqTc> (measurementSequence);
    auto seqJc = std::dynamic_pointer_cast<const MeasSeqJc> (measurementSequence);
    if (seqJc != nullptr)
    {
        QString filename = "Jc_";
        filename.append(measurementSequence->getFileName());
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
        file->write(QString::number(datapoint->getKeithleyData()->getCurrent()).toUtf8() +
            " " + QString::number(datapoint->getKeithleyData()->getVoltage()).toUtf8() + "\n");
    }
}

QString FileWriter::openFile(std::shared_ptr<const MeasurementSequence> measurementSequence)
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

    if (!file->isOpen())
    {
        return QString();
    }
    if (file->isWritable())
    {
        file->write(writeHeader(measurementSequence).toUtf8());
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
