#include <QtWidgets>
#include <memory>
#include <QDebug>

//Internal Classes
#include "mainWindow.h"
#include "../ControlCore/measurementsmanager.h"
#include "../Core/measurementsequence.h"
#include "../Core/datapoint.h"
#include "graphwidget.h"
//#include "openfilewindow.h"
#include "startdialog.h"
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

    MeasManager->openDevice();
}

MainWindow::~MainWindow()
{
    delete MeasManager;
}

QSize MainWindow::sizeHint() const
{
    return QSize(1600, 1200);
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
    QHBoxLayout* Rot = new QHBoxLayout();
    Rot->addSpacing(12);
    Rot->addWidget(rotCheckBox);
    listandRot->addLayout(Rot);
    listandRot->addWidget(mTable);
    GraphandList->addWidget(graph);
    GraphandList->addLayout(listandRot);
    mTable->setMaximumWidth(250);
    mainLayout->addLayout(GraphandList);
    mainLayout->addSpacing(10);
    ppmsWidget->setMaximumHeight(180);
    ppmsWidget->height();
    mainLayout->addWidget(ppmsWidget);
    mainLayoutWidget->setLayout(mainLayout);
}

void MainWindow::createActions()
{
    //QMenu* fileMenu = menuBar()->addMenu(tr("&Measurement"));
    QToolBar* fileToolBar = addToolBar(tr("New Measurement"));
    const QIcon measurementIcon = QIcon::fromTheme("MessungIcon", QIcon(":/Icons/Icons/Jc.svg"));
    const QIcon openFileIcon = QIcon::fromTheme("FileIcon", QIcon(":/Icons/Icons/StartButton.png"));
    QAction* messungStarten = new QAction(measurementIcon, tr("&New Measurement"), this);
    QAction* openFile = new QAction(openFileIcon, tr("&open File"), this);
    messungStarten->setStatusTip(tr("Create a new measurement"));
    openFile->setStatusTip(tr("Show an old Measurement"));
    connect(messungStarten, &QAction::triggered,
        this, &MainWindow::onStartMessungButton);
    connect(openFile, &QAction::triggered,
        this, &MainWindow::onOpenFileButton);
    //fileMenu->addAction(messungStarten);
    //fileMenu->addAction(openFile);
    fileToolBar->addAction(messungStarten);
    fileToolBar->addAction(openFile);
}

void MainWindow::createRotatorButton()
{
    rotCheckBox = new QCheckBox("C&ase sensitive", this);
    rotCheckBox->setText("Rotator On/Off");
}

void MainWindow::onStartMessungButton()
{
    StartDialog* startDialog = new StartDialog(this);
    connect(startDialog, &StartDialog::createMeasurement,
        this, &MainWindow::onCreateMeasurement);
    startDialog->show();
}

void MainWindow::onOpenFileButton()
{
    //TODO: Einbundung von openFileWindow
    //OpenFileWindow* ofw = new OpenFileWindow(this);
    //ofw->show();
}

void MainWindow::onCreateMeasurement(std::vector<std::shared_ptr<const MeasurementSequence>> mSeq)
{
    MeasManager->appendMeasurement(mSeq);
    mTable->newMeasurement(mSeq);
}

void MainWindow::onStartMeasurement(std::shared_ptr<const MeasurementSequence> mSeq)
{
    qDebug() << "MainWindow::onStartMeasurement";
    graph->setStaticValues(mSeq);
    mTable->activeMeasurement(mSeq);
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
    //qDebug() << "MainWindow::onNewData";
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

void MainWindow::onNewErrorMessage(QString errormessagePpms)
{
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setAttribute(Qt::WA_DeleteOnClose); //makes sure the msgbox is deleted automatically when closed
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setWindowTitle(tr("Error"));
    msgBox->setText(errormessagePpms);
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


