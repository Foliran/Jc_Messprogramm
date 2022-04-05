#include "graphdiagram.h"

#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <memory>
#include <QDebug>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>
#include <QtWidgets/QVBoxLayout>

//Internal Classes
#include "../Core/datapoint.h"
#include "../Core/measurementsequence.h"
#include "../Core/measseqjc.h"
#include "../ControlCore/measurementsmanager.h"
QT_CHARTS_USE_NAMESPACE


GraphDiagram::GraphDiagram(QWidget* parent)
    :QWidget(parent)
    , filename1("filename")
    , currentMin(0)
    , currentMax(0)
    , voltMin(0.0)
    , voltMax(0.000001)
    , graphMeas(false)
    , series(new QLineSeries())
    , chart(new QChart())
    , chartView(new QChartView(chart))
    , axisX(new QValueAxis)
    , axisY(new QValueAxis)
    , axisXLog(new QLogValueAxis)
    , axisYLog(new QLogValueAxis)
    , measSeq(nullptr)
    , measurementState(MeasurementsManager::State::Idle)
{
    axisXLog->setBase(10);
    axisXLog->setMinorTickCount(10);
    axisYLog->setBase(10);
    axisYLog->setMinorTickCount(10);
}

void GraphDiagram::appendDataPoint(std::shared_ptr<const DataPoint> datapoint)
{
        //qDebug() << "GraphDiagram::appendDataPoint";
    if (measurementState == MeasurementsManager::State::ApproachEndJc)
    {
        // Range of Y-Axis
        if (voltMin == 10) { voltMin = datapoint->getKeithleyData()->getVoltage(); }
        if (voltMax == 10) { voltMin = datapoint->getKeithleyData()->getVoltage(); }
        if (voltMin > datapoint->getKeithleyData()->getVoltage()) { voltMin = 0.9*datapoint->getKeithleyData()->getVoltage(); }
        if (voltMax < datapoint->getKeithleyData()->getVoltage()) { voltMax = 1.1*datapoint->getKeithleyData()->getVoltage(); }
        axisY->setRange(voltMin, voltMax);
        axisYLog->setRange(voltMin, voltMax);
        series->append(datapoint->getKeithleyData()->getCurrent(), datapoint->getKeithleyData()->getVoltage());

    }
}

void GraphDiagram::MeasurementState(MeasurementsManager::State newState)
{
    measurementState = newState;
}

QSize GraphDiagram::sizeHint() const
{
    return QSize(700, 500);
}

QSize GraphDiagram::minimumSizeHint() const
{
    return QSize(300, 200);
}

void GraphDiagram::setStaticValues(std::shared_ptr<const MeasurementSequence> mSeq)
{
    series->clear();
    measSeq = mSeq;
    auto mSeqJc = std::dynamic_pointer_cast <const MeasSeqJc> (measSeq);

    if (mSeqJc != nullptr)
    {
        axisX->setTitleText("Current in Ampere");
        axisY->setTitleText("Voltage in Volt");
        if (mSeqJc->getCurrentStart() <= mSeqJc->getCurrentEnd())
        {
            axisX->setRange(mSeqJc->getCurrentStart(), mSeqJc->getCurrentEnd()); //
        }
        else
        {
            axisX->setRange(mSeqJc->getCurrentEnd(), mSeqJc->getCurrentStart()); //mSeqJc->getCurrentEnd()
        }
        chart->setTitle("Jc Measurement " + mSeq->getFileName());
    }


}

void GraphDiagram::createQlineDiagramm()
{
    chart->legend()->hide();
    chart->addSeries(series);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    //font Size
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);

    // Dicke der Linie
    QPen pen(QRgb(0x000000));
    pen.setWidth(2);
    series->setPen(pen);
    // Animationen alle an, weil Animationen cool
    chart->setAnimationOptions(QChart::NoAnimation);

    //Durch Antialiasing passt sich chart an, wenn man größer kleiner macht (meine ich)
    //QChartView *chartView = new QChartView(chart_);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(chartView);

    setLayout(mainLayout);
}

void GraphDiagram::setAxisLogarithmic(int state, int chooseAxis){
    //chooseAxis = 0 -> x-Achse logarithmisch; chooseAxis = 1 -> y-Achse logarithmisch
    QAbstractAxis *removeAxis, *insertAxis;
    if(chooseAxis == 0)
    {
        if(state == Qt::Checked){
            removeAxis = axisX;
            insertAxis = axisXLog;
        }
        else { //
            removeAxis = axisXLog;
            insertAxis = axisX;
        }
        qDebug() << "insert " << insertAxis;
        qDebug() << "remove " << removeAxis;
        //set x-axis
        if(chart->axes(Qt::Horizontal).contains(removeAxis))
        {
            chart->removeAxis(removeAxis);
        }
        chart->addAxis(insertAxis, Qt::AlignBottom);
        for(auto serie: chart->series()){
            if(serie->attachedAxes().contains(removeAxis))
            {
                serie->detachAxis(removeAxis);
            }
            serie->attachAxis(insertAxis);
        }

    } else if (chooseAxis == 1) {
        if(state == Qt::Checked){
            removeAxis = axisY;
            insertAxis = axisYLog;
        }
        else { //
            removeAxis = axisYLog;
            insertAxis = axisY;
        }
        qDebug() << "insert " << insertAxis;
        qDebug() << "remove " << removeAxis;
        //set x-axis
        if(chart->axes(Qt::Vertical).contains(removeAxis))
        {
            chart->removeAxis(removeAxis);
        }
        chart->addAxis(insertAxis, Qt::AlignLeft);
        for(auto serie: chart->series()){
            if(serie->attachedAxes().contains(removeAxis))
            {
                serie->detachAxis(removeAxis);
            }
            serie->attachAxis(insertAxis);
        }

        for(auto i : chart->axes()) {qDebug() << i << " " << i->alignment();}
    }
}


