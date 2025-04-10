#ifndef CONTROL_LOOP_H
#define CONTROL_LOOP_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QMutex>
#include <atomic>
#include <memory>

#include "fsm_controller.h"
#include "gimbal_controller.h"
#include "tracker_interface.h"
#include "joystick_interface.h"

class ControlLoop : public QObject
{
    Q_OBJECT

public:
    enum class OperationMode {
        COARSE_TRACK,  // Manual control of both gimbal and FSM
        FINE_TRACK,    // Manual control of FSM only
        AUTO_TRACK     // Automatic tracking using tracker card data
    };

    explicit ControlLoop(QObject *parent = nullptr);
    ~ControlLoop();

    bool initialize();
    bool start();
    bool stop();

    // Set operation mode
    void setOperationMode(OperationMode mode);
    OperationMode getOperationMode() const;

signals:
    void statusChanged(const QString &message);
    void errorOccurred(const QString &error);
    void operationModeChanged(OperationMode mode);
    void telemetryUpdated(double fsmX, double fsmY,
                         double gimbalAz, double gimbalEl, double gimbalAuxEl,
                         double joystickX, double joystickY, double joystickZ,
                         double trackErrorX, double trackErrorY);

private slots:
    void handleJoystickModeButtonPressed();
    void handleJoystickPositionChanged(double x, double y, double z);
    void handleJoystickRotationChanged(double rx, double ry, double rz);
    void handleTrackingStatusChanged(bool isTracking);
    void handleTrackingErrorsUpdated(double xError, double yError);
    void handleFSMFeedbackUpdated(double x, double y);
    void controlLoopTick();

private:
    // Helper methods
    void updateControlMode();
    void cycleOperationMode();

    // Component objects
    std::unique_ptr<FSMController> m_fsmController;
    std::unique_ptr<GimbalController> m_gimbalController;
    std::unique_ptr<TrackerInterface> m_trackerInterface;
    std::unique_ptr<JoystickInterface> m_joystickInterface;

    // High-precision timer for control loop
    QTimer *m_controlTimer;

    // Operation state
    OperationMode m_mode;
    bool m_isTrackingActive;

    // Synchronization
    mutable QMutex m_mutex;
    std::atomic<bool> m_running;

    // Control loop configuration
    int m_controlRateHz;
};

#endif // CONTROL_LOOP_H