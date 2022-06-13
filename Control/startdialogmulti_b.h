#ifndef STARTDIALOGMULTI_B_H
#define STARTDIALOGMULTI_B_H

#include <QDialog>
#include <QButtonGroup>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>

//fertig

//Internal Classes
class MeasSeqJc;
class QDoubleSpinBox;
class QLineEdit;

class StartDialogMulti_B : public QDialog
{
    Q_OBJECT

signals:
    void createMeasurement(std::vector <std::shared_ptr<const MeasSeqJc>>&);
private slots:
    void adjustCurrent();

public:
    explicit StartDialogMulti_B(QWidget* parent = nullptr);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    void accept() override;

private:
    void setupUI();
    QWidget* widgetJc;
    std::vector <std::shared_ptr<const MeasSeqJc>> createSequence() const;

    //Jc
    QCheckBox* reversedPulse;
    QCheckBox* logSteps;
    QLineEdit* sampleNameJc;
    QDoubleSpinBox* startMagFieldJc;
    QDoubleSpinBox* endMagFieldJc;
    QDoubleSpinBox* fieldRateJc;
    QDoubleSpinBox* temperatureJc;
    QDoubleSpinBox* currentStartJc;
    QDoubleSpinBox* currentEndJc;
    QDoubleSpinBox* currentRateJc;
    QDoubleSpinBox* voltageCriterion;
    QDoubleSpinBox* pulseWidth;
    QDoubleSpinBox* timeBetweenPulses;
    QDoubleSpinBox* nPulses;
    QDoubleSpinBox* ratio;

    QLabel* labelCurrentRate;
};

#endif // STARTDIALOGMULTI_B_H
