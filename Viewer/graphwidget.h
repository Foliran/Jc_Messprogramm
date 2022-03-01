#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

//Eigene Klassen
#include "../Core/datafile.h"

#include <memory>
#include <QWidget>


class GraphWidget
{
public:
    GraphWidget(Datafile& cfile);
    void createQlineDiagramm();
    void createDatapoints(std::shared_ptr<Datafile> datafile);
private:
    Datafile cfile;

    QVector<double> volts;
    QVector<double> currents;
    QString filename1;
    //std::shared_ptr<Datafile> datafile = std::make_shared<Datafile>();
};

#endif
