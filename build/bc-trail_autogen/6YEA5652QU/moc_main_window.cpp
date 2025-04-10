/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/main_window.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "onStartSystem",
    "",
    "onStopSystem",
    "onResetSystem",
    "onModeChanged",
    "updateSystemStatus",
    "onRefreshJoysticks",
    "onJoystickSelected",
    "index",
    "updateJoystickList",
    "updateJoystickInfo",
    "onButtonStateChanged",
    "button",
    "pressed",
    "onAxisChanged",
    "axis",
    "value",
    "onHatStateChanged",
    "hat",
    "onCalibrateJoystick",
    "onFsmAxisMappingChanged",
    "onFsmDeadzoneChanged",
    "onFsmInvertAxisToggled",
    "checked",
    "onEnableFsmOutput",
    "enabled",
    "updateFsmPosition",
    "x",
    "y",
    "onGimbalAxisMappingChanged",
    "onGimbalDeadzoneChanged",
    "onGimbalInvertAxisToggled",
    "onEnableGimbalOutput",
    "updateGimbalPosition",
    "azimuth",
    "elevation",
    "auxElevation",
    "onTrackerInitialize",
    "onTrackerPing",
    "onTrackerAutoPollToggled",
    "pollTracker",
    "updateTrackerStatus",
    "xError",
    "yError",
    "state",
    "handleTrackerError",
    "errorMsg",
    "onBrowseLogFile",
    "onStartStopLogging"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[100];
    char stringdata0[11];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[14];
    char stringdata5[14];
    char stringdata6[19];
    char stringdata7[19];
    char stringdata8[19];
    char stringdata9[6];
    char stringdata10[19];
    char stringdata11[19];
    char stringdata12[21];
    char stringdata13[7];
    char stringdata14[8];
    char stringdata15[14];
    char stringdata16[5];
    char stringdata17[6];
    char stringdata18[18];
    char stringdata19[4];
    char stringdata20[20];
    char stringdata21[24];
    char stringdata22[21];
    char stringdata23[23];
    char stringdata24[8];
    char stringdata25[18];
    char stringdata26[8];
    char stringdata27[18];
    char stringdata28[2];
    char stringdata29[2];
    char stringdata30[27];
    char stringdata31[24];
    char stringdata32[26];
    char stringdata33[21];
    char stringdata34[21];
    char stringdata35[8];
    char stringdata36[10];
    char stringdata37[13];
    char stringdata38[20];
    char stringdata39[14];
    char stringdata40[25];
    char stringdata41[12];
    char stringdata42[20];
    char stringdata43[7];
    char stringdata44[7];
    char stringdata45[6];
    char stringdata46[19];
    char stringdata47[9];
    char stringdata48[16];
    char stringdata49[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 13),  // "onStartSystem"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 12),  // "onStopSystem"
        QT_MOC_LITERAL(39, 13),  // "onResetSystem"
        QT_MOC_LITERAL(53, 13),  // "onModeChanged"
        QT_MOC_LITERAL(67, 18),  // "updateSystemStatus"
        QT_MOC_LITERAL(86, 18),  // "onRefreshJoysticks"
        QT_MOC_LITERAL(105, 18),  // "onJoystickSelected"
        QT_MOC_LITERAL(124, 5),  // "index"
        QT_MOC_LITERAL(130, 18),  // "updateJoystickList"
        QT_MOC_LITERAL(149, 18),  // "updateJoystickInfo"
        QT_MOC_LITERAL(168, 20),  // "onButtonStateChanged"
        QT_MOC_LITERAL(189, 6),  // "button"
        QT_MOC_LITERAL(196, 7),  // "pressed"
        QT_MOC_LITERAL(204, 13),  // "onAxisChanged"
        QT_MOC_LITERAL(218, 4),  // "axis"
        QT_MOC_LITERAL(223, 5),  // "value"
        QT_MOC_LITERAL(229, 17),  // "onHatStateChanged"
        QT_MOC_LITERAL(247, 3),  // "hat"
        QT_MOC_LITERAL(251, 19),  // "onCalibrateJoystick"
        QT_MOC_LITERAL(271, 23),  // "onFsmAxisMappingChanged"
        QT_MOC_LITERAL(295, 20),  // "onFsmDeadzoneChanged"
        QT_MOC_LITERAL(316, 22),  // "onFsmInvertAxisToggled"
        QT_MOC_LITERAL(339, 7),  // "checked"
        QT_MOC_LITERAL(347, 17),  // "onEnableFsmOutput"
        QT_MOC_LITERAL(365, 7),  // "enabled"
        QT_MOC_LITERAL(373, 17),  // "updateFsmPosition"
        QT_MOC_LITERAL(391, 1),  // "x"
        QT_MOC_LITERAL(393, 1),  // "y"
        QT_MOC_LITERAL(395, 26),  // "onGimbalAxisMappingChanged"
        QT_MOC_LITERAL(422, 23),  // "onGimbalDeadzoneChanged"
        QT_MOC_LITERAL(446, 25),  // "onGimbalInvertAxisToggled"
        QT_MOC_LITERAL(472, 20),  // "onEnableGimbalOutput"
        QT_MOC_LITERAL(493, 20),  // "updateGimbalPosition"
        QT_MOC_LITERAL(514, 7),  // "azimuth"
        QT_MOC_LITERAL(522, 9),  // "elevation"
        QT_MOC_LITERAL(532, 12),  // "auxElevation"
        QT_MOC_LITERAL(545, 19),  // "onTrackerInitialize"
        QT_MOC_LITERAL(565, 13),  // "onTrackerPing"
        QT_MOC_LITERAL(579, 24),  // "onTrackerAutoPollToggled"
        QT_MOC_LITERAL(604, 11),  // "pollTracker"
        QT_MOC_LITERAL(616, 19),  // "updateTrackerStatus"
        QT_MOC_LITERAL(636, 6),  // "xError"
        QT_MOC_LITERAL(643, 6),  // "yError"
        QT_MOC_LITERAL(650, 5),  // "state"
        QT_MOC_LITERAL(656, 18),  // "handleTrackerError"
        QT_MOC_LITERAL(675, 8),  // "errorMsg"
        QT_MOC_LITERAL(684, 15),  // "onBrowseLogFile"
        QT_MOC_LITERAL(700, 18)   // "onStartStopLogging"
    },
    "MainWindow",
    "onStartSystem",
    "",
    "onStopSystem",
    "onResetSystem",
    "onModeChanged",
    "updateSystemStatus",
    "onRefreshJoysticks",
    "onJoystickSelected",
    "index",
    "updateJoystickList",
    "updateJoystickInfo",
    "onButtonStateChanged",
    "button",
    "pressed",
    "onAxisChanged",
    "axis",
    "value",
    "onHatStateChanged",
    "hat",
    "onCalibrateJoystick",
    "onFsmAxisMappingChanged",
    "onFsmDeadzoneChanged",
    "onFsmInvertAxisToggled",
    "checked",
    "onEnableFsmOutput",
    "enabled",
    "updateFsmPosition",
    "x",
    "y",
    "onGimbalAxisMappingChanged",
    "onGimbalDeadzoneChanged",
    "onGimbalInvertAxisToggled",
    "onEnableGimbalOutput",
    "updateGimbalPosition",
    "azimuth",
    "elevation",
    "auxElevation",
    "onTrackerInitialize",
    "onTrackerPing",
    "onTrackerAutoPollToggled",
    "pollTracker",
    "updateTrackerStatus",
    "xError",
    "yError",
    "state",
    "handleTrackerError",
    "errorMsg",
    "onBrowseLogFile",
    "onStartStopLogging"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  200,    2, 0x08,    1 /* Private */,
       3,    0,  201,    2, 0x08,    2 /* Private */,
       4,    0,  202,    2, 0x08,    3 /* Private */,
       5,    0,  203,    2, 0x08,    4 /* Private */,
       6,    0,  204,    2, 0x08,    5 /* Private */,
       7,    0,  205,    2, 0x08,    6 /* Private */,
       8,    1,  206,    2, 0x08,    7 /* Private */,
      10,    0,  209,    2, 0x08,    9 /* Private */,
      11,    0,  210,    2, 0x08,   10 /* Private */,
      12,    2,  211,    2, 0x08,   11 /* Private */,
      15,    2,  216,    2, 0x08,   14 /* Private */,
      18,    2,  221,    2, 0x08,   17 /* Private */,
      20,    0,  226,    2, 0x08,   20 /* Private */,
      21,    0,  227,    2, 0x08,   21 /* Private */,
      22,    1,  228,    2, 0x08,   22 /* Private */,
      23,    1,  231,    2, 0x08,   24 /* Private */,
      25,    1,  234,    2, 0x08,   26 /* Private */,
      27,    2,  237,    2, 0x08,   28 /* Private */,
      30,    0,  242,    2, 0x08,   31 /* Private */,
      31,    1,  243,    2, 0x08,   32 /* Private */,
      32,    1,  246,    2, 0x08,   34 /* Private */,
      33,    1,  249,    2, 0x08,   36 /* Private */,
      34,    3,  252,    2, 0x08,   38 /* Private */,
      38,    0,  259,    2, 0x08,   42 /* Private */,
      39,    0,  260,    2, 0x08,   43 /* Private */,
      40,    1,  261,    2, 0x08,   44 /* Private */,
      41,    0,  264,    2, 0x08,   46 /* Private */,
      42,    3,  265,    2, 0x08,   47 /* Private */,
      46,    1,  272,    2, 0x08,   51 /* Private */,
      48,    0,  275,    2, 0x08,   53 /* Private */,
      49,    0,  276,    2, 0x08,   54 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   13,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   16,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   19,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void, QMetaType::Bool,   26,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   28,   29,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void, QMetaType::Bool,   26,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   35,   36,   37,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::QString,   43,   44,   45,
    QMetaType::Void, QMetaType::QString,   47,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'onStartSystem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStopSystem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onResetSystem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onModeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateSystemStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRefreshJoysticks'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onJoystickSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateJoystickList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateJoystickInfo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onButtonStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onAxisChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onHatStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onCalibrateJoystick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFsmAxisMappingChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFsmDeadzoneChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onFsmInvertAxisToggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onEnableFsmOutput'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'updateFsmPosition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'onGimbalAxisMappingChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onGimbalDeadzoneChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onGimbalInvertAxisToggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onEnableGimbalOutput'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'updateGimbalPosition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'onTrackerInitialize'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTrackerPing'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTrackerAutoPollToggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'pollTracker'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateTrackerStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'handleTrackerError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onBrowseLogFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStartStopLogging'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onStartSystem(); break;
        case 1: _t->onStopSystem(); break;
        case 2: _t->onResetSystem(); break;
        case 3: _t->onModeChanged(); break;
        case 4: _t->updateSystemStatus(); break;
        case 5: _t->onRefreshJoysticks(); break;
        case 6: _t->onJoystickSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->updateJoystickList(); break;
        case 8: _t->updateJoystickInfo(); break;
        case 9: _t->onButtonStateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 10: _t->onAxisChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 11: _t->onHatStateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 12: _t->onCalibrateJoystick(); break;
        case 13: _t->onFsmAxisMappingChanged(); break;
        case 14: _t->onFsmDeadzoneChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->onFsmInvertAxisToggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 16: _t->onEnableFsmOutput((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 17: _t->updateFsmPosition((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        case 18: _t->onGimbalAxisMappingChanged(); break;
        case 19: _t->onGimbalDeadzoneChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 20: _t->onGimbalInvertAxisToggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 21: _t->onEnableGimbalOutput((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 22: _t->updateGimbalPosition((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 23: _t->onTrackerInitialize(); break;
        case 24: _t->onTrackerPing(); break;
        case 25: _t->onTrackerAutoPollToggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 26: _t->pollTracker(); break;
        case 27: _t->updateTrackerStatus((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 28: _t->handleTrackerError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 29: _t->onBrowseLogFile(); break;
        case 30: _t->onStartStopLogging(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 31)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 31;
    }
    return _id;
}
QT_WARNING_POP
