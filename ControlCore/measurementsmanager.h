#ifndef INDUMANAGER_H
#define INDUMANAGER_H

#include "ControlCore_global.h"
#include <memory>
#include <QObject>
#include <vector>

//Internal Classes
//class MeasSeqTc;
class MeasSeqJc;
class MeasurementSequence;
class DataPoint;
class FileWriter;
class InstrumentManager;

//fertig

class CONTROLCORE_EXPORT MeasurementsManager : public QObject
{
    Q_OBJECT

public:
    explicit MeasurementsManager();
    ~MeasurementsManager();
    void openDevice();
    enum class State { Idle, CheckForMeas, ApproachStartJc, ApproachEndJc };//, ApproachStartTc, ApproachEndTc
    void appendMeasurement(std::vector<std::shared_ptr<const MeasurementSequence>> mVecSeq);
    void startMeasurement(std::shared_ptr<const MeasurementSequence> measurementSequence);
    void rotatorState(bool rotator);

signals:
    void newData(std::shared_ptr<const DataPoint>);
    void startNewMeasurement(std::shared_ptr<const MeasurementSequence>);
    void newState(MeasurementsManager::State newState);
    void newTempSP(double setpoint, double rate);
    void newCurrentValues(double current, double voltage);
    void newMagSP(double magField, double magRate);
    void newAngleSP(double angle);
    void newRotstate(bool rotActive);
    void newErrorMessage(QString errormessagePpms);

private slots:
    void onNewData(std::shared_ptr<DataPoint> datapoint);
    void onNewCurrentValues(double current, double voltage);
    void onNewTempSP(double setpoint, double rate);
    void onNewMagSP(double magField, double magRate);
    void onNewAngleSP(double angle);
    void onNewRotstate(bool rotActive);
    void onNewErrorMessage(QString errormessagePpms);



private:
    size_t measurementNumber;
    std::vector<std::shared_ptr<const MeasurementSequence>> mVecSeq;
    std::unique_ptr <InstrumentManager> instrumentmanager;
    std::unique_ptr <FileWriter> fw;
    std::shared_ptr <MeasSeqJc> mSeqJc;
    State measurementState;
    double magFieldSP;
    double angleSP;
    double tempSP;

};

#endif
