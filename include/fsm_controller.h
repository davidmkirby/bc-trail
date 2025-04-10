#ifndef FSM_CONTROLLER_H
#define FSM_CONTROLLER_H

#include <QObject>
#include <QMutex>
#include <memory>
#include "bdaqctrl.h"

using namespace Automation::BDaq;

// Forward declaration of error string function
QString getErrorString(ErrorCode errorCode);

class FSMController : public QObject
{
    Q_OBJECT

public:
    enum class ControlMode {
        COARSE_TRACK,  // Manual control of both gimbal and FSM
        FINE_TRACK,    // Manual control of FSM only
        AUTO_TRACK     // Automatic tracking using tracker card data
    };

    explicit FSMController(QObject *parent = nullptr);
    ~FSMController();

    bool initialize();
    bool start();
    bool stop();
    bool reset();
    bool isInitialized() const;

    void setControlMode(ControlMode mode);
    ControlMode getControlMode() const;

    // Manual control inputs (-1.0 to 1.0 range)
    void setManualInputs(double x, double y);

    // Tracking inputs from tracker card (-1.0 to 1.0 range)
    void setTrackingInputs(double x, double y);

    // Get current FSM position feedback
    void getCurrentPosition(double &x, double &y);

signals:
    void statusChanged(const QString &message);
    void errorOccurred(const QString &error);
    void feedbackUpdated(double x, double y);

private slots:
    void onAiDataReady(void *sender, BfdAiEventArgs *args);

private:
    // Helper methods
    bool setupAnalogInput();
    bool setupAnalogOutput();
    void processAnalogInput(double *data, int32 count);
    void updateOutputs();

    // Callback wrapper
    static void BDAQCALL OnBfdAiEvent(void *sender, BfdAiEventArgs *args, void *userParam);
    static void BDAQCALL OnBfdAiStopped(void *sender, BfdAiEventArgs *args, void *userParam);

    // DAQ device objects
    InstantAoCtrl *m_aoCtrl;
    BufferedAiCtrl *m_aiCtrl;

    // Control state
    ControlMode m_mode;
    double m_manualX;
    double m_manualY;
    double m_trackX;
    double m_trackY;
    double m_feedbackX;
    double m_feedbackY;

    // Thread synchronization
    mutable QMutex m_mutex;

    // Device configuration
    int m_deviceNumber;
    int m_samplingRate;
    int m_channelCount;
    int m_buffSize;
    double m_scaleFactor;
};

#endif // FSM_CONTROLLER_H
