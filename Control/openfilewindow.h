#ifndef OPENFILEWINDOW_H
#define OPENFILEWINDOW_H

#include <QDialog>
#include "../Core/datafile.h"

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
    Datafile *dfile;
};

#endif // OPENFILEWINDOW_H
