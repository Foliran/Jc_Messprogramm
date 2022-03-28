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
            axisX->setRange(0, mSeqJc->getCurrentEnd()); //mSeqJc->getCurrentStart()
        }
        else
        {
            axisX->setRange(0, 0.01); //mSeqJc->getCurrentEnd()
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

void GraphDiagram::setAxisLogarithmic(int state){
    QAbstractAxis *removeAxisX, *insertAxisX,  *removeAxisY, *insertAxisY;
    if(state == Qt::Checked){
        removeAxisX = axisX;
        insertAxisX = axisYLog;
        removeAxisY = axisY;
        insertAxisY = axisYLog;
    }
    else if (state == Qt::Unchecked){
        removeAxisX = axisXLog;
        insertAxisX = axisX;
        removeAxisY = axisYLog;
        insertAxisY = axisY;
    }
    //set x-axis
    if(chart->axes(Qt::Horizontal).contains(removeAxisX))
        chart->removeAxis(removeAxisX);
    chart->addAxis(insertAxisX, Qt::AlignBottom);

    for(auto serie: chart->series()){
        if(serie->attachedAxes().contains(removeAxisX))
            serie->detachAxis(removeAxisX);
        serie->attachAxis(insertAxisX);
    }

    //set y axis
    if(chart->axes(Qt::Vertical).contains(removeAxisY))
        chart->removeAxis(removeAxisY);
    chart->addAxis(insertAxisY, Qt::AlignLeft);

    for(auto serie: chart->series()){
        if(serie->attachedAxes().contains(removeAxisY))
            serie->detachAxis(removeAxisY);
        serie->attachAxis(insertAxisY);
    }
}


