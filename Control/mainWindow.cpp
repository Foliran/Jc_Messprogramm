#include <QtWidgets>
#include <memory>
#include <QDebug>

//Internal Classes
#include "mainWindow.h"
#include "../ControlCore/measurementsmanager.h"
#include "../Core/measurementsequence.h"
#include "../Core/measseqjc.h"
#include "../Core/datapoint.h"
#include "openfilewindow.h"
#include "startdialog.h"
#include "startdialogmulti.h"
#include "startdialogmulti_b.h"
#include "graphdiagram.h"
#include "ppmswidget.h"
#include "measurementstable.h"
#include "QDialog"

#include "../Instruments/ppmsinstrument.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , graph(new GraphDiagram(this))
    //, graphwidget(new GraphWidget(this))
    , MeasManager(new MeasurementsManager())
    , MeasManagerState(MeasurementsManager::State::Idle)
    , ppmsWidget(new PpmsWidget())
    , mainLayoutWidget(new QWidget())
    , mTable(new MeasurementsTable())
    , rotCheckBox(nullptr)
    , logXAxis(nullptr)
    , logYAxis(nullptr)
    , waitingTime(nullptr)
{
    createRotatorButton();
    setupUi();
    createStatusBar();
    createActions();
    createQLineDiagramm();
    setCentralWidget(mainLayoutWidget);

    connect(MeasManager, &MeasurementsManager::startNewMeasurement,
        this, &MainWindow::onStartMeasurement);
    connect(MeasManager, &MeasurementsManager::newData,
        this, &MainWindow::onNewData);
    connect(MeasManager, &MeasurementsManager::newState,
        this, &MainWindow::onNewMeasurementState);
    connect(MeasManager, &MeasurementsManager::newTempSP,
        this, &MainWindow::onNewTempSP);
    connect(MeasManager, &MeasurementsManager::newCurrentValues,
        this, &MainWindow::onNewCurrentValues);
    connect(MeasManager, &MeasurementsManager::newCurrentSetpoint,
        this, &MainWindow::onNewCurrentSP);
    connect(MeasManager, &MeasurementsManager::newRatio,
        this, &MainWindow::onNewRatio);
    connect(MeasManager, &MeasurementsManager::newPulseWidth,
        this, &MainWindow::onNewPulseWidth);
    connect(MeasManager, &MeasurementsManager::newMagSP,
        this, &MainWindow::onNewMagSP);
    connect(MeasManager, &MeasurementsManager::newAngleSP,
        this, &MainWindow::onNewAngleSP);
    connect(MeasManager, &MeasurementsManager::newRotstate,
        this, &MainWindow::onNewRotState);
    connect(MeasManager, &MeasurementsManager::newErrorMessage,
        this, &MainWindow::onNewErrorMessage);
    connect(rotCheckBox, &QCheckBox::clicked,
        this, &MainWindow::onSetSampleStage);
    connect(shutdown, &QCheckBox::stateChanged, this, &MainWindow::onShutdown);
    connect(MeasManager, &MeasurementsManager::resetGraph, this, &MainWindow::onResetGraph);
    connect(logXAxis, &QCheckBox::stateChanged, this, &MainWindow::onLogXAxis);
    connect(logYAxis, &QCheckBox::stateChanged, this, &MainWindow::onLogYAxis);
    connect(pause, &QPushButton::clicked, this, &MainWindow::onPauseButton);
    connect(skip, &QPushButton::clicked, this, &MainWindow::onSkipButton);
    connect(waitingTime, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::waitingTimeChanged);
    waitingTimeChanged();
    MeasManager->openDevice();
}

MainWindow::~MainWindow()
{
    delete MeasManager;
}

QSize MainWindow::sizeHint() const
{
    return QSize(1600, 1600);
}

QSize MainWindow::minimumSizeHint() const
{
    return QSize(1000, 400);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Quit?",
        tr("Are you sure?\n"),
        QMessageBox::No | QMessageBox::Yes,
        QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes)
    {
        event->ignore();
    }
    else
    {
        event->accept();
    }
}

