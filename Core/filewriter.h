#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "Core_global.h"

#include <QString>
#include <memory>
#include <QFile>
#include <QObject>

//fertig

//Internal Classes
class MeasSeqJc;
//class MeasurementSequence;
class FileWriter;
class DataPoint;
#include "../ControlCore/measurementsmanager.h"

class CORE_EXPORT FileWriter : QObject
{
    Q_OBJECT

public slots:
    void append(std::shared_ptr<DataPoint> datapoint);

public:
    FileWriter(QObject* parent = 0);
    QString openFile(std::shared_ptr<const MeasSeqJc> measurementSequence);
    void closeFile();
    void MeasurementState(MeasurementsManager::State newState);


private:
    QString createFileName(std::shared_ptr<const MeasSeqJc> measurementSequence);
    QString filedir;
    MeasurementsManager::State measurementState;
    std::shared_ptr<QFile> file;
};

#endif
