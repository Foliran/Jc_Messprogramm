#ifndef MEASUREMENTSTABLE_H
#define MEASUREMENTSTABLE_H
#include <QWidget>
#include <QListWidget>

//fertig

//Internal Classes
//class MeasurementSequence;
class MeasSeqJc;

class MeasurementsTable : public QWidget
{
    Q_OBJECT

public:
    explicit MeasurementsTable(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void newMeasurement(const std::vector<std::shared_ptr<const MeasSeqJc>>& mSeq);
    void activeMeasurement(const std::shared_ptr<const MeasSeqJc> mesSeq);

private:
    void setupUI();
    QListWidget* listWidget;
    std::vector<std::shared_ptr<const MeasSeqJc>> vecSeq;
};

#endif
