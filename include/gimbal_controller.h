#ifndef GIMBAL_CONTROLLER_H
#define GIMBAL_CONTROLLER_H

#include <QObject>
#include <QMutex>
#include "bdaqctrl.h"

using namespace Automation::BDaq;

// Forward declaration of error string function
QString getErrorString(ErrorCode errorCode);

class GimbalController : public QObject
{
    Q_OBJECT

public:
    explicit GimbalController(QObject *parent = nullptr);
    ~GimbalController();

    bool initialize();
    bool start();
    bool stop();
    bool reset();
    bool isInitialized() const;

    // Set gimbal position commands (-1.0 to 1.0 range)
    void setPosition(double azimuth, double elevation, double auxElevation);

    // Get current gimbal position
    void getCurrentPosition(double &azimuth, double &elevation, double &auxElevation);

    // Enable/disable gimbal control
    void setEnabled(bool enabled);
    bool isEnabled() const;

signals:
    void statusChanged(const QString &message);
    void errorOccurred(const QString &error);

private:
    // Helper methods
    bool setupAnalogOutput();
    void updateOutputs();

    // DAQ device objects
    InstantAoCtrl *m_aoCtrl;

    // Control state
    double m_azimuth;
    double m_elevation;
    double m_auxElevation;
    bool m_enabled;

    // Thread synchronization
    mutable QMutex m_mutex;

    // Device configuration
    int m_deviceNumber;
    double m_scaleFactor;
};

#endif // GIMBAL_CONTROLLER_H