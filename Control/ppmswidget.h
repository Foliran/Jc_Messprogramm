#ifndef PPPMSWIDGET_H
#define PPPMSWIDGET_H

//fertig

#include <QWidget>

//Internal Classes
class DataPoint;
class QLabel;
class InstrumentManager;

class PpmsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PpmsWidget(QWidget* parent = nullptr);


    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void newData(std::shared_ptr<const DataPoint> dpoint);
    void newMagSP(double magField, double magRate);
    void newAngleSP(double angle);
    void newTempSP(double temp, double rate);
    void newCurrentValues(double curr, double volt);
    void newCurrentSP(double setpoint);
    void newPulseWidth(double value);
    void newRatio(double value);

private:
    void setupUI();
    //tempBlock
    QLabel* tempSetPoint;
    QLabel* tempLive;
    QLabel* tempRate;
    QLabel* tempStatus;
    //QLabel* userTemp;

    //MagBlock
    QLabel* magSetPoint;
    QLabel* magFieldLive;
    QLabel* magRate;
    QLabel* magStatus;

    /*
    //RotationBlock
    QLabel* rotSetPoint;
    QLabel* rotLive;
    QLabel* rotStatus;
    */

    //Chamber
    QLabel* chamberStatus;
    QLabel* chamberLevel;
    QLabel* sampleSpacePressure;

    //keithley 2651A
    QLabel* currentEndpoint;
    QLabel* currentRate;
    QLabel* currentLive;

    //keithley dmm 6500
    QLabel* voltageLive;
    QLabel* pulseWidth;
    QLabel* ratio;

    QString tempStatStr;
    QString magStatStr;
    QString chambStatStr;
    QString rotStatStr;


};

#endif // PPPMSWIDGET_H
