/****************************************************************************
** Meta object code from reading C++ file 'ppmsabstract.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../ppmsabstract.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ppmsabstract.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PpmsAbstract_t {
    QByteArrayData data[14];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PpmsAbstract_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PpmsAbstract_t qt_meta_stringdata_PpmsAbstract = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PpmsAbstract"
QT_MOC_LITERAL(1, 13, 9), // "newTempSP"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "setpoint"
QT_MOC_LITERAL(4, 33, 4), // "rate"
QT_MOC_LITERAL(5, 38, 8), // "newMagSP"
QT_MOC_LITERAL(6, 47, 8), // "magField"
QT_MOC_LITERAL(7, 56, 7), // "magRate"
QT_MOC_LITERAL(8, 64, 10), // "newAngleSP"
QT_MOC_LITERAL(9, 75, 5), // "angle"
QT_MOC_LITERAL(10, 81, 11), // "newRotstate"
QT_MOC_LITERAL(11, 93, 9), // "rotActive"
QT_MOC_LITERAL(12, 103, 12), // "newErrorPPMS"
QT_MOC_LITERAL(13, 116, 9) // "ppmsError"

    },
    "PpmsAbstract\0newTempSP\0\0setpoint\0rate\0"
    "newMagSP\0magField\0magRate\0newAngleSP\0"
    "angle\0newRotstate\0rotActive\0newErrorPPMS\0"
    "ppmsError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PpmsAbstract[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       5,    2,   44,    2, 0x06 /* Public */,
       8,    1,   49,    2, 0x06 /* Public */,
      10,    1,   52,    2, 0x06 /* Public */,
      12,    1,   55,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    6,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::QString,   13,

       0        // eod
};

void PpmsAbstract::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PpmsAbstract *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newTempSP((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->newMagSP((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: _t->newAngleSP((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->newRotstate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->newErrorPPMS((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PpmsAbstract::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PpmsAbstract::newTempSP)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PpmsAbstract::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PpmsAbstract::newMagSP)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PpmsAbstract::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PpmsAbstract::newAngleSP)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PpmsAbstract::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PpmsAbstract::newRotstate)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PpmsAbstract::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PpmsAbstract::newErrorPPMS)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PpmsAbstract::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_PpmsAbstract.data,
    qt_meta_data_PpmsAbstract,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PpmsAbstract::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PpmsAbstract::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PpmsAbstract.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PpmsAbstract::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void PpmsAbstract::newTempSP(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PpmsAbstract::newMagSP(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PpmsAbstract::newAngleSP(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PpmsAbstract::newRotstate(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PpmsAbstract::newErrorPPMS(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
