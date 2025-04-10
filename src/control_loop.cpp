#include "control_loop.h"
#include <QDebug>
#include <cmath>

ControlLoop::ControlLoop(QObject *parent)
    : QObject(parent)
    , m_fsmController(nullptr)
    , m_gimbalController(nullptr)
    , m_trackerInterface(nullptr)
    , m_joystickInterface(nullptr)
    , m_controlTimer(nullptr)
    , m_mode(OperationMode::COARSE_TRACK)
    , m_isTrackingActive(false)
    , m_running(false)
    , m_controlRateHz(1000) // 1000 Hz control rate
{
    // Create component instances
    m_fsmController = std::make_unique<FSMController>();
    m_gimbalController = std::make_unique<GimbalController>();
    m_trackerInterface = std::make_unique<TrackerInterface>();
    m_joystickInterface = std::make_unique<JoystickInterface>();

    // Create control timer
    m_controlTimer = new QTimer(this);
    m_controlTimer->setTimerType(Qt::PreciseTimer);

    // Connect signals and slots
    connect(m_joystickInterface.get(), &JoystickInterface::modeButtonPressed,
            this, &ControlLoop::handleJoystickModeButtonPressed);

    connect(m_joystickInterface.get(), &JoystickInterface::joystickPositionChanged,
            this, &ControlLoop::handleJoystickPositionChanged);

    connect(m_joystickInterface.get(), &JoystickInterface::joystickRotationChanged,
            this, &ControlLoop::handleJoystickRotationChanged);

    connect(m_trackerInterface.get(), &TrackerInterface::trackingStatusChanged,
            this, &ControlLoop::handleTrackingStatusChanged);

    connect(m_trackerInterface.get(), &TrackerInterface::trackingErrorsUpdated,
            this, &ControlLoop::handleTrackingErrorsUpdated);

    connect(m_fsmController.get(), &FSMController::feedbackUpdated,
            this, &ControlLoop::handleFSMFeedbackUpdated);

    connect(m_controlTimer, &QTimer::timeout,
            this, &ControlLoop::controlLoopTick);

    // Forward error signals
    connect(m_fsmController.get(), &FSMController::errorOccurred,
            this, &ControlLoop::errorOccurred);

    connect(m_gimbalController.get(), &GimbalController::errorOccurred,
            this, &ControlLoop::errorOccurred);

    connect(m_trackerInterface.get(), &TrackerInterface::errorOccurred,
            this, &ControlLoop::errorOccurred);

    connect(m_joystickInterface.get(), &JoystickInterface::errorOccurred,
            this, &ControlLoop::errorOccurred);
}

ControlLoop::~ControlLoop()
{
    stop();
}

bool ControlLoop::initialize()
{
    // Initialize all components
    if (!m_fsmController->initialize()) {
        emit errorOccurred("Failed to initialize FSM controller");
        return false;
    }

    if (!m_gimbalController->initialize()) {
        emit errorOccurred("Failed to initialize gimbal controller");
        return false;
    }

    if (!m_trackerInterface->initialize()) {
        emit errorOccurred("Failed to initialize tracker interface");
        return false;
    }

    if (!m_joystickInterface->initialize()) {
        emit errorOccurred("Failed to initialize joystick interface");
        return false;
    }

    // Set initial control mode
    updateControlMode();

    emit statusChanged("Control system initialized");
    return true;
}

bool ControlLoop::start()
{
    QMutexLocker locker(&m_mutex);

    if (m_running) {
        return true; // Already running
    }

    // Start all components
    if (!m_fsmController->start()) {
        emit errorOccurred("Failed to start FSM controller");
        return false;
    }

    if (!m_gimbalController->start()) {
        emit errorOccurred("Failed to start gimbal controller");
        return false;
    }

    if (!m_trackerInterface->start()) {
        emit errorOccurred("Failed to start tracker interface");
        return false;
    }

    if (!m_joystickInterface->start()) {
        emit errorOccurred("Failed to start joystick interface");
        return false;
    }

    // Start control loop timer
    m_controlTimer->start(1000 / m_controlRateHz);

    m_running = true;
    emit statusChanged("Control system started");
    return true;
}

bool ControlLoop::stop()
{
    QMutexLocker locker(&m_mutex);

    if (!m_running) {
        return true; // Already stopped
    }

    // Stop control loop timer
    m_controlTimer->stop();

    // Stop all components
    m_fsmController->stop();
    m_gimbalController->stop();
    m_trackerInterface->stop();
    m_joystickInterface->stop();

    m_running = false;
    emit statusChanged("Control system stopped");
    return true;
}

void ControlLoop::setOperationMode(OperationMode mode)
{
    QMutexLocker locker(&m_mutex);

    if (m_mode == mode) {
        return; // No change
    }

    m_mode = mode;

    // Update control mode for components
    updateControlMode();

    // Emit mode changed signal
    emit operationModeChanged(m_mode);

    emit statusChanged(QString("Operation mode changed to %1")
                      .arg(mode == OperationMode::COARSE_TRACK ? "Coarse Track" :
                           mode == OperationMode::FINE_TRACK ? "Fine Track" : "Auto Track"));
}

