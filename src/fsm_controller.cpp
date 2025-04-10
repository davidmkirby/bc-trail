#include "fsm_controller.h"
#include <QDebug>
#include <cmath>

// Error string helper function
QString getErrorString(ErrorCode errorCode) {
    char errorString[256] = {0};
    // Error codes in the Advantech DAQ system can be displayed as a negative number
    if (errorCode < 0) {
        snprintf(errorString, sizeof(errorString), "Error code: %d", (int)errorCode);
    } else {
        snprintf(errorString, sizeof(errorString), "Success code: %d", (int)errorCode);
    }
    return QString::fromLocal8Bit(errorString);
}

FSMController::FSMController(QObject *parent)
    : QObject(parent)
    , m_aoCtrl(nullptr)
    , m_aiCtrl(nullptr)
    , m_mode(ControlMode::COARSE_TRACK)
    , m_manualX(0.0)
    , m_manualY(0.0)
    , m_trackX(0.0)
    , m_trackY(0.0)
    , m_feedbackX(0.0)
    , m_feedbackY(0.0)
    , m_deviceNumber(0)
    , m_samplingRate(1000) // 1000 Hz
    , m_channelCount(2)    // X and Y channels
    , m_buffSize(1000)     // 1 second of data
    , m_scaleFactor(10.0)  // +/- 10V range
{
}

FSMController::~FSMController()
{
    stop();

    if (m_aoCtrl) {
        m_aoCtrl->Dispose();
        m_aoCtrl = nullptr;
    }

    if (m_aiCtrl) {
        m_aiCtrl->removeDataReadyHandler(OnBfdAiEvent, this);
        m_aiCtrl->removeStoppedHandler(OnBfdAiStopped, this);
        m_aiCtrl->Dispose();
        m_aiCtrl = nullptr;
    }
}

bool FSMController::initialize()
{
    // Set up analog output for controlling the FSM
    if (!setupAnalogOutput()) {
        emit errorOccurred("Failed to initialize analog output for FSM");
        return false;
    }

    // Set up analog input for FSM feedback
    if (!setupAnalogInput()) {
        emit errorOccurred("Failed to initialize analog input for FSM feedback");
        return false;
    }

    emit statusChanged("FSM controller initialized");
    return true;
}

bool FSMController::start()
{
    QMutexLocker locker(&m_mutex);

    // Start the analog input acquisition
    ErrorCode ret = m_aiCtrl->Start();
    if (BioFailed(ret)) {
        emit errorOccurred(QString("Failed to start FSM feedback acquisition: %1").arg(ret));
        return false;
    }

    emit statusChanged("FSM controller started");
    return true;
}

bool FSMController::stop()
{
    QMutexLocker locker(&m_mutex);

    // Stop the analog input acquisition
    if (m_aiCtrl) {
        ErrorCode ret = m_aiCtrl->Stop();
        if (BioFailed(ret)) {
            emit errorOccurred(QString("Failed to stop FSM feedback acquisition: %1").arg(ret));
            return false;
        }
    }

    emit statusChanged("FSM controller stopped");
    return true;
}

bool FSMController::reset()
{
    QMutexLocker locker(&m_mutex);
    
    // Stop first
    stop();
    
    // Reset all control values
    m_manualX = 0.0;
    m_manualY = 0.0;
    m_trackX = 0.0;
    m_trackY = 0.0;
    m_feedbackX = 0.0;
    m_feedbackY = 0.0;
    
    // Set outputs to zero
    updateOutputs();
    
    emit statusChanged("FSM controller reset");
    return true;
}

bool FSMController::isInitialized() const
{
    return (m_aoCtrl != nullptr && m_aiCtrl != nullptr);
}

void FSMController::setControlMode(ControlMode mode)
{
    QMutexLocker locker(&m_mutex);
    m_mode = mode;

    // Update outputs based on new mode
    updateOutputs();

    emit statusChanged(QString("FSM mode changed to %1")
                      .arg(mode == ControlMode::COARSE_TRACK ? "Coarse Track" :
                           mode == ControlMode::FINE_TRACK ? "Fine Track" : "Auto Track"));
}

