#include "startdialogmulti.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <vector>
#include <QButtonGroup>
#include <QMessageBox>
#include <math.h>
#include <QDebug>

//fertig

//Internal Classes
#include "../Core/measurementsequence.h"
#include "../Core/measseqjc.h"

StartDialogMulti::StartDialogMulti(QWidget* parent)
    : QDialog(parent)
    , widgetJc(new QWidget(this))
    , sampleNameJc(nullptr)
    , startTempJc(nullptr)
    , endTempJc(nullptr)
    , tempRateJc(nullptr)
    , magneticFieldJc(nullptr)
    , currentStartJc(nullptr)
    , currentEndJc(nullptr)
    , currentRateJc(nullptr)
    , voltageCriterion(nullptr)
    , nPulses(nullptr)
{
    setupUI();
}

QSize StartDialogMulti::sizeHint() const
{
    return QSize(400, 300);
}

QSize StartDialogMulti::minimumSizeHint() const
{
    return QSize(200, 100);
}

void StartDialogMulti::accept()
{
    auto vecSeq = createSequence();

    emit createMeasurement(vecSeq);
}

void StartDialogMulti::setupUI()
{
    auto gridLayoutJc = new QGridLayout();

    //Jc Measurement
    sampleNameJc = new QLineEdit();
    sampleNameJc->setText("");

    reversedPulse = new QCheckBox();
    reversedPulse->setText("Pulse reversed");
    reversedPulse->setChecked(1);

    logSteps = new QCheckBox();
    logSteps->setText("logarithmic steps");
    logSteps->setChecked(1);

    startTempJc = new QDoubleSpinBox();
    startTempJc->setDecimals(2);
    startTempJc->setSingleStep(0.1);
    startTempJc->setRange(0, 400);
    startTempJc->setValue(90);

    endTempJc = new QDoubleSpinBox();
    endTempJc->setDecimals(2);
    endTempJc->setSingleStep(0.1);
    endTempJc->setRange(0, 400);
    endTempJc->setValue(50);

    tempRateJc = new QDoubleSpinBox();
    tempRateJc->setDecimals(2);
    tempRateJc->setSingleStep(0.1);
    tempRateJc->setRange(0, 400);
    tempRateJc->setValue(0.5);

    currentStartJc = new QDoubleSpinBox();
    currentStartJc->setDecimals(3);
    currentStartJc->setSingleStep(0.002);
    currentStartJc->setRange(0.00, 20);
    currentStartJc->setValue(0.1);

    currentEndJc = new QDoubleSpinBox();
    currentEndJc->setDecimals(3);
    currentEndJc->setSingleStep(0.01);
    currentEndJc->setRange(0, 20);
    currentEndJc->setValue(20);

    currentRateJc = new QDoubleSpinBox();
    currentRateJc->setDecimals(3);
    currentRateJc->setSingleStep(0.002);
    currentRateJc->setRange(0.0001, 1.0);
    currentRateJc->setValue(0.01);

    magneticFieldJc = new QDoubleSpinBox();
    magneticFieldJc->setDecimals(2);
    magneticFieldJc->setSingleStep(0.1);
    magneticFieldJc->setRange(0, 14000);
    magneticFieldJc->setValue(0);

    pulseWidth = new QDoubleSpinBox();
    pulseWidth->setDecimals(0);
    pulseWidth->setSingleStep(1);
    pulseWidth->setValue(30);
    pulseWidth->setRange(20, 1000);

    nPulses = new QDoubleSpinBox();
    nPulses->setDecimals(0);
    nPulses->setSingleStep(1);
    nPulses->setValue(2);

    timeBetweenPulses = new QDoubleSpinBox();
    timeBetweenPulses->setDecimals(0);
    timeBetweenPulses->setRange(0, 1000);
    timeBetweenPulses->setSingleStep(1);
    timeBetweenPulses->setValue(100);

    ratio = new QDoubleSpinBox();
    ratio->setDecimals(0);
    ratio->setSingleStep(1);
    ratio->setRange(0, 1000);
    ratio->setValue(2);

    voltageCriterion = new QDoubleSpinBox();
    voltageCriterion->setDecimals(0);
    voltageCriterion->setRange(0, 20);
    voltageCriterion->setSingleStep(1);
    voltageCriterion->setValue(4);

    auto labelSampleNameJc = new QLabel("Sample name:");
    auto labelStartTempJc = new QLabel("Start temperature in K:");
    auto labelEndTempJc = new QLabel("End temperature in K:");
    auto labelTempRateJc = new QLabel("Temperature rate in K:");
    auto labelCurrentStartJc = new QLabel("Start current in A:");
    auto labelCurrentEndJc = new QLabel("End current in A:");
    labelCurrentRate = new QLabel("Current stepsize in A:");
    auto labelVoltageCriterion = new QLabel("Voltage end criterion in V: 1e-");
    auto labelMagneticFieldJc = new QLabel("Magnetic field in mT:");
    auto labelPulseWidth = new QLabel("Pulse width in ms: ");
    auto labelNPulses= new QLabel("Number of pulses: ");
    auto labelTimeBetwPulses = new QLabel("Time between pulses in ms: ");
    auto labelRatio = new QLabel("Measurement delay in ms:");

    adjustCurrent();

    gridLayoutJc->addWidget(reversedPulse, 0, 0);
    gridLayoutJc->addWidget(logSteps, 0, 1);
    gridLayoutJc->addWidget(labelSampleNameJc);
    gridLayoutJc->addWidget(sampleNameJc);
    gridLayoutJc->addWidget(labelStartTempJc);
    gridLayoutJc->addWidget(startTempJc);
    gridLayoutJc->addWidget(labelEndTempJc);
    gridLayoutJc->addWidget(endTempJc);
    gridLayoutJc->addWidget(labelTempRateJc);
    gridLayoutJc->addWidget(tempRateJc);
    gridLayoutJc->addWidget(labelMagneticFieldJc);
    gridLayoutJc->addWidget(magneticFieldJc);
    gridLayoutJc->addWidget(labelCurrentStartJc);
    gridLayoutJc->addWidget(currentStartJc);
    gridLayoutJc->addWidget(labelCurrentEndJc);
    gridLayoutJc->addWidget(currentEndJc);
    gridLayoutJc->addWidget(labelCurrentRate);
    gridLayoutJc->addWidget(currentRateJc);
    gridLayoutJc->addWidget(labelVoltageCriterion);
    gridLayoutJc->addWidget(voltageCriterion);
    gridLayoutJc->addWidget(labelPulseWidth);
    gridLayoutJc->addWidget(pulseWidth);
    gridLayoutJc->addWidget(labelNPulses);
    gridLayoutJc->addWidget(nPulses);
    gridLayoutJc->addWidget(labelTimeBetwPulses);
    gridLayoutJc->addWidget(timeBetweenPulses);
    gridLayoutJc->addWidget(labelRatio);
    gridLayoutJc->addWidget(ratio);

    widgetJc->setLayout(gridLayoutJc);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
        | QDialogButtonBox::Close);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(logSteps, &QCheckBox::stateChanged, this, &StartDialogMulti::adjustCurrent);

    //set MainLayout
    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(widgetJc);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
}