void MainWindow::setupUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* GraphandList = new QHBoxLayout();
    QVBoxLayout* listandRot = new QVBoxLayout();
    QVBoxLayout* Rot = new QVBoxLayout();

    //Widgets for the temperature waiting time
    waitingTime = new QDoubleSpinBox();
    waitingTime->setRange(0, 1000);
    waitingTime->setDecimals(0);
    waitingTime->setValue(30);

    QLabel *waitingTimeLabel = new QLabel();
    waitingTimeLabel->setText("Time to wait for temp.:");
    QHBoxLayout *timeLayout = new QHBoxLayout();
    timeLayout->addWidget(waitingTimeLabel);
    timeLayout->addWidget(waitingTime);
    QWidget *timeWidget = new QWidget();
    timeWidget->setLayout(timeLayout);

    Rot->addSpacing(5);
    Rot->addWidget(timeWidget);
    //TODO: Alles was mit dem Rotator zu tun hat, kann raus
    //Rot->addWidget(rotCheckBox);
    Rot->addWidget(shutdown);
    Rot->addWidget(logXAxis);
    Rot->addWidget(logYAxis);
    listandRot->addLayout(Rot);
    listandRot->addWidget(mTable);
    listandRot->addWidget(pause);
    listandRot->addWidget(skip);
    GraphandList->addWidget(graph);
    GraphandList->addLayout(listandRot);
    mTable->setMaximumWidth(250);
    mainLayout->addLayout(GraphandList);
    mainLayout->addSpacing(10);
    ppmsWidget->setMaximumHeight(200);
    ppmsWidget->height();
    mainLayout->addWidget(ppmsWidget);
    mainLayoutWidget->setLayout(mainLayout);
}

void MainWindow::createActions()
{
    //QMenu* fileMenu = menuBar()->addMenu(tr("&Measurement"));
    QToolBar* fileToolBar = addToolBar(tr("New Measurement"));
    fileToolBar->setIconSize(QSize(45, 30));
    const QIcon measurementIcon = QIcon::fromTheme("MessungIcon", QIcon(":/Icons/Icons/Jc.svg"));
    const QIcon measurementIconMulti = QIcon::fromTheme("MessungIconMulti", QIcon(":/Icons/Icons/Jc_von_T_at_B.svg"));
    const QIcon measurementIconMulti_B = QIcon::fromTheme("MessungIconMulti", QIcon(":/Icons/Icons/Jc_von_B_at_T.svg"));
    const QIcon openFileIcon = QIcon::fromTheme("FileIcon", QIcon(":/Icons/Icons/open_file.png"));
    QAction* messungStarten = new QAction(measurementIcon, tr("&New single measurement"), this);
    QAction* messungStartenMulti = new QAction(measurementIconMulti, tr("&New Jc(T@B) measurement"), this);
    QAction* messungStartenMulti_B = new QAction(measurementIconMulti_B, tr("&New Jc(B@T) measurement"), this);
    QAction* openFile = new QAction(openFileIcon, tr("&open File"), this);
    messungStarten->setStatusTip(tr("Create a new measurement"));
    messungStartenMulti->setStatusTip(tr("Create a series of J_c(T @B) measurements"));
    messungStartenMulti_B->setStatusTip(tr("Create a series of J_c(B @T) measurements"));
    openFile->setStatusTip(tr("Show an old Measurement"));
    connect(messungStarten, &QAction::triggered, this, &MainWindow::onStartMessungButton);
    connect(messungStartenMulti, &QAction::triggered, this, &MainWindow::onStartMultiMessungButton);
    connect(messungStartenMulti_B, &QAction::triggered, this, &MainWindow::onStartMultiBMessungButton);
    connect(openFile, &QAction::triggered, this, &MainWindow::onOpenFileButton);
    fileToolBar->addAction(messungStarten);
    fileToolBar->addAction(messungStartenMulti);
    fileToolBar->addAction(messungStartenMulti_B);
    fileToolBar->addAction(openFile);
}

void MainWindow::createRotatorButton()
{
    shutdown = new QCheckBox();
    shutdown->setText("Shutdown at the end of the measurements");

    //rotCheckBox = new QCheckBox("C&ase sensitive", this);
    //rotCheckBox->setText("Rotator On/Off");
    logXAxis = new QCheckBox();
    logXAxis->setText("Logarithmic axis x");
    logYAxis = new QCheckBox();
    logYAxis->setText("Logarithmic axis y");

    pause = new QPushButton("Pause");
    skip = new QPushButton("Skip current measurement");
}

void MainWindow::onLogXAxis(int state) {
    graph->setAxisLogarithmic(state, 0);
}

void MainWindow::onLogYAxis(int state) {
    graph->setAxisLogarithmic(state, 1);
}

void MainWindow::onSkipButton() {
    MeasManagerState = MeasurementsManager::State::SkipMeasurement;
    MeasManager->measurementState = MeasManagerState;
    graph->MeasurementState(MeasManagerState);
}

