#ifndef STARTDIALOGMULTI_H
#define STARTDIALOGMULTI_H

#include <QDialog>
#include <QButtonGroup>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>

//fertig

//Internal Classes
class MeasSeqJc;
//class MeasurementSequence;
class QDoubleSpinBox;
class QLineEdit;

class StartDialogMulti : public QDialog
{
    Q_OBJECT

signals:
    void createMeasurement(std::vector <std::shared_ptr<const MeasSeqJc>>&);
private slots:
    void adjustCurrent();

public:
    explicit StartDialogMulti(QWidget* parent = nullptr);
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
    QDoubleSpinBox* startTempJc;
    QDoubleSpinBox* endTempJc;
    QDoubleSpinBox* tempRateJc;
    QDoubleSpinBox* magneticFieldJc;
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

#endif // STARTDIALOGMULTI_H
