#include "ppmswidget.h"

#include <QDebug>
#include <vector>
#include <locale>
#include <sstream>
#include <iomanip>
#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

//fertig

//Internal Classes
#include "../Core/datapoint.h"
#include "../ControlCore/measurementsmanager.h"

PpmsWidget::PpmsWidget(QWidget* parent)
    : QWidget(parent)
    , tempSetPoint(nullptr)
    , tempLive(nullptr)
    , tempRate(nullptr)
    , tempStatus(nullptr)
    , magSetPoint(nullptr)
    , magFieldLive(nullptr)
    , magRate(nullptr)
    , magStatus(nullptr)
    , rotSetPoint(nullptr)
    , rotLive(nullptr)
    , rotStatus(nullptr)
    , chamberStatus(nullptr)
    , chamberLevel(nullptr)
    , sampleSpacePressure(nullptr)
    , currentEndpoint(nullptr)
    , currentRate(nullptr)
    , currentLive(nullptr)
    , voltageLive(nullptr)
    , pulseWidth(nullptr)
    , ratio(nullptr)
{
    setupUI();
}

QSize PpmsWidget::sizeHint() const
{
    return QSize(1800, 300);
}

QSize PpmsWidget::minimumSizeHint() const
{
    return QSize(400, 50);
}

void PpmsWidget::newData(std::shared_ptr<const DataPoint> dpoint)
{
    if (dpoint != nullptr)
    {
        tempLive->setText(QString::number(dpoint->getPpmsdata()->getTempLive()));
        tempStatus->setText(tempStatStr);
        magFieldLive->setText(QString::number(dpoint->getPpmsdata()->getMagFieldLive()));
        rotLive->setText(QString::number(dpoint->getPpmsdata()->getRotLive()));
        chamberLevel->setText(QString::number(dpoint->getPpmsdata()->getChamberLevel()));
        sampleSpacePressure->setText(QString::number(dpoint->getPpmsdata()->getSamplePressure()));
        voltageLive->setText(QString::number(dpoint->getKeithleyData()->getVoltage()));
        currentLive->setText(QString::number(dpoint->getKeithleyData()->getCurrent()));
        currentRate->setText(QString::number(dpoint->getKeithleyData()->getCurrentRate()));

        QString ppmsStatusStr = QString::fromStdString(dpoint->getPpmsdata()->getStatusPpms());
        auto ppmsStatus = ppmsStatusStr.toDouble();

        /*Kurze Erklärung: es wird auf die 3te Zahl zugegriffen und dann mit dem & operator geguckt wo sich die Binärzahlen unterscheiden/gleichen
        *die ersten 4 Zahlen (also 0->15) sind die erste if abfrage usw.
        */

        if ((static_cast<int>(ppmsStatus) & 0b1111) == 0) { tempStatus->setText("Status unknown"); }
        else if ((static_cast<int>(ppmsStatus) & 0b1111) == 1) { tempStatus->setText("Stable"); }
        else if ((static_cast<int>(ppmsStatus) & 0b1111) == 2) { tempStatus->setText("Tracking"); }
        else if ((static_cast<int>(ppmsStatus) & 0b1111) == 3) { tempStatus->setText("Reserved"); }
        else if ((static_cast<int>(ppmsStatus) & 0b1111) == 4) { tempStatus->setText("Reserved"); }
        else if ((static_cast<int>(ppmsStatus) & 0b1111) == 5) { tempStatus->setText("Near"); }
        else if ((static_cast<int>(ppmsStatus) & 0b1111) == 6) { tempStatus->setText("Chasing"); }
        else if ((static_cast<int>(ppmsStatus) & 0b1111) == 7) { tempStatus->setText("Filling/Emptying reservoir"); }
        else if ((static_cast<int>(ppmsStatus) & 0b1111) == 8) { tempStatus->setText("Reserved"); }
        else if ((static_cast<int>(ppmsStatus) & 0b1111) == 9) { tempStatus->setText("Reserved"); }
        else if ((static_cast<int>(ppmsStatus) & 0b1111) == 10) { tempStatus->setText("Stand By Mode"); }
        else if ((static_cast<int>(ppmsStatus) & 0b1111) == 11) { tempStatus->setText("Reserved"); }
        else if ((static_cast<int>(ppmsStatus) & 0b1111) == 12) { tempStatus->setText("Reserved"); }
        else if ((static_cast<int>(ppmsStatus) & 0b1111) == 13) { tempStatus->setText("temperature Control disabled"); }
        else if ((static_cast<int>(ppmsStatus) & 0b1111) == 14) { tempStatus->setText("Impedance not functioning"); }
        else if ((static_cast<int>(ppmsStatus) & 0b1111) == 15) { tempStatus->setText("General Failure"); }
        //Feld-Stati
        if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 0) { magStatus->setText("Status unknown"); }
        else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 1) { magStatus->setText("Persistent mode, stable"); }
        else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 2) { magStatus->setText("Persist mode switch warming"); }
        else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 3) { magStatus->setText("Persist mode switch cooling"); }
        else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 4) { magStatus->setText("Driven mode, stable at final field"); }
        else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 5) { magStatus->setText("Driven mode, final approach"); }
        else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 6) { magStatus->setText("Charging magnet at specified voltage"); }
        else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 7) { magStatus->setText("Discharging magnet"); }
        else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 8) { magStatus->setText("Current error, incorrect current in magnet"); }
        else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 9) { magStatus->setText("Reserved"); }
        else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 10) { magStatus->setText("Reserved"); }
        else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 11) { magStatus->setText("Reserved"); }
        else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 12) { magStatus->setText("Reserved"); }
        else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 13) { magStatus->setText("Reserved"); }
        else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 14) { magStatus->setText("Reserved"); }
        else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 15) { magStatus->setText("General failure in magnet control system"); }
        //Chamber-Stati
        if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 0) { chamberStatus->setText("Status unknown"); }
        else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 1) { chamberStatus->setText("Purged and sealed"); }
        else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 2) { chamberStatus->setText("Vented and sealed"); }
        else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 3) { chamberStatus->setText("Sealed, condition unknown"); }
        else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 4) { chamberStatus->setText("Performing purge/seal routine"); }
        else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 5) { chamberStatus->setText("Performing vent/seal sequence"); }
        else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 6) { chamberStatus->setText("Reserved"); }
        else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 7) { chamberStatus->setText("Reserved"); }
        else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 8) { chamberStatus->setText("Pumping continuously"); }
        else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 9) { chamberStatus->setText("Flooding continuously"); }
        else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 15) { chamberStatus->setText("General failure in gas control System"); }
        //angle
        if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 0) { rotStatus->setText("Status unknown"); }
        else if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 1) { rotStatus->setText("Sample stopped at target value"); }
        else if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 5) { rotStatus->setText("Sample moving toward set point"); }
        else if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 6) { rotStatus->setText("Reserved"); }
        else if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 7) { rotStatus->setText("Reserved"); }
        else if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 8) { rotStatus->setText("Sample hit limit switch"); }
        else if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 9) { rotStatus->setText("Sample hit index switch"); }
        else if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 15) { rotStatus->setText("General failure "); }
        else { rotStatus->setText("Reserved"); }

    }

}

