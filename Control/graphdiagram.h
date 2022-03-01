#ifndef GRAPHDIAGRAM_H
#define GRAPHDIAGRAM_H

#include <memory>
#include <QWidget>
#include <QtCharts>
#include <QtCharts/QValueAxis>

//Internal Classes
class DataPoint;
class MeasurementSequence;
class measSeqJc;
#include "../ControlCore/measurementsmanager.h"

class GraphDiagram : public QWidget
{
    Q_OBJECT
public:

    GraphDiagram(QWidget* parent = nullptr);
    void createQlineDiagramm();
    void appendDataPoint(std::shared_ptr<const DataPoint> datapoint);
    void MeasurementState(MeasurementsManager::State newState);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    QVector<double> current; // x-Achse
    QVector<double> volt; // y-Achse
    QString filename1;
    double currentMin;
    double currentMax;
    double voltMin;
    double voltMax;
    bool graphMeas;
    QLineSeries* series;
    QChart* chart;
    QChartView* chartView;
    QValueAxis* axisX;
    QValueAxis* axisY;

    std::shared_ptr <const MeasurementSequence> measSeq;
    MeasurementsManager::State measurementState;

public slots:
    void setStaticValues(std::shared_ptr<const MeasurementSequence> mSeq);

};

#endif
