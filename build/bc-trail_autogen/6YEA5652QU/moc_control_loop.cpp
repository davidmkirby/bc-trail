/****************************************************************************
** Meta object code from reading C++ file 'control_loop.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/control_loop.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'control_loop.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSControlLoopENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSControlLoopENDCLASS = QtMocHelpers::stringData(
    "ControlLoop",
    "statusChanged",
    "",
    "message",
    "errorOccurred",
    "error",
    "operationModeChanged",
    "OperationMode",
    "mode",
    "telemetryUpdated",
    "fsmX",
    "fsmY",
    "gimbalAz",
    "gimbalEl",
    "gimbalAuxEl",
    "joystickX",
    "joystickY",
    "joystickZ",
    "trackErrorX",
    "trackErrorY",
    "handleJoystickModeButtonPressed",
    "handleJoystickPositionChanged",
    "x",
    "y",
    "z",
    "handleJoystickRotationChanged",
    "rx",
    "ry",
    "rz",
    "handleTrackingStatusChanged",
    "isTracking",
    "handleTrackingErrorsUpdated",
    "xError",
    "yError",
    "handleFSMFeedbackUpdated",
    "controlLoopTick"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSControlLoopENDCLASS_t {
    uint offsetsAndSizes[72];
    char stringdata0[12];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[14];
    char stringdata5[6];
    char stringdata6[21];
    char stringdata7[14];
    char stringdata8[5];
    char stringdata9[17];
    char stringdata10[5];
    char stringdata11[5];
    char stringdata12[9];
    char stringdata13[9];
    char stringdata14[12];
    char stringdata15[10];
    char stringdata16[10];
    char stringdata17[10];
    char stringdata18[12];
    char stringdata19[12];
    char stringdata20[32];
    char stringdata21[30];
    char stringdata22[2];
    char stringdata23[2];
    char stringdata24[2];
    char stringdata25[30];
    char stringdata26[3];
    char stringdata27[3];
    char stringdata28[3];
    char stringdata29[28];
    char stringdata30[11];
    char stringdata31[28];
    char stringdata32[7];
    char stringdata33[7];
    char stringdata34[25];
    char stringdata35[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSControlLoopENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSControlLoopENDCLASS_t qt_meta_stringdata_CLASSControlLoopENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "ControlLoop"
        QT_MOC_LITERAL(12, 13),  // "statusChanged"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 7),  // "message"
        QT_MOC_LITERAL(35, 13),  // "errorOccurred"
        QT_MOC_LITERAL(49, 5),  // "error"
        QT_MOC_LITERAL(55, 20),  // "operationModeChanged"
        QT_MOC_LITERAL(76, 13),  // "OperationMode"
        QT_MOC_LITERAL(90, 4),  // "mode"
        QT_MOC_LITERAL(95, 16),  // "telemetryUpdated"
        QT_MOC_LITERAL(112, 4),  // "fsmX"
        QT_MOC_LITERAL(117, 4),  // "fsmY"
        QT_MOC_LITERAL(122, 8),  // "gimbalAz"
        QT_MOC_LITERAL(131, 8),  // "gimbalEl"
        QT_MOC_LITERAL(140, 11),  // "gimbalAuxEl"
        QT_MOC_LITERAL(152, 9),  // "joystickX"
        QT_MOC_LITERAL(162, 9),  // "joystickY"
        QT_MOC_LITERAL(172, 9),  // "joystickZ"
        QT_MOC_LITERAL(182, 11),  // "trackErrorX"
        QT_MOC_LITERAL(194, 11),  // "trackErrorY"
        QT_MOC_LITERAL(206, 31),  // "handleJoystickModeButtonPressed"
        QT_MOC_LITERAL(238, 29),  // "handleJoystickPositionChanged"
        QT_MOC_LITERAL(268, 1),  // "x"
        QT_MOC_LITERAL(270, 1),  // "y"
        QT_MOC_LITERAL(272, 1),  // "z"
        QT_MOC_LITERAL(274, 29),  // "handleJoystickRotationChanged"
        QT_MOC_LITERAL(304, 2),  // "rx"
        QT_MOC_LITERAL(307, 2),  // "ry"
        QT_MOC_LITERAL(310, 2),  // "rz"
        QT_MOC_LITERAL(313, 27),  // "handleTrackingStatusChanged"
        QT_MOC_LITERAL(341, 10),  // "isTracking"
        QT_MOC_LITERAL(352, 27),  // "handleTrackingErrorsUpdated"
        QT_MOC_LITERAL(380, 6),  // "xError"
        QT_MOC_LITERAL(387, 6),  // "yError"
        QT_MOC_LITERAL(394, 24),  // "handleFSMFeedbackUpdated"
        QT_MOC_LITERAL(419, 15)   // "controlLoopTick"
    },
    "ControlLoop",
    "statusChanged",
    "",
    "message",
    "errorOccurred",
    "error",
    "operationModeChanged",
    "OperationMode",
    "mode",
    "telemetryUpdated",
    "fsmX",
    "fsmY",
    "gimbalAz",
    "gimbalEl",
    "gimbalAuxEl",
    "joystickX",
    "joystickY",
    "joystickZ",
    "trackErrorX",
    "trackErrorY",
    "handleJoystickModeButtonPressed",
    "handleJoystickPositionChanged",
    "x",
    "y",
    "z",
    "handleJoystickRotationChanged",
    "rx",
    "ry",
    "rz",
    "handleTrackingStatusChanged",
    "isTracking",
    "handleTrackingErrorsUpdated",
    "xError",
    "yError",
    "handleFSMFeedbackUpdated",
    "controlLoopTick"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSControlLoopENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   80,    2, 0x06,    1 /* Public */,
       4,    1,   83,    2, 0x06,    3 /* Public */,
       6,    1,   86,    2, 0x06,    5 /* Public */,
       9,   10,   89,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      20,    0,  110,    2, 0x08,   18 /* Private */,
      21,    3,  111,    2, 0x08,   19 /* Private */,
      25,    3,  118,    2, 0x08,   23 /* Private */,
      29,    1,  125,    2, 0x08,   27 /* Private */,
      31,    2,  128,    2, 0x08,   29 /* Private */,
      34,    2,  133,    2, 0x08,   32 /* Private */,
      35,    0,  138,    2, 0x08,   35 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,   10,   11,   12,   13,   14,   15,   16,   17,   18,   19,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   22,   23,   24,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   26,   27,   28,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   32,   33,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   22,   23,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ControlLoop::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSControlLoopENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSControlLoopENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSControlLoopENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ControlLoop, std::true_type>,
        // method 'statusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'operationModeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<OperationMode, std::false_type>,
        // method 'telemetryUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'handleJoystickModeButtonPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleJoystickPositionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'handleJoystickRotationChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'handleTrackingStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handleTrackingErrorsUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'handleFSMFeedbackUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'controlLoopTick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ControlLoop::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ControlLoop *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->statusChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->operationModeChanged((*reinterpret_cast< std::add_pointer_t<OperationMode>>(_a[1]))); break;
        case 3: _t->telemetryUpdated((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[9])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[10]))); break;
        case 4: _t->handleJoystickModeButtonPressed(); break;
        case 5: _t->handleJoystickPositionChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 6: _t->handleJoystickRotationChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 7: _t->handleTrackingStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->handleTrackingErrorsUpdated((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        case 9: _t->handleFSMFeedbackUpdated((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        case 10: _t->controlLoopTick(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ControlLoop::*)(const QString & );
            if (_t _q_method = &ControlLoop::statusChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ControlLoop::*)(const QString & );
            if (_t _q_method = &ControlLoop::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ControlLoop::*)(OperationMode );
            if (_t _q_method = &ControlLoop::operationModeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ControlLoop::*)(double , double , double , double , double , double , double , double , double , double );
            if (_t _q_method = &ControlLoop::telemetryUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *ControlLoop::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlLoop::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSControlLoopENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ControlLoop::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ControlLoop::statusChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ControlLoop::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ControlLoop::operationModeChanged(OperationMode _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ControlLoop::telemetryUpdated(double _t1, double _t2, double _t3, double _t4, double _t5, double _t6, double _t7, double _t8, double _t9, double _t10)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t8))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t9))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t10))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
