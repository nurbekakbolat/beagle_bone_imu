/****************************************************************************
** Meta object code from reading C++ file 'imuclient.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "imuclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imuclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IMUClient_t {
    const uint offsetsAndSize[20];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_IMUClient_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_IMUClient_t qt_meta_stringdata_IMUClient = {
    {
QT_MOC_LITERAL(0, 9), // "IMUClient"
QT_MOC_LITERAL(10, 22), // "imuOrientationReceived"
QT_MOC_LITERAL(33, 0), // ""
QT_MOC_LITERAL(34, 2), // "qx"
QT_MOC_LITERAL(37, 2), // "qy"
QT_MOC_LITERAL(40, 2), // "qz"
QT_MOC_LITERAL(43, 2), // "qw"
QT_MOC_LITERAL(46, 15), // "imuDataReceived"
QT_MOC_LITERAL(62, 4), // "data"
QT_MOC_LITERAL(67, 8) // "readData"

    },
    "IMUClient\0imuOrientationReceived\0\0qx\0"
    "qy\0qz\0qw\0imuDataReceived\0data\0readData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IMUClient[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    4,   32,    2, 0x06,    1 /* Public */,
       7,    1,   41,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   44,    2, 0x08,    8 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::QByteArray,    8,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void IMUClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IMUClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->imuOrientationReceived((*reinterpret_cast< std::add_pointer_t<float>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[4]))); break;
        case 1: _t->imuDataReceived((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 2: _t->readData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IMUClient::*)(float , float , float , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMUClient::imuOrientationReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (IMUClient::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMUClient::imuDataReceived)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject IMUClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_IMUClient.offsetsAndSize,
    qt_meta_data_IMUClient,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_IMUClient_t
, QtPrivate::TypeAndForceComplete<IMUClient, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<float, std::false_type>, QtPrivate::TypeAndForceComplete<float, std::false_type>, QtPrivate::TypeAndForceComplete<float, std::false_type>, QtPrivate::TypeAndForceComplete<float, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *IMUClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IMUClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IMUClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int IMUClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void IMUClient::imuOrientationReceived(float _t1, float _t2, float _t3, float _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void IMUClient::imuDataReceived(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