FSMController::ControlMode FSMController::getControlMode() const
{
    QMutexLocker locker(&m_mutex);
    return m_mode;
}

void FSMController::setManualInputs(double x, double y)
{
    QMutexLocker locker(&m_mutex);

    // Limit inputs to -1.0 to 1.0 range
    m_manualX = std::max(-1.0, std::min(1.0, x));
    m_manualY = std::max(-1.0, std::min(1.0, y));

    // Update outputs based on new inputs
    if (m_mode == ControlMode::COARSE_TRACK || m_mode == ControlMode::FINE_TRACK) {
        updateOutputs();
    }
}

void FSMController::setTrackingInputs(double x, double y)
{
    QMutexLocker locker(&m_mutex);

    // Limit inputs to -1.0 to 1.0 range
    m_trackX = std::max(-1.0, std::min(1.0, x));
    m_trackY = std::max(-1.0, std::min(1.0, y));

    // Update outputs based on new inputs if in auto track mode
    if (m_mode == ControlMode::AUTO_TRACK) {
        updateOutputs();
    }
}

void FSMController::getCurrentPosition(double &x, double &y)
{
    QMutexLocker locker(&m_mutex);
    x = m_feedbackX;
    y = m_feedbackY;
}

void FSMController::onAiDataReady(void *sender, BfdAiEventArgs *args)
{
    // Get the data
    int32 count = args->Count;
    double *rawData = new double[count * m_channelCount];

    ErrorCode ret = m_aiCtrl->GetData(count, rawData);
    if (BioFailed(ret)) {
        emit errorOccurred(QString("Failed to get FSM feedback data: %1").arg(ret));
        delete[] rawData;
        return;
    }

    // Process the data
    processAnalogInput(rawData, count);

    delete[] rawData;
}

bool FSMController::setupAnalogOutput()
{
    // Create a new instance of analog output control
    m_aoCtrl = InstantAoCtrl::Create();
    if (!m_aoCtrl) {
        emit errorOccurred("Failed to create Instant AO control");
        return false;
    }

    // Set the device by enumeration
    DeviceInformation devInfo;
    devInfo.DeviceNumber = m_deviceNumber;
    ErrorCode ret = m_aoCtrl->setSelectedDevice(devInfo);
    if (BioFailed(ret)) {
        emit errorOccurred(QString("Failed to set AO device: %1").arg(getErrorString(ret)));
        return false;
    }

    // Check channels
    int32 chCount = m_aoCtrl->getChannelCount();
    if (chCount < m_channelCount) {
        emit errorOccurred(QString("Not enough AO channels: %1 (needed: %2)").arg(chCount).arg(m_channelCount));
        return false;
    }

    // Set channel value ranges
    for (int i = 0; i < m_channelCount; i++) {
        m_aoCtrl->getChannels()->getItem(i).setValueRange(ValueRange::V_Neg10To10);
    }

    return true;
}

