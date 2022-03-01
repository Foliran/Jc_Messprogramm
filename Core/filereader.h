#ifndef FILEREADER_H
#define FILEREADER_H

#include "Core_global.h"
#include <memory>
#include "datafile.h"
#include <QObject>

//fertig


class CORE_EXPORT FileReader : QObject
{
    Q_OBJECT
public:
    FileReader(Datafile& dfile);
    std::shared_ptr<Datafile> readFile();
private:
    Datafile dfile;
};

#endif
