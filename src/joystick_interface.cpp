#include "joystick_interface.h"
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <SDL2/SDL.h>

JoystickInterface::JoystickInterface(QObject *parent)
    : QObject(parent)
    , m_pollTimer(new QTimer(this))
    , m_currentJoystick(nullptr)
    , m_sdlInitialized(false)
    , m_x(0.0)
    , m_y(0.0)
    , m_z(0.0)
    , m_rx(0.0)
    , m_ry(0.0)
    , m_rz(0.0)
    , m_buttonState(0)
    , m_running(false)
{
    // Set up poll timer with 60Hz rate
    m_pollTimer->setInterval(POLLING_RATE_MS);
    connect(m_pollTimer, &QTimer::timeout, this, &JoystickInterface::pollEvents);
}

JoystickInterface::~JoystickInterface()
{
    stop();

    if (m_sdlInitialized) {
        // Ensure SDL is properly shut down
        closeJoystick();
        SDL_Quit();
        m_sdlInitialized = false;
    }
}

bool JoystickInterface::initialize()
{
    // Initialize SDL for joystick subsystem
    if (SDL_Init(SDL_INIT_JOYSTICK) < 0) {
        emit errorOccurred(QString("SDL could not initialize! Error: %1").arg(SDL_GetError()));
        return false;
    }

    m_sdlInitialized = true;

    // Enable joystick events
    SDL_JoystickEventState(SDL_ENABLE);

    // Scan for available joysticks
    scanJoysticks();

    emit errorOccurred("Joystick interface initialized");
    return true;
}

void JoystickInterface::scanJoysticks()
{
    QMutexLocker locker(&m_mutex);
    m_availableJoysticks.clear();

    int numJoysticks = SDL_NumJoysticks();
    for (int i = 0; i < numJoysticks; i++) {
        const char* name = SDL_JoystickNameForIndex(i);
        if (name) {
            m_availableJoysticks[i] = QString::fromUtf8(name);
        } else {
            m_availableJoysticks[i] = QString("Joystick %1").arg(i);
        }
    }

    emit joysticksChanged();
}

QStringList JoystickInterface::getAvailableJoysticks() const
{
    QMutexLocker locker(&m_mutex);
    QStringList result;
    for (auto it = m_availableJoysticks.constBegin(); it != m_availableJoysticks.constEnd(); ++it) {
        result << it.value();
    }
    return result;
}

int JoystickInterface::openJoystick(int index)
{
    QMutexLocker locker(&m_mutex);

    // Close any existing joystick first
    closeJoystick();

    m_currentJoystick = SDL_JoystickOpen(index);
    if (!m_currentJoystick) {
        emit errorOccurred(QString("Couldn't open joystick %1: %2").arg(index).arg(SDL_GetError()));
        return -1;
    }

    // Initialize calibration for this joystick
    calibrateAxes();

    // Initialize hat state array
    int numHats = SDL_JoystickNumHats(m_currentJoystick);
    m_hatState.resize(numHats);
    for (int i = 0; i < numHats; ++i) {
        m_hatState[i] = SDL_HAT_CENTERED;
    }

    emit errorOccurred(QString("Opened joystick: %1").arg(getJoystickName()));
    return index;
}

void JoystickInterface::closeJoystick()
{
    QMutexLocker locker(&m_mutex);

    if (m_currentJoystick) {
        SDL_JoystickClose(m_currentJoystick);
        m_currentJoystick = nullptr;
    }

    // Clear calibration data
    m_axisCalibration.clear();

    // Clear hat state data
    m_hatState.clear();
}

bool JoystickInterface::isJoystickOpen() const
{
    QMutexLocker locker(&m_mutex);
    return m_currentJoystick != nullptr;
}

int JoystickInterface::getNumAxes() const
{
    QMutexLocker locker(&m_mutex);
    if (!m_currentJoystick) return 0;
    return SDL_JoystickNumAxes(m_currentJoystick);
}

int JoystickInterface::getNumButtons() const
{
    QMutexLocker locker(&m_mutex);
    if (!m_currentJoystick) return 0;
    return SDL_JoystickNumButtons(m_currentJoystick);
}

int JoystickInterface::getNumHats() const
{
    QMutexLocker locker(&m_mutex);
    if (!m_currentJoystick) return 0;
    return SDL_JoystickNumHats(m_currentJoystick);
}

QString JoystickInterface::getJoystickName() const
{
    QMutexLocker locker(&m_mutex);
    if (!m_currentJoystick) return QString();

    const char* name = SDL_JoystickName(m_currentJoystick);
    if (name) {
        return QString::fromUtf8(name);
    }
    return QString("Unknown Joystick");
}

bool JoystickInterface::start()
{
    QMutexLocker locker(&m_mutex);

    if (m_running) {
        return true; // Already running
    }

    if (!m_sdlInitialized) {
        emit errorOccurred("Cannot start joystick interface: not initialized");
        return false;
    }

    if (!m_currentJoystick) {
        // Try to open the first available joystick if none is open
        if (!m_availableJoysticks.isEmpty()) {
            openJoystick(m_availableJoysticks.firstKey());
        } else {
            emit errorOccurred("Cannot start joystick interface: no joysticks available");
            return false;
        }
    }

    // Start the polling timer
    m_running = true;
    m_pollTimer->start();

    emit errorOccurred("Joystick interface started");
    return true;
}

bool JoystickInterface::stop()
{
    QMutexLocker locker(&m_mutex);

    if (!m_running) {
        return true; // Already stopped
    }

    // Stop the polling timer
    m_pollTimer->stop();
    m_running = false;

    emit errorOccurred("Joystick interface stopped");
    return true;
}

