#include "graphwidget.h"
#include "../Core/filereader.h"

#include <QString>
#include <QTextStream>
#include <QtWidgets\QDialog>
#include <QtWidgets\QFileDialog>
#include <QtWidgets\QMessageBox>
#include <QtWidgets\QApplication>
#include <QtWidgets/QMainWindow>
#include <QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <memory>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE;

GraphWidget::GraphWidget(Datafile& cfile)
    :cfile(cfile)
{

}

void GraphWidget::createDatapoints(std::shared_ptr<Datafile> datafile)
{
    currents = datafile->getCurrent();
    volts = datafile->getVoltage();
    filename1 = cfile.getFileName();
}


void GraphWidget::createQlineDiagramm()
{
    QVector<double> StromVektordouble = currents;
    QVector<double> SpannungVektordouble = volts;
    QString filename_2 = "Jc-Messung: ";
    QString filename = filename1;
    QString filename_3 = filename.section('/', -1);
    filename_2.append(filename_3);

    //erstelle das LinienDiagramm
    QLineSeries* series = new QLineSeries();
    // Warum hier bis -2?
    //TODO: Ausprobieren, ob bis -1 auch geht
    //Ja, -1 geht bisher auch, falls mal irgendwann das Programm abstürzt könnte es hieran liegen
    for (int j = 0; j < StromVektordouble.length() - 1; j++)
    {
        series->append(StromVektordouble[j], SpannungVektordouble[j]);
    }

    //chart des Diagramms
    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);

    //X-Achse plus Beschreibung
    QValueAxis* axisX = new QValueAxis;
    axisX->setTitleText("Stromstärke in Ampere");
    //Y-Achse plus Beschreibung
    QValueAxis* axisY = new QValueAxis;
    axisY->setTitleText("Spannung in Volt");
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    //font Size
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    // Titel von oben einsetzen
    chart->setTitle(filename_2);

    // Dicke der Linie
    QPen pen(QRgb(0x000000));
    pen.setWidth(2);
    series->setPen(pen);
    // Animationen alle an, weil Animationen cool
    chart->setAnimationOptions(QChart::AllAnimations);

    //Durch Antialiasing passt sich chart an, wenn man größer kleiner macht (meine ich)
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    // ich meine das dieser Befehl, die Chart im neuen Fenster öffnet, was danach noch auf die richtige Größe gesetzt wird
    chartView->show();
    chartView->resize(1000, 800);
}
