#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "../Core/datafile.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QString filename;
    std::shared_ptr<Datafile> datafile = std::make_shared<Datafile>();
    Ui::MainWindow *ui;

private slots:
    void on_TextSuche_clicked();
    void on_DialogOpen_clicked();
};

#endif // MAINWINDOW_H