void MainWindow::onPauseButton() {
    if(pause->text() == "Pause") {
        StateBeforePause = MeasManagerState;
        MeasManagerState = MeasurementsManager::State::PauseMeasurement;
        pause->setText("Go on");
    } else if(pause->text() == "Go on") {
        MeasManagerState = StateBeforePause;
        pause->setText("Pause");
    }
    MeasManager->measurementState = MeasManagerState;
    graph->MeasurementState(MeasManagerState);
}

void MainWindow::onShutdown() {
    if(shutdown->isChecked())
    {
        MeasManager->goToShutdown = true;
    } else if(!shutdown->isChecked()) {
        MeasManager->goToShutdown = false;
    }
}

void MainWindow::onStartMessungButton()
{
    StartDialog* startDialog = new StartDialog(this);
    connect(startDialog, &StartDialog::createMeasurement,
        this, &MainWindow::onCreateMeasurement);
    startDialog->show();
}

void MainWindow::onStartMultiMessungButton()
{
    StartDialogMulti* start = new StartDialogMulti(this);
    connect(start, &StartDialogMulti::createMeasurement,
        this, &MainWindow::onCreateMeasurement);
    start->show();
}

void MainWindow::onStartMultiBMessungButton()
{
    StartDialogMulti_B* start = new StartDialogMulti_B(this);
    connect(start, &StartDialogMulti_B::createMeasurement,
        this, &MainWindow::onCreateMeasurement);
    start->show();
}

void MainWindow::onOpenFileButton()
{
    OpenFileWindow *openfile = new OpenFileWindow();
    openfile->show();
}

void MainWindow::onCreateMeasurement(std::vector<std::shared_ptr<const MeasSeqJc>> mSeq)
{
    MeasManager->appendMeasurement(mSeq);
    mTable->newMeasurement(mSeq);
}

void MainWindow::onStartMeasurement(std::shared_ptr<const MeasSeqJc> mSeq)
{
    //graph->setStaticValues(mSeq);
    mTable->activeMeasurement(mSeq);
}

void MainWindow::onResetGraph(std::shared_ptr<const MeasSeqJc> mSeq) {
    graph->setStaticValues(mSeq);
}

void MainWindow::onSetSampleStage(bool rotator)
{
    MeasManager->rotatorState(rotator);

    if(rotator == true)
    {
        rotCheckBox->setText("Rotator On");
    }
    else
    {
        rotCheckBox->setText("Rotator Off");
    }
}

void MainWindow::onNewData(std::shared_ptr<const DataPoint> datapoint)
{
    ppmsWidget->newData(datapoint);
    graph->appendDataPoint(datapoint);
}

void MainWindow::onNewMeasurementState(MeasurementsManager::State newState)
{
    MeasManagerState = newState;
    graph->MeasurementState(MeasManagerState);
}

void MainWindow::onNewTempSP(double temp, double rate)
{
    ppmsWidget->newTempSP(temp, rate);
}

void MainWindow::onNewCurrentValues(double curr, double volt)
{
    ppmsWidget->newCurrentValues(curr, volt);
}

void MainWindow::onNewCurrentSP(double setpoint)
{
    ppmsWidget->newCurrentSP(setpoint);
}

void MainWindow::onNewRatio(double r)
{
    ppmsWidget->newRatio(r);
}

void MainWindow::onNewPulseWidth(double pWidth)
{
    ppmsWidget->newPulseWidth(pWidth);
}

void MainWindow::onNewMagSP(double magField, double magRate)
{
    ppmsWidget->newMagSP(magField, magRate);
}

void MainWindow::onNewAngleSP(double angle)
{
    ppmsWidget->newAngleSP(angle);
}

void MainWindow::onNewRotState(bool rotActive)
{
    Qt::CheckState rotState = rotActive ? Qt::CheckState::Checked : Qt::CheckState::Unchecked;
    rotCheckBox->setCheckState(rotState);
}

void MainWindow::onNewErrorMessage(QString errormessage)
{
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setAttribute(Qt::WA_DeleteOnClose); //makes sure the msgbox is deleted automatically when closed
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setWindowTitle(tr("Error"));
    msgBox->setText(errormessage);
    msgBox->setModal(false); // if you want it non-modal
    msgBox->open(this, SLOT(msgBoxClosed(QAbstractButton*)));
}


void MainWindow::createQLineDiagramm()
{
    graph->createQlineDiagramm();
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::waitingTimeChanged() {
    MeasManager->setWaitingTime((int)waitingTime->value());
}
