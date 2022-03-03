/****************************************************************************
** Meta object code from reading C++ file 'instrumentmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../instrumentmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'instrumentmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_InstrumentManager_t {
    QByteArrayData data[21];
    char stringdata0[215];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InstrumentManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InstrumentManager_t qt_meta_stringdata_InstrumentManager = {
    {
QT_MOC_LITERAL(0, 0, 17), // "InstrumentManager"
QT_MOC_LITERAL(1, 18, 7), // "newData"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 26), // "std::shared_ptr<DataPoint>"
QT_MOC_LITERAL(4, 54, 9), // "dataPoint"
QT_MOC_LITERAL(5, 64, 9), // "newTempSP"
QT_MOC_LITERAL(6, 74, 8), // "setpoint"
QT_MOC_LITERAL(7, 83, 4), // "rate"
QT_MOC_LITERAL(8, 88, 8), // "newMagSP"
QT_MOC_LITERAL(9, 97, 8), // "magField"
QT_MOC_LITERAL(10, 106, 7), // "magRate"
QT_MOC_LITERAL(11, 114, 10), // "newAngleSP"
QT_MOC_LITERAL(12, 125, 5), // "angle"
QT_MOC_LITERAL(13, 131, 11), // "newRotstate"
QT_MOC_LITERAL(14, 143, 9), // "rotActive"
QT_MOC_LITERAL(15, 153, 9), // "newValues"
QT_MOC_LITERAL(16, 163, 7), // "current"
QT_MOC_LITERAL(17, 171, 7), // "voltage"
QT_MOC_LITERAL(18, 179, 15), // "newErrorMessage"
QT_MOC_LITERAL(19, 195, 9), // "ppmsError"
QT_MOC_LITERAL(20, 205, 9) // "onPolling"

    },
    "InstrumentManager\0newData\0\0"
    "std::shared_ptr<DataPoint>\0dataPoint\0"
    "newTempSP\0setpoint\0rate\0newMagSP\0"
    "magField\0magRate\0newAngleSP\0angle\0"
    "newRotstate\0rotActive\0newValues\0current\0"
    "voltage\0newErrorMessage\0ppmsError\0"
    "onPolling"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InstrumentManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    2,   57,    2, 0x06 /* Public */,
       8,    2,   62,    2, 0x06 /* Public */,
      11,    1,   67,    2, 0x06 /* Public */,
      13,    1,   70,    2, 0x06 /* Public */,
      15,    2,   73,    2, 0x06 /* Public */,
      18,    1,   78,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    0,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    6,    7,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    9,   10,
    QMetaType::Void, QMetaType::Double,   12,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   16,   17,
    QMetaType::Void, QMetaType::QString,   19,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void InstrumentManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InstrumentManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newData((*reinterpret_cast< std::shared_ptr<DataPoint>(*)>(_a[1]))); break;
        case 1: _t->newTempSP((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: _t->newMagSP((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->newAngleSP((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->newRotstate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->newValues((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 6: _t->newErrorMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->onPolling(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (InstrumentManager::*)(std::shared_ptr<DataPoint> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InstrumentManager::newData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (InstrumentManager::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InstrumentManager::newTempSP)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (InstrumentManager::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InstrumentManager::newMagSP)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (InstrumentManager::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InstrumentManager::newAngleSP)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (InstrumentManager::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InstrumentManager::newRotstate)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (InstrumentManager::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InstrumentManager::newValues)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (InstrumentManager::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InstrumentManager::newErrorMessage)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject InstrumentManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_InstrumentManager.data,
    qt_meta_data_InstrumentManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *InstrumentManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InstrumentManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_InstrumentManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int InstrumentManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void InstrumentManager::newData(std::shared_ptr<DataPoint> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void InstrumentManager::newTempSP(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void InstrumentManager::newMagSP(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void InstrumentManager::newAngleSP(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void InstrumentManager::newRotstate(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void InstrumentManager::newValues(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void InstrumentManager::newErrorMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