void JoystickInterface::refreshJoysticks()
{
    // Rescan for available joysticks
    scanJoysticks();
}

void JoystickInterface::pollEvents()
{
    if (!m_sdlInitialized || !m_running) {
        return;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_JOYAXISMOTION: {
                QMutexLocker locker(&m_mutex);
                int axis = event.jaxis.axis;
                int rawValue = event.jaxis.value;

                // Apply calibration and normalization
                double normalizedValue = normalizeAxisValue(axis, rawValue);

                // Map to our position/rotation structure
                mapAxisToPositionOrRotation(axis, normalizedValue);
                break;
            }

            case SDL_JOYBUTTONDOWN: {
                QMutexLocker locker(&m_mutex);
                int button = event.jbutton.button;

                // Update button state
                m_buttonState |= (1 << button);

                // Emit signals
                emit buttonStateChanged(button, true);

                // Special handling for mode button
                if (button == static_cast<int>(Button::MODE_SWITCH)) {
                    emit modeButtonPressed();
                }
                break;
            }

            case SDL_JOYBUTTONUP: {
                QMutexLocker locker(&m_mutex);
                int button = event.jbutton.button;

                // Update button state
                m_buttonState &= ~(1 << button);

                // Emit signal
                emit buttonStateChanged(button, false);
                break;
            }

            case SDL_JOYHATMOTION: {
                QMutexLocker locker(&m_mutex);
                int hat = event.jhat.hat;
                int value = event.jhat.value;

                // Update hat state
                if (hat < m_hatState.size()) {
                    m_hatState[hat] = value;
                }

                // Emit hat changed signal
                emit hatStateChanged(hat, value);
                break;
            }

            case SDL_JOYDEVICEADDED:
            case SDL_JOYDEVICEREMOVED:
                // Device was added or removed, update joystick list
                scanJoysticks();
                break;
        }
    }
}

void JoystickInterface::calibrateAxes()
{
    QMutexLocker locker(&m_mutex);

    if (!m_currentJoystick) {
        return;
    }

    int numAxes = SDL_JoystickNumAxes(m_currentJoystick);
    m_axisCalibration.clear();

    // Initialize calibration with current values as center
    for (int i = 0; i < numAxes; ++i) {
        int currentValue = SDL_JoystickGetAxis(m_currentJoystick, i);
        AxisCalibration cal;
        cal.min = -32768;
        cal.max = 32767;
        cal.center = currentValue; // Use current position as center
        cal.calibrated = true;
        m_axisCalibration.append(cal);

        qDebug() << "Calibrated axis" << i << "center:" << cal.center;
    }
}

double JoystickInterface::normalizeAxisValue(int axis, int value) const
{
    // Apply calibration if available
    if (axis < m_axisCalibration.size() && m_axisCalibration[axis].calibrated) {
        // Subtract center value to adjust for drift
        int adjustedValue = value - m_axisCalibration[axis].center;

        // Normalize to -1.0 to 1.0 range
        if (adjustedValue > 0) {
            return static_cast<double>(adjustedValue) / (32767 - m_axisCalibration[axis].center);
        } else {
            return static_cast<double>(adjustedValue) / (32768 + m_axisCalibration[axis].center);
        }
    }

    // Default normalization if no calibration
    return static_cast<double>(value) / 32767.0;
}

void JoystickInterface::mapAxisToPositionOrRotation(int axis, double value)
{
    // Map axis to appropriate position or rotation variable
    // We use a simple default mapping based on common joystick layouts
    switch (axis) {
        case DEFAULT_X_AXIS: // X axis
            m_x = value;
            break;
        case DEFAULT_Y_AXIS: // Y axis
            m_y = value;
            break;
        case DEFAULT_Z_AXIS: // Z axis
            m_z = value;
            break;
        case DEFAULT_RX_AXIS: // RX axis
            m_rx = value;
            break;
        case DEFAULT_RY_AXIS: // RY axis
            m_ry = value;
            break;
        case DEFAULT_RZ_AXIS: // RZ axis
            m_rz = value;
            break;
    }

    // Emit the appropriate signals based on which axis changed
    if (axis <= DEFAULT_Z_AXIS) {
        emit joystickPositionChanged(m_x, m_y, m_z);
    } else {
        emit joystickRotationChanged(m_rx, m_ry, m_rz);
    }
}

void JoystickInterface::getJoystickPosition(double &x, double &y, double &z)
{
    QMutexLocker locker(&m_mutex);
    x = m_x;
    y = m_y;
    z = m_z;
}

void JoystickInterface::getJoystickRotation(double &rx, double &ry, double &rz)
{
    QMutexLocker locker(&m_mutex);
    rx = m_rx;
    ry = m_ry;
    rz = m_rz;
}

int JoystickInterface::getHatPosition(int hat) const
{
    QMutexLocker locker(&m_mutex);
    if (!m_currentJoystick || hat >= m_hatState.size()) return HAT_CENTERED;
    return m_hatState[hat];
}

QString JoystickInterface::hatPositionToString(int value)
{
    switch (value) {
        case HAT_CENTERED: return "Centered";
        case HAT_UP: return "Up";
        case HAT_RIGHT: return "Right";
        case HAT_DOWN: return "Down";
        case HAT_LEFT: return "Left";
        case HAT_RIGHTUP: return "Right+Up";
        case HAT_RIGHTDOWN: return "Right+Down";
        case HAT_LEFTUP: return "Left+Up";
        case HAT_LEFTDOWN: return "Left+Down";
        default: return "Unknown";
    }
}

bool JoystickInterface::isButtonPressed(int button) const
{
    QMutexLocker locker(&m_mutex);
    uint32_t mask = 1 << button;
    return (m_buttonState & mask) != 0;
}