ControlLoop::OperationMode ControlLoop::getOperationMode() const
{
    QMutexLocker locker(&m_mutex);
    return m_mode;
}

void ControlLoop::handleJoystickModeButtonPressed()
{
    QMutexLocker locker(&m_mutex);

    // Cycle to the next mode
    cycleOperationMode();
}

void ControlLoop::handleJoystickPositionChanged(double x, double y, double z)
{
    QMutexLocker locker(&m_mutex);

    // In all modes, joystick position controls FSM
    m_fsmController->setManualInputs(x, y);

    // In coarse track mode, also control gimbal
    if (m_mode == OperationMode::COARSE_TRACK) {
        // For gimbal control, use a reduced range for fine control
        double scaleFactor = 0.2; // Scale down for more precise control
        m_gimbalController->setPosition(x * scaleFactor, y * scaleFactor, z * scaleFactor);
    }
}

void ControlLoop::handleJoystickRotationChanged(double rx, double ry, double rz)
{
    QMutexLocker locker(&m_mutex);

    // Only use rotation in coarse track mode for additional gimbal control
    if (m_mode == OperationMode::COARSE_TRACK) {
        double az, el, auxEl;
        m_gimbalController->getCurrentPosition(az, el, auxEl);

        // Update auxiliary elevation using rotation input
        double scaleFactor = 0.2; // Scale down for more precise control
        m_gimbalController->setPosition(az, el, rz * scaleFactor);
    }
}

void ControlLoop::handleTrackingStatusChanged(bool isTracking)
{
    QMutexLocker locker(&m_mutex);

    m_isTrackingActive = isTracking;

    // If in auto track mode, may need to adjust based on tracking status
    if (m_mode == OperationMode::AUTO_TRACK) {
        if (!m_isTrackingActive) {
            // If tracking is lost, could switch to manual mode
            // For now, just emit a status message
            emit statusChanged("Warning: Tracking lost in auto track mode");
        }
    }
}

void ControlLoop::handleTrackingErrorsUpdated(double xError, double yError)
{
    QMutexLocker locker(&m_mutex);

    // In auto track mode, update FSM with tracking errors
    if (m_mode == OperationMode::AUTO_TRACK && m_isTrackingActive) {
        m_fsmController->setTrackingInputs(xError, yError);
    }
}

void ControlLoop::handleFSMFeedbackUpdated(double x, double y)
{
    // This is called from the FSM controller thread, so need mutex
    QMutexLocker locker(&m_mutex);

    // Could implement additional logic based on FSM feedback
    // For now, feedback is used primarily for telemetry/display
}

void ControlLoop::controlLoopTick()
{
    QMutexLocker locker(&m_mutex);

    if (!m_running) {
        return;
    }

    // Get all current state for telemetry
    double fsmX, fsmY;
    m_fsmController->getCurrentPosition(fsmX, fsmY);

    double gimbalAz, gimbalEl, gimbalAuxEl;
    m_gimbalController->getCurrentPosition(gimbalAz, gimbalEl, gimbalAuxEl);

    double joystickX, joystickY, joystickZ;
    m_joystickInterface->getJoystickPosition(joystickX, joystickY, joystickZ);

    double trackErrorX, trackErrorY;
    m_trackerInterface->getTrackingErrors(trackErrorX, trackErrorY);

    // Emit telemetry update
    emit telemetryUpdated(
        fsmX, fsmY,
        gimbalAz, gimbalEl, gimbalAuxEl,
        joystickX, joystickY, joystickZ,
        trackErrorX, trackErrorY
    );
}

void ControlLoop::updateControlMode()
{
    // Set FSM controller mode based on operation mode
    FSMController::ControlMode fsmMode;
    switch (m_mode) {
        case OperationMode::COARSE_TRACK:
            fsmMode = FSMController::ControlMode::COARSE_TRACK;
            m_gimbalController->setEnabled(true);
            break;

        case OperationMode::FINE_TRACK:
            fsmMode = FSMController::ControlMode::FINE_TRACK;
            m_gimbalController->setEnabled(false);
            break;

        case OperationMode::AUTO_TRACK:
            fsmMode = FSMController::ControlMode::AUTO_TRACK;
            m_gimbalController->setEnabled(false);
            break;
    }

    m_fsmController->setControlMode(fsmMode);
}

void ControlLoop::cycleOperationMode()
{
    // Cycle to the next operation mode
    switch (m_mode) {
        case OperationMode::COARSE_TRACK:
            setOperationMode(OperationMode::FINE_TRACK);
            break;

        case OperationMode::FINE_TRACK:
            setOperationMode(OperationMode::AUTO_TRACK);
            break;

        case OperationMode::AUTO_TRACK:
            setOperationMode(OperationMode::COARSE_TRACK);
            break;
    }
}