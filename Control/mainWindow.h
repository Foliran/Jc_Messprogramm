#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <vector>
#include <QMainWindow>
#include <QCloseEvent>
#include <QCheckBox>
#include <QPushButton>
#include "../ControlCore/measurementsmanager.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QPlainTextEdit;
class QSessionManager;
class MeasSeqJc;
//class MeasurementSequence;
class DataPoint;
class GraphDiagram;
class PpmsSimulation;
class KeithleySimulation;
class PpmsWidget;
class MeasurementsTable;
//class GraphWidget;
//class OpenFileWindow;

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void closeEvent(QCloseEvent* event) override;

private slots:
    void onStartMessungButton();
    void onStartMultiMessungButton();
    void onOpenFileButton();
    void onCreateMeasurement(std::vector<std::shared_ptr<const MeasSeqJc>> mSeq);
    void onStartMeasurement(std::shared_ptr<const MeasSeqJc> mSeq);
    void onSetSampleStage(bool rotator);
    void onNewData(std::shared_ptr<const DataPoint> datapoint);
    void onNewMeasurementState(MeasurementsManager::State newState);
    void onNewTempSP(double temp, double rate);
    void onNewCurrentValues(double curr, double volt);
    void onNewCurrentSP(double currentSP);
    void onNewRatio(double r);
    void onNewPulseWidth(double pWidth);
    void onNewMagSP(double magField, double magRate);
    void onNewAngleSP(double angle);
    void onNewRotState(bool rotActive);
    void onNewErrorMessage(QString errormessagePpms);
    void onLogXAxis(int state);
    void onLogYAxis(int state);
    void onSkipButton();
    void onPauseButton();

private:
    void setupUi();
    void createStatusBar();
    void createActions();
    void createQLineDiagramm();
    void createRotatorButton();

    GraphDiagram* graph;
    MeasurementsManager* MeasManager;
    MeasurementsManager::State MeasManagerState;
    MeasurementsManager::State StateBeforePause;
    PpmsWidget* ppmsWidget;
    QWidget* mainLayoutWidget;
    MeasurementsTable* mTable;
    QCheckBox* rotCheckBox;
    QCheckBox* logXAxis;
    QCheckBox* logYAxis;
    QPushButton *pause;
    QPushButton *skip;
};
#endif