bool FSMController::setupAnalogInput()
{
    // Create a new instance of buffered analog input control
    m_aiCtrl = BufferedAiCtrl::Create();
    if (!m_aiCtrl) {
        emit errorOccurred("Failed to create Buffered AI control");
        return false;
    }

    // Set the device by enumeration
    DeviceInformation devInfo;
    devInfo.DeviceNumber = m_deviceNumber;
    ErrorCode ret = m_aiCtrl->setSelectedDevice(devInfo);
    if (BioFailed(ret)) {
        emit errorOccurred(QString("Failed to set AI device: %1").arg(getErrorString(ret)));
        return false;
    }

    // Configure the conversion clock
    ConvertClock* convertClock = m_aiCtrl->getConvertClock();
    ret = convertClock->setRate(m_samplingRate);
    if (BioFailed(ret)) {
        emit errorOccurred(QString("Failed to set AI sampling rate: %1").arg(getErrorString(ret)));
        return false;
    }

    // Get device name using device number
    QString devName = QString("Device #%1").arg(m_deviceNumber);
    emit statusChanged(QString("Using device: %1").arg(devName));

    // Set up the trigger
    ScanChannel* scanChannel = m_aiCtrl->getScanChannel();
    ret = scanChannel->setChannelCount(m_channelCount);
    if (BioFailed(ret)) {
        emit errorOccurred(QString("Failed to set AI scan channel count: %1").arg(getErrorString(ret)));
        return false;
    }
    
    // Set up the trigger
    Trigger* trigger = m_aiCtrl->getTrigger();
    ret = trigger->setSource(SignalNone); // Use 'None' from the library
    if (BioFailed(ret)) {
        emit errorOccurred(QString("Failed to set AI trigger source: %1").arg(getErrorString(ret)));
        return false;
    }
    
    ret = trigger->setAction(DelayToStart); // Use 'DelayToStart' from the library
    if (BioFailed(ret)) {
        emit errorOccurred(QString("Failed to set AI trigger action: %1").arg(getErrorString(ret)));
        return false;
    }
    
    ret = trigger->setDelayCount(0);
    if (BioFailed(ret)) {
        emit errorOccurred(QString("Failed to set AI trigger delay: %1").arg(getErrorString(ret)));
        return false;
    }

    // Set up event handlers
    m_aiCtrl->addDataReadyHandler(OnBfdAiEvent, this);
    emit statusChanged("AI data ready handler registered");
    
    m_aiCtrl->addStoppedHandler(OnBfdAiStopped, this);
    emit statusChanged("AI stopped handler registered");

    // Set up the channels
    for (int i = 0; i < m_channelCount; i++) {
        m_aiCtrl->getChannels()->getItem(i).setValueRange(ValueRange::V_Neg10To10);
    }

    return true;
}

void FSMController::processAnalogInput(double *data, int32 count)
{
    QMutexLocker locker(&m_mutex);

    // We just process the latest sample in the buffer
    if (count > 0) {
        int lastIdx = (count - 1) * m_channelCount;

        // Scale data from voltage to normalized -1.0 to 1.0
        m_feedbackX = data[lastIdx] / m_scaleFactor;
        m_feedbackY = data[lastIdx + 1] / m_scaleFactor;

        // Emit the feedback updated signal
        emit feedbackUpdated(m_feedbackX, m_feedbackY);
    }
}

void FSMController::updateOutputs()
{
    if (!m_aoCtrl) {
        return;
    }

    double outputs[2] = {0.0, 0.0};

    // Calculate outputs based on mode
    switch (m_mode) {
        case ControlMode::COARSE_TRACK:
        case ControlMode::FINE_TRACK:
            // In manual modes, use joystick input
            outputs[0] = m_manualX * m_scaleFactor;
            outputs[1] = m_manualY * m_scaleFactor;
            break;

        case ControlMode::AUTO_TRACK:
            // In auto mode, use tracking input
            outputs[0] = m_trackX * m_scaleFactor;
            outputs[1] = m_trackY * m_scaleFactor;
            break;
    }

    // Write values to the AO channels
    ErrorCode ret = m_aoCtrl->Write(0, m_channelCount, outputs);
    if (BioFailed(ret)) {
        emit errorOccurred(QString("Failed to write to FSM outputs: %1").arg(ret));
    }
}

void BDAQCALL FSMController::OnBfdAiEvent(void *sender, BfdAiEventArgs *args, void *userParam)
{
    // Forward the callback to the instance method
    if (userParam) {
        FSMController *instance = static_cast<FSMController*>(userParam);
        instance->onAiDataReady(sender, args);
    }
}

void BDAQCALL FSMController::OnBfdAiStopped(void *sender, BfdAiEventArgs *args, void *userParam)
{
    // When the AI acquisition is stopped, notify the FSMController
    if (userParam) {
        FSMController *instance = static_cast<FSMController*>(userParam);
        // Notify that the acquisition has stopped
        QMetaObject::invokeMethod(instance, "statusChanged", 
                                 Qt::QueuedConnection,
                                 Q_ARG(QString, "FSM feedback acquisition stopped"));
    }
}
