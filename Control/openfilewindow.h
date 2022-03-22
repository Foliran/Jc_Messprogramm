#ifndef OPENFILEWINDOW_H
#define OPENFILEWINDOW_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class OpenFileWindow;
}

class OpenFileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OpenFileWindow(QWidget *parent = nullptr);
    ~OpenFileWindow();

private slots:
    void openFile_clicked();

private:
    Ui::OpenFileWindow *ui;
    QString filename;
    QLineSeries *series;
};

#endif // OPENFILEWINDOW_H
