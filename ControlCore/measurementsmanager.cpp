#include "measurementsmanager.h"
#include <QDebug>
#include <vector>

//Internal Classes
#include "instrumentmanager.h"
//#include "../Core/measurementsequence.h"
#include "../Core/measseqjc.h"
#include "../Core/datapoint.h"
#include "../Core/filewriter.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Core/datapoint.h"
#include <QThread>
#include <QTime>
#include <memory>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>


MeasurementsManager::MeasurementsManager()
    : measurementState(State::Idle)
    , measurementNumber(0)
    , instrumentmanager(std::make_unique<InstrumentManager>())
    , fw(nullptr)
    , mSeqJc(std::make_shared<MeasSeqJc>())
    , msg(nullptr)
    , magFieldSP(0)
    , angleSP(0)
    , tempSP(0)
    , timeToWait(300)
    , goToShutdown(false)

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
    msg = new QWidget();
    textLabel = new QLabel();
    QHBoxLayout *lyt = new QHBoxLayout();
    lyt->addWidget(textLabel);
    msg->setLayout(lyt);
    remainingTime = timeToWait;
}

MeasurementsManager::~MeasurementsManager()
{

}

void MeasurementsManager::openDevice()
{
    instrumentmanager->openDevice();
}


void MeasurementsManager::appendMeasurement(std::vector<std::shared_ptr<const MeasSeqJc>> mVecSeqNew)
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