void PpmsWidget::newMagSP(double magField, double magRateNew)
{
    magSetPoint->setText(QString::number(magField));
    magRate->setText(QString::number(magRateNew));
}

void PpmsWidget::newAngleSP(double angle)
{
    rotSetPoint->setText(QString::number(angle));
}

void PpmsWidget::newTempSP(double temp, double rate)
{
    tempSetPoint->setText(QString::number(temp));
    tempRate->setText(QString::number(rate));
}

void PpmsWidget::newCurrentValues(double curr, double rate)
{
    currentLive->setText(QString::number(curr));
    voltageLive->setText(QString::number(rate));
}

void PpmsWidget:: newPulseWidth(double value)
{
    pulseWidth->setText(QString::number(value));
}

void PpmsWidget::newRatio(double value)
{
    ratio->setText(QString::number(value));
}

void PpmsWidget::setupUI()
{
    tempLive = new QLabel();
    tempLive->setText("");
    tempSetPoint = new QLabel();
    tempSetPoint->setText("");
    tempRate = new QLabel();
    tempRate->setText("");
    tempStatus = new QLabel();
    tempStatus->setText("");

    magSetPoint = new QLabel();
    magSetPoint->setText("");
    magFieldLive = new QLabel();
    magFieldLive->setText("");
    magRate = new QLabel();
    magRate->setText("");
    magStatus = new QLabel();
    magStatus->setText("");

    rotLive = new QLabel();
    rotLive->setText("");
    rotSetPoint = new QLabel();
    rotSetPoint->setText("");
    rotStatus = new QLabel();
    rotStatus->setText("");

    chamberStatus = new QLabel();
    chamberStatus->setText("");
    chamberLevel = new QLabel();
    chamberLevel->setText("");
    sampleSpacePressure = new QLabel();
    sampleSpacePressure->setText("");

    voltageLive = new QLabel();
    voltageLive->setText("");
    currentLive = new QLabel();
    currentLive->setText("");
    pulseWidth = new QLabel();
    pulseWidth->setText("");
    ratio = new QLabel();
    ratio->setText("");

    //label
    auto labelTempLive = new QLabel("Temperature:");
    auto labelTempSetPoint = new QLabel("Temperature Setpoint:");
    auto labelTempRate = new QLabel("Temperature rate:");
    auto labelTempStatus = new QLabel("Status:");

    auto labelMagFeldLive = new QLabel("Mag. Field:");
    auto labelMagSetPoint = new QLabel("Setpoint:");
    auto labelMagRate = new QLabel("Mag. rate:");
    auto labelMagStatus = new QLabel("Status:");

    auto labelRotLive = new QLabel("Rotation:");
    auto labelRotSetPoint = new QLabel("Setpoint:");
    auto labelRotStatus = new QLabel("Status:");

    auto labelChamberLevel = new QLabel("Helium level:");
    auto labelChamberStatus = new QLabel("Status:");
    auto labelSampleSpacePressure = new QLabel("Chamber pressure: ");


    auto labelCurrentLive = new QLabel("Current:");
    auto labelCurrentRate = new QLabel("Current rate:");
    auto labelCurrentEndpoint = new QLabel("Current setpoint:");
    auto labelVoltageLive = new QLabel("Voltage: ");
    auto labelpulseWidth = new QLabel("Pulse width: ");
    auto labelRatio = new QLabel("Ratio: ");

    auto labelempty = new QLabel("");

    //Grid Layouts:
    auto TempGridLayout = new QGridLayout();
    auto MagGridLayout = new QGridLayout();
    auto RotGridLayout = new QGridLayout();
    auto ChamberGridLayout = new QGridLayout();
    auto VoltageGridLayout = new QGridLayout();

    TempGridLayout->addWidget(labelTempLive, 0, 0);
    TempGridLayout->addWidget(tempLive, 0, 1);
    TempGridLayout->addWidget(labelTempSetPoint, 1, 0);
    TempGridLayout->addWidget(tempSetPoint, 1, 1);
    TempGridLayout->addWidget(labelTempRate, 2, 0);
    TempGridLayout->addWidget(tempRate, 2, 1);
    TempGridLayout->addWidget(labelTempStatus, 3, 0);
    TempGridLayout->addWidget(tempStatus, 3, 1);

    MagGridLayout->addWidget(labelMagFeldLive, 0, 0);
    MagGridLayout->addWidget(magFieldLive, 0, 1);
    MagGridLayout->addWidget(labelMagSetPoint, 1, 0);
    MagGridLayout->addWidget(magSetPoint, 1, 1);
    MagGridLayout->addWidget(labelMagRate, 2, 0);
    MagGridLayout->addWidget(magRate, 2, 1);
    MagGridLayout->addWidget(labelMagStatus, 3, 0);
    MagGridLayout->addWidget(magStatus, 3, 1);

    RotGridLayout->addWidget(labelRotLive, 0, 0);
    RotGridLayout->addWidget(rotLive, 0, 1);
    RotGridLayout->addWidget(labelRotSetPoint, 1, 0);
    RotGridLayout->addWidget(rotSetPoint, 1, 1);
    RotGridLayout->addWidget(labelRotStatus, 2, 0);
    RotGridLayout->addWidget(rotStatus, 2, 1);
    RotGridLayout->addWidget(labelempty, 3, 0);
    RotGridLayout->addWidget(labelempty, 3, 1);

    ChamberGridLayout->addWidget(labelChamberLevel, 0, 0);
    ChamberGridLayout->addWidget(chamberLevel, 0, 1);
    ChamberGridLayout->addWidget(labelChamberStatus, 2, 0);
    ChamberGridLayout->addWidget(chamberStatus, 2, 1);
    ChamberGridLayout->addWidget(labelSampleSpacePressure, 1, 0);
    ChamberGridLayout->addWidget(sampleSpacePressure, 1, 1);
    ChamberGridLayout->addWidget(labelempty, 3, 0);
    ChamberGridLayout->addWidget(labelempty, 3, 1);

    VoltageGridLayout->addWidget(labelCurrentLive, 0, 0);
    VoltageGridLayout->addWidget(currentLive, 0, 1);
    VoltageGridLayout->addWidget(labelCurrentEndpoint, 1, 0);
    VoltageGridLayout->addWidget(currentEndpoint, 1, 1);
    VoltageGridLayout->addWidget(labelCurrentRate, 2, 0);
    VoltageGridLayout->addWidget(currentRate, 2, 1);
    VoltageGridLayout->addWidget(labelVoltageLive, 3, 0);
    VoltageGridLayout->addWidget(voltageLive, 3, 1);
    VoltageGridLayout->addWidget(labelpulseWidth, 4, 0);
    VoltageGridLayout->addWidget(pulseWidth, 4, 1);
    VoltageGridLayout->addWidget(labelRatio, 5, 0);
    VoltageGridLayout->addWidget(ratio, 5, 1);

    QWidget* tempWidget = new QWidget();
    tempWidget->setLayout(TempGridLayout);
    QWidget* magWidget = new QWidget();
    magWidget->setLayout(MagGridLayout);
    QWidget* rotWidget = new QWidget();
    rotWidget->setLayout(RotGridLayout);
    QWidget* chamberWidget = new QWidget();
    chamberWidget->setLayout(ChamberGridLayout);
    QWidget* voltageWidget = new QWidget();
    voltageWidget->setLayout(VoltageGridLayout);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(tempWidget);
    mainLayout->addWidget(magWidget);
    mainLayout->addWidget(rotWidget);
    mainLayout->addWidget(chamberWidget);
    mainLayout->addWidget(voltageWidget);
    setLayout(mainLayout);
}
