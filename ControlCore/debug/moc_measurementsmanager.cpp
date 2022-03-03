/****************************************************************************
** Meta object code from reading C++ file 'measurementsmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../measurementsmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'measurementsmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MeasurementsManager_t {
    QByteArrayData data[32];
    char stringdata0[450];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MeasurementsManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MeasurementsManager_t qt_meta_stringdata_MeasurementsManager = {
    {
QT_MOC_LITERAL(0, 0, 19), // "MeasurementsManager"
QT_MOC_LITERAL(1, 20, 7), // "newData"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 32), // "std::shared_ptr<const DataPoint>"
QT_MOC_LITERAL(4, 62, 19), // "startNewMeasurement"
QT_MOC_LITERAL(5, 82, 42), // "std::shared_ptr<const Measure..."
QT_MOC_LITERAL(6, 125, 8), // "newState"
QT_MOC_LITERAL(7, 134, 26), // "MeasurementsManager::State"
QT_MOC_LITERAL(8, 161, 9), // "newTempSP"
QT_MOC_LITERAL(9, 171, 8), // "setpoint"
QT_MOC_LITERAL(10, 180, 4), // "rate"
QT_MOC_LITERAL(11, 185, 16), // "newCurrentValues"
QT_MOC_LITERAL(12, 202, 7), // "current"
QT_MOC_LITERAL(13, 210, 7), // "voltage"
QT_MOC_LITERAL(14, 218, 8), // "newMagSP"
QT_MOC_LITERAL(15, 227, 8), // "magField"
QT_MOC_LITERAL(16, 236, 7), // "magRate"
QT_MOC_LITERAL(17, 244, 10), // "newAngleSP"
QT_MOC_LITERAL(18, 255, 5), // "angle"
QT_MOC_LITERAL(19, 261, 11), // "newRotstate"
QT_MOC_LITERAL(20, 273, 9), // "rotActive"
QT_MOC_LITERAL(21, 283, 15), // "newErrorMessage"
QT_MOC_LITERAL(22, 299, 16), // "errormessagePpms"
QT_MOC_LITERAL(23, 316, 9), // "onNewData"
QT_MOC_LITERAL(24, 326, 26), // "std::shared_ptr<DataPoint>"
QT_MOC_LITERAL(25, 353, 9), // "datapoint"
QT_MOC_LITERAL(26, 363, 18), // "onNewCurrentValues"
QT_MOC_LITERAL(27, 382, 11), // "onNewTempSP"
QT_MOC_LITERAL(28, 394, 10), // "onNewMagSP"
QT_MOC_LITERAL(29, 405, 12), // "onNewAngleSP"
QT_MOC_LITERAL(30, 418, 13), // "onNewRotstate"
QT_MOC_LITERAL(31, 432, 17) // "onNewErrorMessage"

    },
    "MeasurementsManager\0newData\0\0"
    "std::shared_ptr<const DataPoint>\0"
    "startNewMeasurement\0"
    "std::shared_ptr<const MeasurementSequence>\0"
    "newState\0MeasurementsManager::State\0"
    "newTempSP\0setpoint\0rate\0newCurrentValues\0"
    "current\0voltage\0newMagSP\0magField\0"
    "magRate\0newAngleSP\0angle\0newRotstate\0"
    "rotActive\0newErrorMessage\0errormessagePpms\0"
    "onNewData\0std::shared_ptr<DataPoint>\0"
    "datapoint\0onNewCurrentValues\0onNewTempSP\0"
    "onNewMagSP\0onNewAngleSP\0onNewRotstate\0"
    "onNewErrorMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MeasurementsManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,
       6,    1,  100,    2, 0x06 /* Public */,
       8,    2,  103,    2, 0x06 /* Public */,
      11,    2,  108,    2, 0x06 /* Public */,
      14,    2,  113,    2, 0x06 /* Public */,
      17,    1,  118,    2, 0x06 /* Public */,
      19,    1,  121,    2, 0x06 /* Public */,
      21,    1,  124,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      23,    1,  127,    2, 0x08 /* Private */,
      26,    2,  130,    2, 0x08 /* Private */,
      27,    2,  135,    2, 0x08 /* Private */,
      28,    2,  140,    2, 0x08 /* Private */,
      29,    1,  145,    2, 0x08 /* Private */,
      30,    1,  148,    2, 0x08 /* Private */,
      31,    1,  151,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 7,    6,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    9,   10,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   12,   13,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   15,   16,
    QMetaType::Void, QMetaType::Double,   18,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::QString,   22,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   12,   13,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    9,   10,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   15,   16,
    QMetaType::Void, QMetaType::Double,   18,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::QString,   22,

       0        // eod
};

void MeasurementsManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MeasurementsManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newData((*reinterpret_cast< std::shared_ptr<const DataPoint>(*)>(_a[1]))); break;
        case 1: _t->startNewMeasurement((*reinterpret_cast< std::shared_ptr<const MeasurementSequence>(*)>(_a[1]))); break;
        case 2: _t->newState((*reinterpret_cast< MeasurementsManager::State(*)>(_a[1]))); break;
        case 3: _t->newTempSP((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 4: _t->newCurrentValues((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 5: _t->newMagSP((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 6: _t->newAngleSP((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->newRotstate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->newErrorMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->onNewData((*reinterpret_cast< std::shared_ptr<DataPoint>(*)>(_a[1]))); break;
        case 10: _t->onNewCurrentValues((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 11: _t->onNewTempSP((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 12: _t->onNewMagSP((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 13: _t->onNewAngleSP((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->onNewRotstate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->onNewErrorMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MeasurementsManager::*)(std::shared_ptr<const DataPoint> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeasurementsManager::newData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MeasurementsManager::*)(std::shared_ptr<const MeasurementSequence> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeasurementsManager::startNewMeasurement)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MeasurementsManager::*)(MeasurementsManager::State );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeasurementsManager::newState)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MeasurementsManager::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeasurementsManager::newTempSP)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MeasurementsManager::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeasurementsManager::newCurrentValues)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MeasurementsManager::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeasurementsManager::newMagSP)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MeasurementsManager::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeasurementsManager::newAngleSP)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MeasurementsManager::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeasurementsManager::newRotstate)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MeasurementsManager::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeasurementsManager::newErrorMessage)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MeasurementsManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MeasurementsManager.data,
    qt_meta_data_MeasurementsManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MeasurementsManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MeasurementsManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MeasurementsManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MeasurementsManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MeasurementsManager::newData(std::shared_ptr<const DataPoint> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MeasurementsManager::startNewMeasurement(std::shared_ptr<const MeasurementSequence> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MeasurementsManager::newState(MeasurementsManager::State _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MeasurementsManager::newTempSP(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MeasurementsManager::newCurrentValues(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MeasurementsManager::newMagSP(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MeasurementsManager::newAngleSP(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MeasurementsManager::newRotstate(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MeasurementsManager::newErrorMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
