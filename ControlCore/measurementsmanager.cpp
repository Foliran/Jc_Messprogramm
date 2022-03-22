#include "measurementsmanager.h"
#include <QDebug>
#include <vector>

//Internal Classes
#include "instrumentmanager.h"
#include "../Core/measurementsequence.h"
#include "../Core/measseqjc.h"
#include "../Core/datapoint.h"
#include "../Core/filewriter.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Core/datapoint.h"
#include <QThread>
#include <memory>


MeasurementsManager::MeasurementsManager()
    : measurementNumber(0)
    , instrumentmanager(std::make_unique<InstrumentManager>())
    , fw(nullptr)
    , mSeqJc(std::make_shared<MeasSeqJc>())
    , measurementState(State::Idle)
    , magFieldSP(0)
    , angleSP(0)
    , tempSP(0)

{
    connect(instrumentmanager.get(), &InstrumentManager::newData,
        this, &MeasurementsManager::onNewData);
    connect(instrumentmanager.get(), &InstrumentManager::newTempSP,
        this, &MeasurementsManager::onNewTempSP);
    connect(instrumentmanager.get(), &InstrumentManager::newMagSP,
        this, &MeasurementsManager::onNewMagSP);
    connect(instrumentmanager.get(), &InstrumentManager::newAngleSP,
        this, &MeasurementsManager::onNewAngleSP);
    connect(instrumentmanager.get(), &InstrumentManager::newRotstate,
        this, &MeasurementsManager::onNewRotstate);
    connect(instrumentmanager.get(), &InstrumentManager::newErrorMessage,
        this, &MeasurementsManager::onNewErrorMessage);
    connect(instrumentmanager.get(), &InstrumentManager::newValues,
        this, &MeasurementsManager::onNewCurrentValues);
}

MeasurementsManager::~MeasurementsManager()
{

}

void MeasurementsManager::openDevice()
{
    instrumentmanager->openDevice();
}


void MeasurementsManager::appendMeasurement(std::vector<std::shared_ptr<const MeasurementSequence>> mVecSeqNew)
{
    for (const auto& mesSeq : mVecSeqNew)
    {
        mVecSeq.push_back(mesSeq);
    }
    if (measurementState == State::Idle)
    {
        measurementState = State::CheckForMeas;
        emit newState(measurementState);
    }
}


void MeasurementsManager::startMeasurement(std::shared_ptr<const MeasurementSequence> measurementSequence)
{
    //qDebug() << "MeasManager::StartMeasurement";
    auto seqJc = std::dynamic_pointer_cast<const MeasSeqJc>(measurementSequence);
    fw = std::make_unique<FileWriter>();
    fw->openFile(measurementSequence);

    mSeqJc->setCurrentStart(seqJc->getCurrentStart());
    mSeqJc->setCurrentEnd(seqJc->getCurrentEnd());
    mSeqJc->setCurrentRate(seqJc->getCurrentRate());
    mSeqJc->setTemperature(seqJc->getTemperature());
    mSeqJc->setPulsewidth(seqJc->getPulsewidth());
    mSeqJc->setRatio(seqJc->getRatio());
    //scheint zu gehen, wenn ich hier die drei emits setzte
    emit newRatio(mSeqJc->getRatio());
    emit newPulseWidth(mSeqJc->getPulsewidth());
    emit newCurrentSetpoint(mSeqJc->getCurrentEnd());

    if (tempSP != mSeqJc->getTemperature())
    {
        instrumentmanager->setTempSetpoint(mSeqJc->getTemperature(), 20);
    }
    measurementState = State::ApproachStartJc;
    emit newState(measurementState);

    instrumentmanager->setAngle(measurementSequence->getCoilAngle());
    instrumentmanager->setMagFieldSP(measurementSequence->getMagneticField(), 200);
}

void MeasurementsManager::rotatorState(bool rotator)
{
    instrumentmanager->rotatorState(rotator);
}

