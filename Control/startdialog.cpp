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
    , coilAngleJc(nullptr)
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
    auto boxButton = new QHBoxLayout();


    //Jc Measurement
    sampleNameJc = new QLineEdit();
    sampleNameJc->setText("");

    tempJc = new QDoubleSpinBox();
    tempJc->setDecimals(2);
    tempJc->setSingleStep(0.1);
    tempJc->setRange(0, 400);
    tempJc->setValue(80);

    currentStartJc = new QDoubleSpinBox();
    currentStartJc->setDecimals(3);
    currentStartJc->setSingleStep(0.002);
    currentStartJc->setRange(0.004, 5);
    currentStartJc->setValue(0.004);

    currentEndJc = new QDoubleSpinBox();
    currentEndJc->setDecimals(3);
    currentEndJc->setSingleStep(0.01);
    currentEndJc->setRange(0, 5);
    currentEndJc->setValue(1.0);

    currentRateJc = new QDoubleSpinBox();
    currentRateJc->setDecimals(3);
    currentRateJc->setSingleStep(0.002);
    currentRateJc->setRange(0.002, 0.1);
    currentRateJc->setValue(0.002);

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

    ratio = new QDoubleSpinBox();
    ratio->setDecimals(2);
    ratio->setSingleStep(0.01);
    ratio->setValue(0.5);

    auto labelSampleNameJc = new QLabel("Sample Name:");
    auto labelTempJc = new QLabel("Temperature:");
    auto labelCurrentStartJc = new QLabel("Start Current:");
    auto labelCurrentEndJc = new QLabel("End Current:");
    auto labelCurrentRate = new QLabel("Current Rate:");
    auto labelMagneticFieldJc = new QLabel("Magnetic Field:");
    auto labelCoilAngleJc = new QLabel("Coil Angle:");
    auto labelPulseWidth = new QLabel("Pulse width");
    auto labelRatio = new QLabel("Measurement Ratio:");

    gridLayoutJc->addWidget(labelSampleNameJc, 0, 0);
    gridLayoutJc->addWidget(sampleNameJc, 0, 1);
    gridLayoutJc->addWidget(labelTempJc);
    gridLayoutJc->addWidget(tempJc);
    gridLayoutJc->addWidget(labelCurrentStartJc);
    gridLayoutJc->addWidget(currentStartJc);
    gridLayoutJc->addWidget(labelCurrentEndJc);
    gridLayoutJc->addWidget(currentEndJc);
    gridLayoutJc->addWidget(labelCurrentRate);
    gridLayoutJc->addWidget(currentRateJc);
    gridLayoutJc->addWidget(labelPulseWidth);
    gridLayoutJc->addWidget(pulseWidth);
    gridLayoutJc->addWidget(labelRatio);
    gridLayoutJc->addWidget(ratio);
    gridLayoutJc->addWidget(labelMagneticFieldJc);
    gridLayoutJc->addWidget(magneticFieldJc);
    gridLayoutJc->addWidget(labelCoilAngleJc);
    gridLayoutJc->addWidget(coilAngleJc);

    //set Layouts
    //widgetTc->setLayout(gridLayout);
    widgetJc->setLayout(gridLayoutJc);
    auto boxwidget = new QWidget();
    boxwidget->setLayout(boxButton);
    widgetJc->setVisible(true);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
        | QDialogButtonBox::Close);

    //connect(buttongroupmes, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
    //    this, &StartDialog::updateUI);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    //set MainLayout
    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(boxwidget);
    //mainLayout->addWidget(widgetTc);
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
    seqJc.setRatio(ratio->value());
    seqJc.setFileName(sampleNameJc->text() + "_" +
        QString::number(tempJc->value()) + "K_" +
        //QString::number(frequencyJc_->value()) + "hz_" +
        QString::number(magneticFieldJc->value()) + "mT_" +
        QString::number(coilAngleJc->value()) + "d"
    );
    vecSeq.push_back(std::make_shared<const MeasSeqJc>(seqJc));
    return vecSeq;
}
