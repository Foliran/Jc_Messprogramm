#ifndef OPENFILEWINDOW_H
#define OPENFILEWINDOW_H

#include <QMainWindow>
#include <QString>
#include <../Core/datafile.h>

namespace Ui {
class OpenFileWindow;
}

class OpenFileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OpenFileWindow(QWidget *parent = nullptr);
    ~OpenFileWindow();

private:
    Ui::OpenFileWindow *ui;

private slots:
    void on_TextSuche_clicked();
    void on_DialogOpen_clicked();

    QString filename;
    std::shared_ptr<Datafile> datafile = std::make_shared<Datafile>();
};

#endif // OPENFILEWINDOW_H