void MeasurementsManager::onNewData(std::shared_ptr<DataPoint> datapoint)
{
    emit newData(datapoint);

    //ppmsStatus
    QString ppmsStatusStr = QString::fromStdString(datapoint->getPpmsdata()->getStatusPpms());
    auto ppmsStatus = ppmsStatusStr.toDouble();
    bool tempStable = false;
    bool magStable = false;
    bool rotStable = false;
    if ((static_cast<int>(ppmsStatus) & 0b1111) == 1) { tempStable = true; }
    if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 1) { magStable = true; }
    if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 1) { rotStable = true; }

    switch (measurementState)
    {
        case State::Idle:
        {
            /*
             * if abfrage-> ob das Programm bei Aktueller Temp bleiben soll, oder Energiesparmodus!
            */
            // Der Kommentar ist noch von Hendrik; ich weiß nicht genau was er da machen wollte, hab es also auch noch nicht bearbeitet
            // Also entweder bearbeitet das in Zukunft jemand (Hallo zukünftiger jemand!), oder man schmeißt das mal raus
            break;
        }
    //Jc
        case State::ApproachStartJc:
        {
            //qDebug() << "State::ApproachStartJc";
        // Sind Parameter nahe genug an den gewollten Startwerten, starte Messung
        // gehe also auf approachEndJc
            if (std::abs(mSeqJc->getTemperature() - datapoint->getPpmsdata()->getTempLive()) < 0.6 &&
                std::abs(magFieldSP - datapoint->getPpmsdata()->getMagFieldLive()) < 10 &&
                std::abs(angleSP - datapoint->getPpmsdata()->getRotLive()) < 1 &&
                tempStable == true && magStable == true && rotStable == true)
            {
                measurementState = State::ApproachEndJc;
                instrumentmanager->setPulseAndMeasure(mSeqJc->getCurrentStart(), mSeqJc->getPulsewidth(), mSeqJc->getRatio());
                mSeqJc->setCurrentLive(mSeqJc->getCurrentStart());
                emit newState(measurementState);
            }
            break;
        }

        case State::ApproachEndJc:
        {
            if ((datapoint->getKeithleyData()->getCurrent()+mSeqJc->getCurrentRate()) <= mSeqJc->getCurrentEnd())
            {
                instrumentmanager->setPulseAndMeasure(mSeqJc->getCurrentLive() + mSeqJc->getCurrentRate(), mSeqJc->getPulsewidth(), mSeqJc->getRatio());
                mSeqJc->setCurrentLive(mSeqJc->getCurrentLive()+mSeqJc->getCurrentRate());
            }

    // Wenn Stromstärke weniger als eine Schrittweite vom Zielwert entfernt:
    // Beende Messung, setze neuen State und emitte newState
            if (fw != nullptr)
            {
                fw->MeasurementState(measurementState);
                fw->append(datapoint);
            }
            if (std::abs(mSeqJc->getCurrentEnd() - datapoint->getKeithleyData()->getCurrent()) < mSeqJc->getCurrentRate())
            {
                tempSP = datapoint->getPpmsdata()->getTempSetpoint();
                fw->closeFile();
                measurementState = State::CheckForMeas;
                measurementNumber++;
                emit newState(measurementState);
            }
            break;
        }

        case State::CheckForMeas:
        {
        // Wenn es also noch weitere Messungen gibt, fange neue Messung an
            if (mVecSeq.size() > measurementNumber)
            {
                emit startNewMeasurement(mVecSeq[measurementNumber]);
                startMeasurement(mVecSeq[measurementNumber]);
            }
            else
            {
                measurementState = State::Idle;
                emit newState(measurementState);
            }
            break;
        }

    default:assert(false);
    }
}

void MeasurementsManager::onNewTempSP(double setpoint, double rate)
{
    emit newTempSP(setpoint, rate);
}

void MeasurementsManager::onNewCurrentValues(double current, double voltage)
{
    emit newCurrentValues(current, voltage);
}

void MeasurementsManager::onNewMagSP(double magField, double magRate)
{
    emit newMagSP(magField, magRate);
    magFieldSP = magField;
}

void MeasurementsManager::onNewAngleSP(double angle)
{
    emit newAngleSP(angle);
    angleSP = angle;
}

void MeasurementsManager::onNewRotstate(bool rotActive)
{
    emit newRotstate(rotActive);
}

void MeasurementsManager::onNewErrorMessage(QString errormessagePpms)
{
    emit newErrorMessage(errormessagePpms);
}