std::vector <std::shared_ptr<const MeasSeqJc>> StartDialogMulti::createSequence() const
{
    std::vector <std::shared_ptr<const MeasSeqJc>> vecSeq;
    int nMeasurements = std::abs(startTempJc->value() - endTempJc->value()) / tempRateJc->value() + 1;
    int direction = startTempJc->value() > endTempJc->value() ? -1: 1;
    double temp = startTempJc->value();
    for(int i = 0; i < nMeasurements; i++)
    {
        MeasSeqJc seqJc;
        seqJc.setSupraName(sampleNameJc->text());
        seqJc.setTemperature(temp);
        seqJc.setMagneticField(magneticFieldJc->value());
        seqJc.setCurrentStart(currentStartJc->value());
        seqJc.setCurrentEnd(currentEndJc->value());
        seqJc.setCurrentRate(currentRateJc->value());
        seqJc.setCoilAngle(0);
        seqJc.setPulsewidth(pulseWidth->value());
        seqJc.setNumberPulses((int)nPulses->value());
        seqJc.setInterPulseTime(timeBetweenPulses->value());
        seqJc.setRatio(ratio->value());
        seqJc.setVoltageCriterion(std::pow(10, -(double)voltageCriterion->value()));
        seqJc.setFileName(sampleNameJc->text() + "_" +
            QString::number(temp) + "K_" +
            QString::number(magneticFieldJc->value()) + "mT");
        temp = temp + direction * tempRateJc->value();
        if(!logSteps->isChecked() && !reversedPulse->isChecked())
        {
            seqJc.setPulseMode(1);
        }
        else if(logSteps->isChecked() && !reversedPulse->isChecked())
        {
            seqJc.setPulseMode(2);
        }
        else if(!logSteps->isChecked() && reversedPulse->isChecked())
        {
            seqJc.setPulseMode(3);
        }
        else if(logSteps->isChecked() && reversedPulse->isChecked())
        {
            seqJc.setPulseMode(4);
        }
        vecSeq.push_back(std::make_shared<const MeasSeqJc>(seqJc));
    }
    return vecSeq;

}

void StartDialogMulti::adjustCurrent() {
    if(logSteps->isChecked())
    {
        labelCurrentRate->setText(QChar(0x0394)+QString(" I / I"));
        currentRateJc->setValue(0.025);
    } else {
        labelCurrentRate->setText("Current rate");
        currentRateJc->setValue(0.01);
    }
}
