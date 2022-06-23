#include "startdialogmulti_b.h"

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

StartDialogMulti_B::StartDialogMulti_B(QWidget* parent)
    : QDialog(parent)
    , widgetJc(new QWidget(this))
    , sampleNameJc(nullptr)
    , startMagFieldJc(nullptr)
    , endMagFieldJc(nullptr)
    , fieldRateJc(nullptr)
    , temperatureJc(nullptr)
    , currentStartJc(nullptr)
    , currentEndJc(nullptr)
    , currentRateJc(nullptr)
    , voltageCriterion(nullptr)
    , nPulses(nullptr)
{
    setupUI();
}

QSize StartDialogMulti_B::sizeHint() const
{
    return QSize(400, 300);
}

QSize StartDialogMulti_B::minimumSizeHint() const
{
    return QSize(200, 100);
}

void StartDialogMulti_B::accept()
{
    auto vecSeq = createSequence();

    emit createMeasurement(vecSeq);
}

void StartDialogMulti_B::setupUI()
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

    startMagFieldJc = new QDoubleSpinBox();
    startMagFieldJc->setDecimals(2);
    startMagFieldJc->setSingleStep(0.1);
    startMagFieldJc->setRange(0, 14000);
    startMagFieldJc->setValue(14000);

    endMagFieldJc = new QDoubleSpinBox();
    endMagFieldJc->setDecimals(2);
    endMagFieldJc->setSingleStep(0.1);
    endMagFieldJc->setRange(0, 14000);
    endMagFieldJc->setValue(0);

    fieldRateJc = new QDoubleSpinBox();
    fieldRateJc->setDecimals(2);
    fieldRateJc->setSingleStep(0.1);
    fieldRateJc->setRange(0, 14000);
    fieldRateJc->setValue(500);

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
    currentRateJc->setValue(0.001);

    temperatureJc = new QDoubleSpinBox();
    temperatureJc->setDecimals(2);
    temperatureJc->setSingleStep(0.1);
    temperatureJc->setRange(0, 400);
    temperatureJc->setValue(77);

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
    timeBetweenPulses->setValue(1);

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
    auto labelStartFieldJc = new QLabel("Start magnetic field in mT:");
    auto labelEndFieldJc = new QLabel("End magnetic field in mT:");
    auto labelFieldRateJc = new QLabel("Field rate in mT:");
    auto labelCurrentStartJc = new QLabel("Start current in A:");
    auto labelCurrentEndJc = new QLabel("End current in A:");
    labelCurrentRate = new QLabel("Current stepsize in A:");
    auto labelVoltageCriterion = new QLabel("Voltage end criterion in V: 1e-");
    auto labelTemperatureJc = new QLabel("Temperature in K:");
    auto labelPulseWidth = new QLabel("Pulse width in ms: ");
    auto labelNPulses= new QLabel("Number of pulses: ");
    auto labelTimeBetwPulses = new QLabel("Time between pulses in ms: ");
    auto labelRatio = new QLabel("Measurement delay in ms:");

    adjustCurrent();

    gridLayoutJc->addWidget(reversedPulse, 0, 0);
    gridLayoutJc->addWidget(logSteps, 0, 1);
    gridLayoutJc->addWidget(labelSampleNameJc);
    gridLayoutJc->addWidget(sampleNameJc);
    gridLayoutJc->addWidget(labelStartFieldJc);
    gridLayoutJc->addWidget(startMagFieldJc);
    gridLayoutJc->addWidget(labelEndFieldJc);
    gridLayoutJc->addWidget(endMagFieldJc);
    gridLayoutJc->addWidget(labelFieldRateJc);
    gridLayoutJc->addWidget(fieldRateJc);
    gridLayoutJc->addWidget(labelTemperatureJc);
    gridLayoutJc->addWidget(temperatureJc);
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
    connect(logSteps, &QCheckBox::stateChanged, this, &StartDialogMulti_B::adjustCurrent);

    //set MainLayout
    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(widgetJc);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
}

std::vector <std::shared_ptr<const MeasSeqJc>> StartDialogMulti_B::createSequence() const
{
    std::vector <std::shared_ptr<const MeasSeqJc>> vecSeq;
    int nMeasurements = std::abs(startMagFieldJc->value() - endMagFieldJc->value()) / fieldRateJc->value() + 1;
    int direction = startMagFieldJc->value() > endMagFieldJc->value() ? -1: 1;
    double field = startMagFieldJc->value();
    for(int i = 0; i < nMeasurements; i++)
    {
        MeasSeqJc seqJc;
        seqJc.setSupraName(sampleNameJc->text());
        seqJc.setTemperature(temperatureJc->value());
        seqJc.setMagneticField(field);
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
            QString::number(temperatureJc->value()) + "K_" +
            QString::number(field)+ "mT");
        field = field + direction * fieldRateJc->value();
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

void StartDialogMulti_B::adjustCurrent() {
    if(logSteps->isChecked())
    {
        labelCurrentRate->setText(QChar(0x0394)+QString(" I / I"));
        currentRateJc->setValue(0.025);
    } else {
        labelCurrentRate->setText("Current rate");
        currentRateJc->setValue(0.01);
    }
}
