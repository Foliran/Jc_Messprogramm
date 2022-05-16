#include "startdialog.h"

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
//#include "../Measurements/measseqtc.h"
#include "../Core/measseqjc.h"

StartDialog::StartDialog(QWidget* parent)
    : QDialog(parent)
    //, widgetTc(new QWidget(this))
    , widgetJc(new QWidget(this))
    , sampleNameJc(nullptr)
    , tempJc(nullptr)
    , magneticFieldJc(nullptr)
    , currentStartJc(nullptr)
    , currentEndJc(nullptr)
    , currentRateJc(nullptr)
    , voltageCriterion(nullptr)
    , coilAngleJc(nullptr)
    , nPulses(nullptr)
{
    setupUI();
}

QSize StartDialog::sizeHint() const
{
    return QSize(400, 300);
}

QSize StartDialog::minimumSizeHint() const
{
    return QSize(200, 100);
}

void StartDialog::accept()
{
    auto vecSeq = createSequence();

    emit createMeasurement(vecSeq);
}

void StartDialog::setupUI()
{
    auto gridLayoutJc = new QGridLayout();
    //auto boxButton = new QHBoxLayout();

    //Jc Measurement
    sampleNameJc = new QLineEdit();
    sampleNameJc->setText("");

    reversedPulse = new QCheckBox();
    reversedPulse->setText("Pulse reversed");

    logSteps = new QCheckBox();
    logSteps->setText("logarithmic steps");

    tempJc = new QDoubleSpinBox();
    tempJc->setDecimals(2);
    tempJc->setSingleStep(0.1);
    tempJc->setRange(0, 400);
    tempJc->setValue(320);

    currentStartJc = new QDoubleSpinBox();
    currentStartJc->setDecimals(3);
    currentStartJc->setSingleStep(0.002);
    currentStartJc->setRange(0.00, 20);
    currentStartJc->setValue(0.00);

    currentEndJc = new QDoubleSpinBox();
    currentEndJc->setDecimals(3);
    currentEndJc->setSingleStep(0.01);
    currentEndJc->setRange(0, 20);
    currentEndJc->setValue(0.1);

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

    coilAngleJc = new QDoubleSpinBox();
    coilAngleJc->setDecimals(1);
    coilAngleJc->setSingleStep(0.5);
    coilAngleJc->setRange(0, 360);
    coilAngleJc->setValue(0);

    pulseWidth = new QDoubleSpinBox();
    pulseWidth->setDecimals(0);
    pulseWidth->setSingleStep(1);
    pulseWidth->setValue(30);
    pulseWidth->setRange(0.1, 1000);

    nPulses = new QDoubleSpinBox();
    nPulses->setDecimals(0);
    nPulses->setSingleStep(1);
    nPulses->setValue(1);

    timeBetweenPulses = new QDoubleSpinBox();
    timeBetweenPulses->setDecimals(0);
    timeBetweenPulses->setValue(100);
    timeBetweenPulses->setRange(0, 1000);
    timeBetweenPulses->setSingleStep(1);

    ratio = new QDoubleSpinBox();
    ratio->setDecimals(2);
    ratio->setSingleStep(0.01);
    ratio->setRange(0, 1000);
    ratio->setValue(0.5);

    voltageCriterion = new QDoubleSpinBox();
    voltageCriterion->setDecimals(0);
    voltageCriterion->setValue(5);
    voltageCriterion->setRange(0, 20);
    voltageCriterion->setSingleStep(1);

    auto labelSampleNameJc = new QLabel("Sample name:");
    auto labelTempJc = new QLabel("Temperature:");
    auto labelCurrentStartJc = new QLabel("Start current:");
    auto labelCurrentEndJc = new QLabel("End current:");
    labelCurrentRate = new QLabel("Current rate:");
    auto labelVoltageCriterion = new QLabel("Voltage end criterion: 10e-");
    auto labelMagneticFieldJc = new QLabel("Magnetic field:");
    auto labelCoilAngleJc = new QLabel("Coil angle:");
    auto labelPulseWidth = new QLabel("Pulse width: ");
    auto labelNPulses= new QLabel("Number of pulses: ");
    auto labelTimeBetwPulses= new QLabel("Time between pulses: ");
    auto labelRatio = new QLabel("Measurement delay:");

    gridLayoutJc->addWidget(reversedPulse, 0, 0);
    gridLayoutJc->addWidget(logSteps, 0, 1);
    gridLayoutJc->addWidget(labelSampleNameJc);
    gridLayoutJc->addWidget(sampleNameJc);
    gridLayoutJc->addWidget(labelTempJc);
    gridLayoutJc->addWidget(tempJc);
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
    gridLayoutJc->addWidget(labelMagneticFieldJc);
    gridLayoutJc->addWidget(magneticFieldJc);
    gridLayoutJc->addWidget(labelCoilAngleJc);
    gridLayoutJc->addWidget(coilAngleJc);

    widgetJc->setLayout(gridLayoutJc);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
        | QDialogButtonBox::Close);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(logSteps, &QCheckBox::stateChanged, this, &StartDialog::adjustCurrent);

    //set MainLayout
    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(widgetJc);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
}

std::vector <std::shared_ptr<const MeasurementSequence>> StartDialog::createSequence() const
{
    std::vector <std::shared_ptr<const MeasurementSequence>> vecSeq;
    MeasSeqJc seqJc;
    seqJc.setSupraName(sampleNameJc->text());
    seqJc.setTemperature(tempJc->value());
    seqJc.setMagneticField(magneticFieldJc->value());
    seqJc.setCurrentStart(currentStartJc->value());
    seqJc.setCurrentEnd(currentEndJc->value());
    seqJc.setCurrentRate(currentRateJc->value());
    seqJc.setCoilAngle(coilAngleJc->value());
    seqJc.setPulsewidth(pulseWidth->value());
    seqJc.setNumberPulses((int)nPulses->value());
    seqJc.setInterPulseTime(timeBetweenPulses->value());
    seqJc.setRatio(ratio->value());
    seqJc.setFileName(sampleNameJc->text() + "_" +
        QString::number(tempJc->value()) + "K_" +
        //QString::number(frequencyJc_->value()) + "hz_" +
        QString::number(magneticFieldJc->value()) + "mT_" +
        QString::number(coilAngleJc->value()) + "d"
    );
    if(logSteps->isChecked() && reversedPulse->isChecked())
    {
        seqJc.setPulseMode(4);
        //qDebug() << "PulseMode ist logReversed";
    }
    else if(logSteps->isChecked() && !reversedPulse->isChecked())
    {
        seqJc.setPulseMode(2);
        //qDebug() << "PulseMode ist logOnce";
    }
    else if(!logSteps->isChecked() && reversedPulse->isChecked())
    {
        seqJc.setPulseMode(3);
        //qDebug() << "PulseMode ist linearReversed";
    }
    else if(!logSteps->isChecked() && !reversedPulse->isChecked())
    {
        seqJc.setPulseMode(1);
        //qDebug() << "PulseMode ist LinearOnce";
    }
    vecSeq.push_back(std::make_shared<const MeasSeqJc>(seqJc));
    return vecSeq;
}

void StartDialog::adjustCurrent() {
    if(logSteps->isChecked())
    {
        labelCurrentRate->setText(QChar(0x0394)+QString(" I / I"));
        currentRateJc->setValue(0.025);
    } else {
        labelCurrentRate->setText("Current rate");
        currentRateJc->setValue(0.01);
    }
}
