#include "gimbal_controller.h"
#include <QDebug>
#include <cmath>

GimbalController::GimbalController(QObject *parent)
    : QObject(parent)
    , m_aoCtrl(nullptr)
    , m_azimuth(0.0)
    , m_elevation(0.0)
    , m_auxElevation(0.0)
    , m_enabled(false)
    , m_deviceNumber(1)  // Assuming device 1 for PCIE-1824
    , m_scaleFactor(10.0)  // +/- 10V range
{
}

GimbalController::~GimbalController()
{
    stop();

    if (m_aoCtrl) {
        m_aoCtrl->Dispose();
        m_aoCtrl = nullptr;
    }
}

bool GimbalController::initialize()
{
    // Set up analog output for controlling the gimbal
    if (!setupAnalogOutput()) {
        emit errorOccurred("Failed to initialize analog output for gimbal");
        return false;
    }

    emit statusChanged("Gimbal controller initialized");
    return true;
}

bool GimbalController::start()
{
    QMutexLocker locker(&m_mutex);
    m_enabled = true;
    updateOutputs();

    emit statusChanged("Gimbal controller started");
    return true;
}

bool GimbalController::stop()
{
    QMutexLocker locker(&m_mutex);
    m_enabled = false;

    // Set all outputs to zero
    if (m_aoCtrl) {
        double outputs[3] = {0.0, 0.0, 0.0};
        ErrorCode ret = m_aoCtrl->Write(0, 3, outputs);
        if (BioFailed(ret)) {
            emit errorOccurred(QString("Failed to zero gimbal outputs: %1").arg(getErrorString(ret)));
            return false;
        }
    }

    emit statusChanged("Gimbal controller stopped");
    return true;
}

bool GimbalController::reset()
{
    QMutexLocker locker(&m_mutex);
    
    // Stop first
    stop();
    
    // Reset all position values
    m_azimuth = 0.0;
    m_elevation = 0.0;
    m_auxElevation = 0.0;
    
    // Set outputs to zero again to be sure
    if (m_aoCtrl) {
        double outputs[3] = {0.0, 0.0, 0.0};
        ErrorCode ret = m_aoCtrl->Write(0, 3, outputs);
        if (BioFailed(ret)) {
            emit errorOccurred(QString("Failed to zero gimbal outputs: %1").arg(getErrorString(ret)));
            return false;
        }
    }
    
    emit statusChanged("Gimbal controller reset");
    return true;
}

bool GimbalController::isInitialized() const
{
    return (m_aoCtrl != nullptr);
}

void GimbalController::setPosition(double azimuth, double elevation, double auxElevation)
{
    QMutexLocker locker(&m_mutex);

    // Limit inputs to -1.0 to 1.0 range
    m_azimuth = std::max(-1.0, std::min(1.0, azimuth));
    m_elevation = std::max(-1.0, std::min(1.0, elevation));
    m_auxElevation = std::max(-1.0, std::min(1.0, auxElevation));

    // Update outputs if enabled
    if (m_enabled) {
        updateOutputs();
    }
}

void GimbalController::getCurrentPosition(double &azimuth, double &elevation, double &auxElevation)
{
    QMutexLocker locker(&m_mutex);
    azimuth = m_azimuth;
    elevation = m_elevation;
    auxElevation = m_auxElevation;
}

void GimbalController::setEnabled(bool enabled)
{
    QMutexLocker locker(&m_mutex);

    if (m_enabled == enabled) {
        return;  // No change
    }

    m_enabled = enabled;

    if (m_enabled) {
        // Update outputs with current position
        updateOutputs();
        emit statusChanged("Gimbal control enabled");
    } else {
        // Set all outputs to zero
        if (m_aoCtrl) {
            double outputs[3] = {0.0, 0.0, 0.0};
            ErrorCode ret = m_aoCtrl->Write(0, 3, outputs);
            if (BioFailed(ret)) {
                emit errorOccurred(QString("Failed to zero gimbal outputs: %1").arg(getErrorString(ret)));
            }
        }
        emit statusChanged("Gimbal control disabled");
    }
}

bool GimbalController::isEnabled() const
{
    QMutexLocker locker(&m_mutex);
    return m_enabled;
}

bool GimbalController::setupAnalogOutput()
{
    // Create a new instance of analog output control
    m_aoCtrl = InstantAoCtrl::Create();
    if (!m_aoCtrl) {
        emit errorOccurred("Failed to create Instant AO control for gimbal");
        return false;
    }

    // Set the device by enumeration
    DeviceInformation devInfo;
    devInfo.DeviceNumber = m_deviceNumber;
    ErrorCode ret = m_aoCtrl->setSelectedDevice(devInfo);
    if (BioFailed(ret)) {
        emit errorOccurred(QString("Failed to set gimbal AO device: %1").arg(getErrorString(ret)));
        return false;
    }

    // Check channels (need 3 for azimuth, elevation, aux elevation)
    int32 chCount = m_aoCtrl->getChannelCount();
    if (chCount < 3) {
        emit errorOccurred(QString("Not enough gimbal AO channels: %1 (needed: 3)").arg(chCount));
        return false;
    }

    // Set channel value ranges
    for (int i = 0; i < 3; i++) {
        m_aoCtrl->getChannels()->getItem(i).setValueRange(ValueRange::V_Neg10To10);
    }

    return true;
}

void GimbalController::updateOutputs()
{
    if (!m_aoCtrl || !m_enabled) {
        return;
    }

    // Scale normalized inputs to voltage
    double outputs[3] = {
        m_azimuth * m_scaleFactor,
        m_elevation * m_scaleFactor,
        m_auxElevation * m_scaleFactor
    };

    // Write values to the AO channels
    ErrorCode ret = m_aoCtrl->Write(0, 3, outputs);
    if (BioFailed(ret)) {
        emit errorOccurred(QString("Failed to write to gimbal outputs: %1").arg(getErrorString(ret)));
    }
}