#include "openfilewindow.h"
#include "ui_openfilewindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <vector>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>

QT_CHARTS_USE_NAMESPACE

OpenFileWindow::OpenFileWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFileWindow),
    series(new QLineSeries)
{
    ui->setupUi(this);
    connect(ui->openFile, &QPushButton::clicked, this, &OpenFileWindow::openFile_clicked);
}

OpenFileWindow::~OpenFileWindow()
{
    delete ui;
}

void OpenFileWindow::openFile_clicked()
{
    std::vector<double> current;
    std::vector<double> voltage;
    qDebug() << "Current path is" << QDir::currentPath();
    filename = QDir::currentPath() + "/" + QString::fromStdString("Messergebnisse/") + ui->insertFilename->displayText();
    qDebug() << "Filename is " + filename;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox* msgBox = new QMessageBox(this);
        msgBox->setAttribute(Qt::WA_DeleteOnClose); //makes sure the msgbox is deleted automatically when closed
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setWindowTitle(tr("Error"));
        msgBox->setText("Datei kann nicht geöffnet werden.");
        msgBox->setModal(false); // if you want it non-modal
        msgBox->open(this, SLOT(msgBoxClosed(QAbstractButton*)));
        return;
    }
    QTextStream stream(&file);
    int lineNumber = 0;
    while(!stream.atEnd())
    {
        if (lineNumber >= 3)
        {
            QString line = file.readLine();
            QString StringCurr = line.split(QRegExp("\\s+"))[5];
            QString StringVolt = line.split(QRegExp("\\s+"))[6];
            series->append(StringCurr.toDouble(), StringVolt.toDouble());
        }
        lineNumber++;
    }

    //Diagramm erstellen
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Current in Ampere");
    QValueAxis *axisY= new QValueAxis;
    axisY->setTitleText("Spannung in Volt");
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    QPen pen(QRgb(0x000000));
    pen.setWidth(2);
    series->setPen(pen);
    QChartView *chartView = new QChartView(chart);
    chartView->show();
    chartView->resize(1000,800);

}
