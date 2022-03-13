#include "openfilewindow.h"
#include "ui_openfilewindow.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>

OpenFileWindow::OpenFileWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFileWindow)
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
    filename = ui->insertFilename->displayText();
    qDebug() << filename;
}
