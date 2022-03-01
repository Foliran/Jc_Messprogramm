#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QRadioButton>

//fertig

//Internal Classes
class MeasSeqJc;
class MeasurementSequence;
class QDoubleSpinBox;
class QLineEdit;

class StartDialog : public QDialog
{
    Q_OBJECT

signals:
    void createMeasurement(std::vector <std::shared_ptr<const MeasurementSequence>>&);

public:
    explicit StartDialog(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    void accept() override;

private:
    void setupUI();
    QWidget* widgetJc;
    std::vector <std::shared_ptr<const MeasurementSequence>> createSequence() const;

    //Jc
    QLineEdit* sampleNameJc;
    QDoubleSpinBox* tempJc;
    QDoubleSpinBox* magneticFieldJc;
    QDoubleSpinBox* currentStartJc;
    QDoubleSpinBox* currentEndJc;
    QDoubleSpinBox* currentRateJc;
    QDoubleSpinBox* coilAngleJc;
    QDoubleSpinBox* pulseWidth;
    QDoubleSpinBox* ratio;
};

#endif // STARTDIALOG_H
