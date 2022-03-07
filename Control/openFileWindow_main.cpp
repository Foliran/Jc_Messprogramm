#include "openfilewindow.h"

#include <QApplication>

int main2(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenFileWindow w;
    w.show();
    return a.exec();
}