void MeasurementsManager::startMeasurement(std::shared_ptr<const MeasSeqJc> measurementSequence)
{
    auto seqJc = std::dynamic_pointer_cast<const MeasSeqJc>(measurementSequence);
    fw = std::make_unique<FileWriter>();
    fw->openFile(measurementSequence);

    mSeqJc->setCurrentStart(seqJc->getCurrentStart());
    mSeqJc->setCurrentEnd(seqJc->getCurrentEnd());
    mSeqJc->setCurrentRate(seqJc->getCurrentRate());
    mSeqJc->setTemperature(seqJc->getTemperature());
    mSeqJc->setPulsewidth(seqJc->getPulsewidth());
    mSeqJc->setRatio(seqJc->getRatio());
    mSeqJc->setPulseMode(seqJc->getPulseMode());
    mSeqJc->setInterPulseTime(seqJc->getInterPulseTime());
    mSeqJc->setNumberPulses(seqJc->getNumberPulses());
    mSeqJc->setVoltageCriterion(seqJc->getVoltageCriterion());
    mSeqJc->setMagneticField(seqJc->getMagneticField());
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
    if(mSeqJc->getMagneticField() > 0.0) {
        instrumentmanager->setMagFieldSP(mSeqJc->getMagneticField(), 200);
    } else {
        instrumentmanager->setMagFieldSP(0.0, 1.0);
    }
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
            qDebug() << "Idle";
            /*
             * if abfrage-> ob das Programm bei Aktueller Temp bleiben soll, oder Energiesparmodus!
            */
            // Der Kommentar ist noch von Hendrik; ich weiß nicht genau was er da machen wollte, hab es also auch noch nicht bearbeitet
            // Also entweder bearbeitet das in Zukunft jemand (Hallo zukünftiger jemand!), oder man schmeißt das mal raus
            break;
        }

        case State::ApproachStartJc:
        {
            qDebug() << "ApproachStartJc";
            // Sind Parameter nahe genug an den gewollten Startwerten, starte Messung
            // gehe also auf approachEndJc
            if (std::abs(mSeqJc->getTemperature() - datapoint->getPpmsdata()->getTempLive()) < 0.6 &&
                std::abs(magFieldSP - datapoint->getPpmsdata()->getMagFieldLive()) < 10 &&
                std::abs(angleSP - datapoint->getPpmsdata()->getRotLive()) < 1 &&
                tempStable == true && magStable == true && rotStable == true)
            {
                measurementState = State::waitForTemp;
                emit newState(measurementState);
            }
            break;
        }
        case State::waitForTemp:
        {
            qDebug() << "WaitForTemp, remainingTime is" << remainingTime;
            if(remainingTime == timeToWait) {
                //qDebug() << "First if";
                std::string txt = "Waiting for " + std::to_string(remainingTime) + " more seconds before starting the measurement";
                textLabel->setText(QString::fromStdString(txt));
                msg->show();
                remainingTime--;
            }
            else if(remainingTime > 0 && remainingTime < timeToWait) {
                //qDebug() << "Second if";
                std::string txt = "Waiting for " + std::to_string(remainingTime) + " more seconds before starting the measurement";
                textLabel->setText(QString::fromStdString(txt));
                remainingTime--;
                qDebug() << remainingTime;
            }
            else if(remainingTime == 0){
                //qDebug() << "Third if";
                remainingTime = timeToWait;
                msg->close();
                measurementState = State::MeasureBackground;
                emit newState(measurementState);
            }
            break;
        }
        case State::MeasureBackground:
        {
            qDebug() << "MeasureBackground";
            if(datapoint->getKeithleyData()->getBackground() == -1000.0)
            {
                // -1000 -> Background noch nicht gemessen
                emit resetGraph(mSeqJc);
                if(mSeqJc->getPulseMode() == 1  || mSeqJc->getPulseMode() == 2)
                {
                    instrumentmanager->initializeSettings(mSeqJc->getPulsewidth(), mSeqJc->getRatio(), mSeqJc->getNumberPulses(), mSeqJc->getInterPulseTime(), false);
                } else if(mSeqJc->getPulseMode() == 3 || mSeqJc->getPulseMode() == 4) {
                    instrumentmanager->initializeSettings(mSeqJc->getPulsewidth(), mSeqJc->getRatio(), mSeqJc->getNumberPulses(), mSeqJc->getInterPulseTime(), true);
                }
                instrumentmanager->measureBackground();
            }
            else if(!instrumentmanager->isBusyBackground()){
                measurementState = State::ApproachEndJc;
                instrumentmanager->setPulseAndMeasure(mSeqJc->getCurrentStart());
                mSeqJc->setCurrentLive(mSeqJc->getCurrentStart());
                emit newState(measurementState);
            }
            break;
        }

        case State::ApproachEndJc:
        {
            qDebug() << "ApproachEndJc" ;
            int sleeptime = 2 * mSeqJc->getNumberPulses() * (mSeqJc->getPulsewidth() + mSeqJc->getInterPulseTime());
            //TODO: Ausprobieren ob es reicht, wenn ich das hier als Interval setze
            instrumentmanager->timer->setInterval(sleeptime);
            double newCurrent = 0;
            if(mSeqJc->getPulseMode() == 1 || mSeqJc->getPulseMode() == 3) {
                newCurrent = mSeqJc->getCurrentLive() + mSeqJc->getCurrentRate();
            } else if(mSeqJc->getPulseMode() == 2 || mSeqJc->getPulseMode() == 4) {
                newCurrent = mSeqJc->getCurrentLive() + mSeqJc->getCurrentLive() * mSeqJc->getCurrentRate();
            }
            // Wenn Stromstärke weniger als eine Schrittweite vom Zielwert entfernt:
            // Beende Messung, setze neuen State und emitte newState
            if (fw != nullptr)
            {
                fw->MeasurementState(measurementState);
                fw->append(datapoint);
            }
            if (newCurrent <= mSeqJc->getCurrentEnd() )
            {
                instrumentmanager->setPulseAndMeasure(newCurrent);
                mSeqJc->setCurrentLive(newCurrent);
            } else
            {
                qDebug() << "Reached maximal current";
                tempSP = datapoint->getPpmsdata()->getTempSetpoint();
                fw->closeFile();
                measurementState = State::CheckForMeas;
                measurementNumber++;
                instrumentmanager->resetBackground();
                instrumentmanager->timer->setInterval(1000);
                emit newState(measurementState);
            }
            if(std::abs(datapoint->getKeithleyData()->getVoltage()) > std::abs(mSeqJc->getVoltageCriterion()))
            {
                qDebug() << "Reached maximal voltage";
                tempSP = datapoint->getPpmsdata()->getTempSetpoint();
                fw->closeFile();
                measurementState = State::CheckForMeas;
                measurementNumber++;
                instrumentmanager->resetBackground();
                instrumentmanager->timer->setInterval(1000);
                emit newState(measurementState);
            }
            break;
        }

        case State::SkipMeasurement:
        {
            qDebug() << "SkipMeasurement";
            tempSP = datapoint->getPpmsdata()->getTempSetpoint();
            fw->closeFile();
            measurementState = State::CheckForMeas;
            measurementNumber++;
            instrumentmanager->resetBackground();
            emit newState(measurementState);
        }

        case State::CheckForMeas:
        {
            // Wenn es also noch weitere Messungen gibt, fange neue Messung an

            qDebug() << "CheckForMeas";
            if (mVecSeq.size() > measurementNumber)
            {
                emit startNewMeasurement(mVecSeq[measurementNumber]);
                startMeasurement(mVecSeq[measurementNumber]);
            }
            else
            {
                if(goToShutdown)
                {
                    instrumentmanager->shutdown();
                }
                measurementState = State::Idle;
                emit newState(measurementState);
            }
            break;
        }
        case State::PauseMeasurement:
        {
            emit newState(measurementState);
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

void MeasurementsManager::setWaitingTime(int time) {
    if(measurementState != State::waitForTemp) {
        remainingTime = time;
    }
    timeToWait = time;
}
