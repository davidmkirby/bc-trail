#ifndef TRACKER_INTERFACE_H
#define TRACKER_INTERFACE_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QTimer>
#include <atomic>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

// Memory offset definitions
#define COMMAND_MAILBOX_OFFSET 0x000  // Command mailbox register
#define STATUS_MAILBOX_OFFSET  0x002  // Status mailbox register
#define COMMAND_MESSAGE_OFFSET 0x020  // Command message buffer start
#define STATUS_MESSAGE_OFFSET  0x100  // Status message buffer start

// Polling rate in milliseconds (4ms = 250Hz)
#define TRACKER_POLLING_RATE_MS 4

/**
 * @brief Structure to hold tracker data received from the EO Imaging 7007 tracker card
 */
struct TrackData {
    float rawErrorX;     // Raw X error from tracker (-1.0 to 1.0)
    float rawErrorY;     // Raw Y error from tracker (-1.0 to 1.0)
    uint16_t trackState; // Tracking state bits
    uint16_t status;     // Status word

    // Helper method to determine if currently tracking
    bool isTracking() const {
        return (trackState == 4); // Track state 4 = tracking active
    }
};

/**
 * @brief Interface for communicating with the EO Imaging 7007 Tracker card.
 *
 * This class provides memory-mapped I/O to interact with the 7007 tracker card.
 * It implements a thread-based polling architecture to read track data at 250Hz.
 */
class TrackerInterface : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent The parent QObject
     */
    explicit TrackerInterface(QObject *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~TrackerInterface();

    /**
     * @brief Initialize the tracker interface with the specified memory parameters
     * @param baseAddress The physical base address of the tracker card memory
     * @param memSize The size of the memory region to map
     * @param pciBus The PCI bus number of the tracker card (usually 0x98)
     * @param pciSlot The PCI slot number of the tracker card
     * @param pciFunc The PCI function number of the tracker card
     * @return True if initialization was successful
     */
    bool initialize(uintptr_t baseAddress = 0xdba00000, size_t memSize = 0x0800,
                   uint8_t pciBus = 0x98, uint8_t pciSlot = 0x00, uint8_t pciFunc = 0x00);

    /**
     * @brief Start the tracker polling thread
     * @return True if started successfully
     */
    bool start();

    /**
     * @brief Stop the tracker polling thread
     * @return True if stopped successfully
     */
    bool stop();

    /**
     * @brief Get the current tracking errors
     * @param xError Output parameter for X tracking error
     * @param yError Output parameter for Y tracking error
     */
    void getTrackingErrors(double &xError, double &yError);

    /**
     * @brief Get the current tracking errors and state
     * @param xError Output parameter for X tracking error
     * @param yError Output parameter for Y tracking error
     * @param state Output parameter for tracking state
     * @return True if the operation was successful
     */
    bool getTrackingError(double &xError, double &yError, QString &state);

    /**
     * @brief Check if target is being tracked
     * @return True if the target is currently being tracked
     */
    bool isTargetTracked() const;

    /**
     * @brief Send a ping message to the tracker to verify communication
     * @return True if ping was successful
     */
    bool ping();

signals:
    /**
     * @brief Signal emitted when tracking errors are updated
     * @param xError The X-axis error (-1.0 to 1.0)
     * @param yError The Y-axis error (-1.0 to 1.0)
     */
    void trackingErrorsUpdated(double xError, double yError);

    /**
     * @brief Signal emitted when tracking status changes
     * @param isTracking True if the tracker is currently tracking
     */
    void trackingStatusChanged(bool isTracking);

    /**
     * @brief Signal emitted when the interface status changes
     * @param status Status message
     */
    void statusChanged(const QString &status);

    /**
     * @brief Signal emitted when an error occurs
     * @param error Error message
     */
    void errorOccurred(const QString &error);

private:
    // Thread function to poll the tracker at 250Hz
    void trackerPollingThread();

    // PCI configuration method
    bool configurePCIDevice();

    // Memory mapping methods
    bool setupMemoryMapping();
    void cleanupMemoryMapping();

    // Low-level memory access methods
    uint16_t readWord(size_t offset);
    void writeWord(size_t offset, uint16_t value);

    // Tracker data methods
    bool readStatusData(TrackData &data);
    bool isReadyForCommand();

    // Helper method to calculate checksum
    uint16_t calculateChecksum(const uint16_t* data, size_t words);

    // File descriptor for memory mapping
    int m_fd;

    // Mapped memory pointer
    void* m_mappedMem;

    // Memory size and base address
    size_t m_memSize;
    uintptr_t m_baseAddress;

    // PCI device location
    uint8_t m_pciBus;
    uint8_t m_pciSlot;
    uint8_t m_pciFunc;

    // Thread for polling the tracker
    QThread m_pollingThread;

    // State variables
    bool m_initialized;
    bool m_running;
    bool m_isTracking;

    // Tracking error values
    double m_xError;
    double m_yError;

    // Mutex for thread safety
    mutable QMutex m_mutex;
};

#endif // TRACKER_INTERFACE_H