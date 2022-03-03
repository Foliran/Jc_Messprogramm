/****************************************************************************
** Meta object code from reading C++ file 'mainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[31];
    char stringdata0[470];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 20), // "onStartMessungButton"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 19), // "onCreateMeasurement"
QT_MOC_LITERAL(4, 53, 56), // "std::vector<std::shared_ptr<c..."
QT_MOC_LITERAL(5, 110, 4), // "mSeq"
QT_MOC_LITERAL(6, 115, 18), // "onStartMeasurement"
QT_MOC_LITERAL(7, 134, 42), // "std::shared_ptr<const Measure..."
QT_MOC_LITERAL(8, 177, 16), // "onSetSampleStage"
QT_MOC_LITERAL(9, 194, 7), // "rotator"
QT_MOC_LITERAL(10, 202, 9), // "onNewData"
QT_MOC_LITERAL(11, 212, 32), // "std::shared_ptr<const DataPoint>"
QT_MOC_LITERAL(12, 245, 9), // "datapoint"
QT_MOC_LITERAL(13, 255, 21), // "onNewMeasurementState"
QT_MOC_LITERAL(14, 277, 26), // "MeasurementsManager::State"
QT_MOC_LITERAL(15, 304, 8), // "newState"
QT_MOC_LITERAL(16, 313, 11), // "onNewTempSP"
QT_MOC_LITERAL(17, 325, 4), // "temp"
QT_MOC_LITERAL(18, 330, 4), // "rate"
QT_MOC_LITERAL(19, 335, 18), // "onNewCurrentValues"
QT_MOC_LITERAL(20, 354, 4), // "curr"
QT_MOC_LITERAL(21, 359, 4), // "volt"
QT_MOC_LITERAL(22, 364, 10), // "onNewMagSP"
QT_MOC_LITERAL(23, 375, 8), // "magField"
QT_MOC_LITERAL(24, 384, 7), // "magRate"
QT_MOC_LITERAL(25, 392, 12), // "onNewAngleSP"
QT_MOC_LITERAL(26, 405, 5), // "angle"
QT_MOC_LITERAL(27, 411, 13), // "onNewRotState"
QT_MOC_LITERAL(28, 425, 9), // "rotActive"
QT_MOC_LITERAL(29, 435, 17), // "onNewErrorMessage"
QT_MOC_LITERAL(30, 453, 16) // "errormessagePpms"

    },
    "MainWindow\0onStartMessungButton\0\0"
    "onCreateMeasurement\0"
    "std::vector<std::shared_ptr<const MeasurementSequence> >\0"
    "mSeq\0onStartMeasurement\0"
    "std::shared_ptr<const MeasurementSequence>\0"
    "onSetSampleStage\0rotator\0onNewData\0"
    "std::shared_ptr<const DataPoint>\0"
    "datapoint\0onNewMeasurementState\0"
    "MeasurementsManager::State\0newState\0"
    "onNewTempSP\0temp\0rate\0onNewCurrentValues\0"
    "curr\0volt\0onNewMagSP\0magField\0magRate\0"
    "onNewAngleSP\0angle\0onNewRotState\0"
    "rotActive\0onNewErrorMessage\0"
    "errormessagePpms"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    1,   75,    2, 0x08 /* Private */,
       6,    1,   78,    2, 0x08 /* Private */,
       8,    1,   81,    2, 0x08 /* Private */,
      10,    1,   84,    2, 0x08 /* Private */,
      13,    1,   87,    2, 0x08 /* Private */,
      16,    2,   90,    2, 0x08 /* Private */,
      19,    2,   95,    2, 0x08 /* Private */,
      22,    2,  100,    2, 0x08 /* Private */,
      25,    1,  105,    2, 0x08 /* Private */,
      27,    1,  108,    2, 0x08 /* Private */,
      29,    1,  111,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    5,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   17,   18,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   20,   21,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   23,   24,
    QMetaType::Void, QMetaType::Double,   26,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::QString,   30,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onStartMessungButton(); break;
        case 1: _t->onCreateMeasurement((*reinterpret_cast< std::vector<std::shared_ptr<const MeasurementSequence> >(*)>(_a[1]))); break;
        case 2: _t->onStartMeasurement((*reinterpret_cast< std::shared_ptr<const MeasurementSequence>(*)>(_a[1]))); break;
        case 3: _t->onSetSampleStage((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->onNewData((*reinterpret_cast< std::shared_ptr<const DataPoint>(*)>(_a[1]))); break;
        case 5: _t->onNewMeasurementState((*reinterpret_cast< MeasurementsManager::State(*)>(_a[1]))); break;
        case 6: _t->onNewTempSP((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 7: _t->onNewCurrentValues((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 8: _t->onNewMagSP((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 9: _t->onNewAngleSP((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->onNewRotState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->onNewErrorMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
