/****************************************************************************
** Meta object code from reading C++ file 'joystick_interface.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/joystick_interface.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'joystick_interface.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSJoystickInterfaceENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSJoystickInterfaceENDCLASS = QtMocHelpers::stringData(
    "JoystickInterface",
    "joystickPositionChanged",
    "",
    "x",
    "y",
    "z",
    "joystickRotationChanged",
    "rx",
    "ry",
    "rz",
    "buttonStateChanged",
    "button",
    "pressed",
    "hatStateChanged",
    "hat",
    "value",
    "modeButtonPressed",
    "joysticksChanged",
    "errorOccurred",
    "error",
    "refreshJoysticks",
    "pollEvents"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSJoystickInterfaceENDCLASS_t {
    uint offsetsAndSizes[44];
    char stringdata0[18];
    char stringdata1[24];
    char stringdata2[1];
    char stringdata3[2];
    char stringdata4[2];
    char stringdata5[2];
    char stringdata6[24];
    char stringdata7[3];
    char stringdata8[3];
    char stringdata9[3];
    char stringdata10[19];
    char stringdata11[7];
    char stringdata12[8];
    char stringdata13[16];
    char stringdata14[4];
    char stringdata15[6];
    char stringdata16[18];
    char stringdata17[17];
    char stringdata18[14];
    char stringdata19[6];
    char stringdata20[17];
    char stringdata21[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSJoystickInterfaceENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSJoystickInterfaceENDCLASS_t qt_meta_stringdata_CLASSJoystickInterfaceENDCLASS = {
    {
        QT_MOC_LITERAL(0, 17),  // "JoystickInterface"
        QT_MOC_LITERAL(18, 23),  // "joystickPositionChanged"
        QT_MOC_LITERAL(42, 0),  // ""
        QT_MOC_LITERAL(43, 1),  // "x"
        QT_MOC_LITERAL(45, 1),  // "y"
        QT_MOC_LITERAL(47, 1),  // "z"
        QT_MOC_LITERAL(49, 23),  // "joystickRotationChanged"
        QT_MOC_LITERAL(73, 2),  // "rx"
        QT_MOC_LITERAL(76, 2),  // "ry"
        QT_MOC_LITERAL(79, 2),  // "rz"
        QT_MOC_LITERAL(82, 18),  // "buttonStateChanged"
        QT_MOC_LITERAL(101, 6),  // "button"
        QT_MOC_LITERAL(108, 7),  // "pressed"
        QT_MOC_LITERAL(116, 15),  // "hatStateChanged"
        QT_MOC_LITERAL(132, 3),  // "hat"
        QT_MOC_LITERAL(136, 5),  // "value"
        QT_MOC_LITERAL(142, 17),  // "modeButtonPressed"
        QT_MOC_LITERAL(160, 16),  // "joysticksChanged"
        QT_MOC_LITERAL(177, 13),  // "errorOccurred"
        QT_MOC_LITERAL(191, 5),  // "error"
        QT_MOC_LITERAL(197, 16),  // "refreshJoysticks"
        QT_MOC_LITERAL(214, 10)   // "pollEvents"
    },
    "JoystickInterface",
    "joystickPositionChanged",
    "",
    "x",
    "y",
    "z",
    "joystickRotationChanged",
    "rx",
    "ry",
    "rz",
    "buttonStateChanged",
    "button",
    "pressed",
    "hatStateChanged",
    "hat",
    "value",
    "modeButtonPressed",
    "joysticksChanged",
    "errorOccurred",
    "error",
    "refreshJoysticks",
    "pollEvents"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSJoystickInterfaceENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   68,    2, 0x06,    1 /* Public */,
       6,    3,   75,    2, 0x06,    5 /* Public */,
      10,    2,   82,    2, 0x06,    9 /* Public */,
      13,    2,   87,    2, 0x06,   12 /* Public */,
      16,    0,   92,    2, 0x06,   15 /* Public */,
      17,    0,   93,    2, 0x06,   16 /* Public */,
      18,    1,   94,    2, 0x06,   17 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      20,    0,   97,    2, 0x0a,   19 /* Public */,
      21,    0,   98,    2, 0x08,   20 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    4,    5,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    7,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   19,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject JoystickInterface::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSJoystickInterfaceENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSJoystickInterfaceENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSJoystickInterfaceENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<JoystickInterface, std::true_type>,
        // method 'joystickPositionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'joystickRotationChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'buttonStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'hatStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'modeButtonPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'joysticksChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'refreshJoysticks'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pollEvents'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void JoystickInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<JoystickInterface *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->joystickPositionChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 1: _t->joystickRotationChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 2: _t->buttonStateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 3: _t->hatStateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->modeButtonPressed(); break;
        case 5: _t->joysticksChanged(); break;
        case 6: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->refreshJoysticks(); break;
        case 8: _t->pollEvents(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (JoystickInterface::*)(double , double , double );
            if (_t _q_method = &JoystickInterface::joystickPositionChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (JoystickInterface::*)(double , double , double );
            if (_t _q_method = &JoystickInterface::joystickRotationChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (JoystickInterface::*)(int , bool );
            if (_t _q_method = &JoystickInterface::buttonStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (JoystickInterface::*)(int , int );
            if (_t _q_method = &JoystickInterface::hatStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (JoystickInterface::*)();
            if (_t _q_method = &JoystickInterface::modeButtonPressed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (JoystickInterface::*)();
            if (_t _q_method = &JoystickInterface::joysticksChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (JoystickInterface::*)(const QString & );
            if (_t _q_method = &JoystickInterface::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject *JoystickInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JoystickInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSJoystickInterfaceENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int JoystickInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void JoystickInterface::joystickPositionChanged(double _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void JoystickInterface::joystickRotationChanged(double _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void JoystickInterface::buttonStateChanged(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void JoystickInterface::hatStateChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void JoystickInterface::modeButtonPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void JoystickInterface::joysticksChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void JoystickInterface::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
