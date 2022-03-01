#include "filereader.h"
#include <QVector>
#include <QTextStream>
#include "datafile.h"
#include <QtDebug>


//fertig
FileReader::FileReader(Datafile& file)
    : dfile(file)                             // wir setzen hier dfile_=dfile; von typ datenfile
{
}

std::shared_ptr<Datafile> FileReader::readFile()
{

    std::shared_ptr<Datafile> datafile = std::make_shared<Datafile>();
    QVector<double> CurrentVectordouble;
    QVector<double> VoltageVectordouble;

    QString text = dfile.getInputText();
    // rufe getinput auf, aus der file dfile_
    // ich erstelle eine Regular Expression die den String in 2 Listen aufteilt: vor und nach dem bestimmten Punkt:
    QRegExp rx("A\\s*V\\s*\n*Current\\s*Voltage"); // alt: "K\\s*V\\s*Deg\\s*\n*Temperature\\s*Voltage\\s*Phase"
    // ich teile die Text datei in 2 teile:
    QStringList RegExpAufteilungListe = text.split(rx);
    //Ich splitte den 2ten Teil der nurnoch nummern enthält auf in die einzelnen Zahlen und schreibe diese in eine Liste
    QStringList DateiListe1 = RegExpAufteilungListe[1].split('\t', Qt::SkipEmptyParts);
    // die Liste wird Wort für Wort eingepflegt
    for (int i = 0; i < DateiListe1.length(); i++)
    {
        // es wird einem Vektor von typ string nach und nach die Temp oder Volt hinzugefügt
        if (i % 3 == 0)
        {
            CurrentVectordouble.append(DateiListe1[i].toDouble());
        }
        if (i % 3 == 1)
        {
            VoltageVectordouble.append(DateiListe1[i].toDouble());
        }
    }

    datafile->setVoltage(VoltageVectordouble);
    datafile->setCurrent(CurrentVectordouble);

    return datafile;
}
