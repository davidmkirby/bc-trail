#ifndef JOYSTICK_INTERFACE_H
#define JOYSTICK_INTERFACE_H

#include <QObject>
#include <QMutex>
#include <QTimer>
#include <QVector>
#include <QMap>
#include <QString>
#include <SDL2/SDL.h>

/**
 * @brief Interface for joystick input and control.
 *
 * This class provides a unified interface for joystick control using SDL2,
 * supporting multiple devices, calibration, and comprehensive input mapping.
 */
class JoystickInterface : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Button identifiers for commonly used joystick buttons
     */
    enum class Button {
        MODE_SWITCH = 0,
        RESET = 1,
        ACTION = 2,
        START = 3,
        // Add more buttons as needed
    };

    /**
     * @brief Hat position constants from SDL
     */
    enum HatPosition {
        HAT_CENTERED = SDL_HAT_CENTERED,
        HAT_UP = SDL_HAT_UP,
        HAT_RIGHT = SDL_HAT_RIGHT,
        HAT_DOWN = SDL_HAT_DOWN,
        HAT_LEFT = SDL_HAT_LEFT,
        HAT_RIGHTUP = SDL_HAT_RIGHTUP,
        HAT_RIGHTDOWN = SDL_HAT_RIGHTDOWN,
        HAT_LEFTUP = SDL_HAT_LEFTUP,
        HAT_LEFTDOWN = SDL_HAT_LEFTDOWN
    };

    /**
     * @brief Construct a new Joystick Interface object
     *
     * @param parent The parent QObject
     */
    explicit JoystickInterface(QObject *parent = nullptr);

    /**
     * @brief Destroy the Joystick Interface object
     */
    ~JoystickInterface();

    /**
     * @brief Initialize the joystick interface
     *
     * @return true If initialization was successful
     * @return false If initialization failed
     */
    bool initialize();

    /**
     * @brief Start the joystick polling
     *
     * @return true If started successfully
     * @return false If start failed
     */
    bool start();

    /**
     * @brief Stop the joystick polling
     *
     * @return true If stopped successfully
     * @return false If stop failed
     */
    bool stop();

    /**
     * @brief Get available joysticks connected to the system
     *
     * @return QStringList List of available joystick names
     */
    QStringList getAvailableJoysticks() const;

    /**
     * @brief Open a specific joystick by index
     *
     * @param index The index of the joystick to open
     * @return int The index of the opened joystick or -1 on failure
     */
    int openJoystick(int index);

    /**
     * @brief Close the currently open joystick
     */
    void closeJoystick();

    /**
     * @brief Check if a joystick is currently open
     *
     * @return true If a joystick is open
     * @return false If no joystick is open
     */
    bool isJoystickOpen() const;

    /**
     * @brief Get the name of the currently open joystick
     *
     * @return QString The joystick name or empty string if none open
     */
    QString getJoystickName() const;

    /**
     * @brief Get the number of axes on the current joystick
     *
     * @return int Number of axes or 0 if no joystick open
     */
    int getNumAxes() const;

    /**
     * @brief Get the number of buttons on the current joystick
     *
     * @return int Number of buttons or 0 if no joystick open
     */
    int getNumButtons() const;

    /**
     * @brief Get the number of hats on the current joystick
     *
     * @return int Number of hats or 0 if no joystick open
     */
    int getNumHats() const;

    /**
     * @brief Get joystick position axes in normalized range (-1.0 to 1.0)
     *
     * @param x Output parameter for X axis position
     * @param y Output parameter for Y axis position
     * @param z Output parameter for Z axis position
     */
    void getJoystickPosition(double &x, double &y, double &z);

    /**
     * @brief Get joystick rotation axes in normalized range (-1.0 to 1.0)
     *
     * @param rx Output parameter for X rotation
     * @param ry Output parameter for Y rotation
     * @param rz Output parameter for Z rotation
     */
    void getJoystickRotation(double &rx, double &ry, double &rz);

    /**
     * @brief Get the current hat position value
     *
     * @param hat The hat index to check
     * @return int The hat position value, see HatPosition enum
     */
    int getHatPosition(int hat) const;

    /**
     * @brief Convert hat position value to human-readable string
     *
     * @param value The hat position value
     * @return QString Human-readable description of the hat position
     */
    static QString hatPositionToString(int value);

    /**
     * @brief Check if a specific button is pressed
     *
     * @param button The button to check
     * @return true If the button is pressed
     * @return false If the button is not pressed
     */
    bool isButtonPressed(Button button) const;

    /**
     * @brief Check if a specific button is pressed by index
     *
     * @param button The button index to check
     * @return true If the button is pressed
     * @return false If the button is not pressed
     */
    bool isButtonPressed(int button) const;

    /**
     * @brief Calibrate joystick axes to correct for center offset
     */
    void calibrateAxes();

