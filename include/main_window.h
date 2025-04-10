#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QProgressBar>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QElapsedTimer>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QFont>
#include <QTextEdit>
#include <QGroupBox>

#include "joystick_interface.h"
#include "fsm_controller.h"
#include "gimbal_controller.h"
#include "tracker_interface.h"
#include "control_loop.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // System control
    void onStartSystem();
    void onStopSystem();
    void onResetSystem();
    void onModeChanged();
    void updateSystemStatus();

    // Joystick related slots
    void onRefreshJoysticks();
    void onJoystickSelected(int index);
    void updateJoystickList();
    void updateJoystickInfo();
    void onButtonStateChanged(int button, bool pressed);
    void onAxisChanged(int axis, int value);
    void onHatStateChanged(int hat, int value);
    void onCalibrateJoystick();

    // FSM related slots
    void onFsmAxisMappingChanged();
    void onFsmDeadzoneChanged(int value);
    void onFsmInvertAxisToggled(bool checked);
    void onEnableFsmOutput(bool enabled);
    void updateFsmPosition(double x, double y);

    // Gimbal related slots
    void onGimbalAxisMappingChanged();
    void onGimbalDeadzoneChanged(int value);
    void onGimbalInvertAxisToggled(bool checked);
    void onEnableGimbalOutput(bool enabled);
    void updateGimbalPosition(double azimuth, double elevation, double auxElevation);

    // Tracker related slots
    void onTrackerInitialize();
    void onTrackerPing();
    void onTrackerAutoPollToggled(bool checked);
    void pollTracker();
    void updateTrackerStatus(double xError, double yError, const QString &state);
    void handleTrackerError(const QString &errorMsg);

    // Logging slots
    void onBrowseLogFile();
    void onStartStopLogging();

private:
    Ui::MainWindow *ui;
    JoystickInterface *m_joystickInterface;
    FSMController *m_fsmController;
    GimbalController *m_gimbalController;
    TrackerInterface *m_trackerInterface;
    ControlLoop *m_controlLoop;

    // Joystick UI elements
    QVector<QLabel*> m_buttonLabels;
    QVector<QProgressBar*> m_axisProgressBars;
    QVector<QLabel*> m_hatLabels;

    // System state
    bool m_systemRunning;
    enum class ControlMode {
        CoarseTrack,  // Manual control of both gimbal and FSM
        FineTrack,    // Manual control of FSM only
        AutoTrack     // Automatic tracking using tracker card
    };
    ControlMode m_currentMode;

    // Selected joystick index
    int m_selectedJoystickIndex;

    // FSM control state
    bool m_fsmOutputEnabled;
    int m_fsmXAxisIndex;
    int m_fsmYAxisIndex;
    bool m_invertFsmXAxis;
    bool m_invertFsmYAxis;
    double m_fsmDeadzone;

    // Gimbal control state
    bool m_gimbalOutputEnabled;
    int m_azimuthAxisIndex;
    int m_elevationAxisIndex;
    int m_auxElevationAxisIndex;
    bool m_invertAzimuthAxis;
    bool m_invertElevationAxis;
    bool m_invertAuxElevationAxis;
    double m_gimbalDeadzone;

    // Tracker state
    bool m_trackerInitialized;
    bool m_trackerAutoPoll;
    QTimer *m_trackerPollTimer;

    // Data logging
    QFile *m_logFile;
    QTextStream *m_logStream;
    bool m_loggingActive;
    QElapsedTimer m_loggingTimer;

    // Status update timer
    QTimer *m_statusUpdateTimer;
    
    // Font for status bar
    QFont m_statusFont;

    // Telemetry data structure 
    struct Telemetry {
        double fsmX;
        double fsmY;
        double gimbalAz;
        double gimbalEl;
        double gimbalAuxEl;
        double joystickX;
        double joystickY;
        double joystickZ;
        double trackErrorX;
        double trackErrorY;
    } m_telemetry;

    // UI initialization methods
    void setupUi();
    void setupSignals();
    void setupGraphs();
    void setupStatusBar();
    void createJoystickInputsUI();
    void clearJoystickInputsUI();
    void setupSignalsAndSlots();
    
    // Status and logging methods
    void updateStatusDisplay();
    void updateModeDisplay(ControlLoop::OperationMode mode);
    void logMessage(const QString &message);
    void logError(const QString &error);
    
    // Event handlers from other components
    void onClearLogsButtonClicked();
    void onStatusChanged(const QString &message);
    void onErrorOccurred(const QString &error);
    void onOperationModeChanged(ControlLoop::OperationMode mode);
    void onTelemetryUpdated(double fsmX, double fsmY, 
                          double gimbalAz, double gimbalEl, double gimbalAuxEl,
                          double joystickX, double joystickY, double joystickZ,
                          double trackErrorX, double trackErrorY);

    // Helper methods
    QString hatValueToString(int value);
    double mapAxisToPosition(int axisValue, double deadzone, bool invert);
    void logData(const QString &data);
    void updateUIForCurrentMode();
    void setStatusMessage(const QString &message);
};

#endif // MAIN_WINDOW_H