signals:
    /**
     * @brief Signal emitted when joystick position changes
     *
     * @param x X position in range -1.0 to 1.0
     * @param y Y position in range -1.0 to 1.0
     * @param z Z position in range -1.0 to 1.0
     */
    void joystickPositionChanged(double x, double y, double z);

    /**
     * @brief Signal emitted when joystick rotation changes
     *
     * @param rx X rotation in range -1.0 to 1.0
     * @param ry Y rotation in range -1.0 to 1.0
     * @param rz Z rotation in range -1.0 to 1.0
     */
    void joystickRotationChanged(double rx, double ry, double rz);

    /**
     * @brief Signal emitted when a button state changes
     *
     * @param button Button number
     * @param pressed true if pressed, false if released
     */
    void buttonStateChanged(int button, bool pressed);

    /**
     * @brief Signal emitted when a hat (d-pad) state changes
     *
     * @param hat Hat number
     * @param value Hat position value
     */
    void hatStateChanged(int hat, int value);

    /**
     * @brief Signal emitted when the mode button is pressed
     */
    void modeButtonPressed();

    /**
     * @brief Signal emitted when the list of available joysticks changes
     */
    void joysticksChanged();

    /**
     * @brief Signal emitted when an error occurs
     *
     * @param error Error message
     */
    void errorOccurred(const QString &error);

public slots:
    /**
     * @brief Refresh the list of available joysticks
     */
    void refreshJoysticks();

private slots:
    /**
     * @brief Poll for joystick events
     */
    void pollEvents();

private:
    /**
     * @brief Scan for available joysticks
     */
    void scanJoysticks();

    /**
     * @brief Convert raw axis value to normalized position
     *
     * @param axis Axis number
     * @param value Raw axis value
     * @return double Normalized value (-1.0 to 1.0)
     */
    double normalizeAxisValue(int axis, int value) const;

    /**
     * @brief Map SDL axis numbers to our position/rotation structure
     *
     * @param axis SDL axis number
     * @param value Normalized axis value
     */
    void mapAxisToPositionOrRotation(int axis, double value);

    // SDL joystick polling timer
    QTimer *m_pollTimer;

    // SDL joystick handle
    SDL_Joystick *m_currentJoystick;

    // Map of available joysticks (index -> name)
    QMap<int, QString> m_availableJoysticks;

    // SDL initialization state
    bool m_sdlInitialized;

    // Axis calibration structure
    struct AxisCalibration {
        int min;       // Minimum value
        int max;       // Maximum value
        int center;    // Center value
        bool calibrated; // Whether calibration has been performed
    };

    // Calibration data for each axis
    QVector<AxisCalibration> m_axisCalibration;

    // Joystick state - position axes
    double m_x, m_y, m_z;

    // Joystick state - rotation axes
    double m_rx, m_ry, m_rz;

    // Hat state - array of hat positions
    QVector<int> m_hatState;

    // Button state bitmap
    uint32_t m_buttonState;

    // Mutex for thread safety
    mutable QMutex m_mutex;

    // Running state
    bool m_running;

    // Polling rate in milliseconds
    static const int POLLING_RATE_MS = 16; // ~60Hz

    // Default axis mappings (can be overridden in configuration)
    static const int DEFAULT_X_AXIS = 0;
    static const int DEFAULT_Y_AXIS = 1;
    static const int DEFAULT_Z_AXIS = 2;
    static const int DEFAULT_RX_AXIS = 3;
    static const int DEFAULT_RY_AXIS = 4;
    static const int DEFAULT_RZ_AXIS = 5;
};

#endif // JOYSTICK_INTERFACE_H
