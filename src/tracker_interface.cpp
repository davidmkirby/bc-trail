#include "tracker_interface.h"
#include <QDebug>
#include <QObject>
#include <QEventLoop>
#include <QTimer>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <cstring>
#include <cmath>
#include <cstdlib>   // For system()

// Dummy definitions for the tracker card interface
// These would be replaced with actual definitions from the Moog 7007 API
#define TRACKER_DEVICE "/dev/eoimaging0"
#define TRACKER_IOC_GET_STATUS _IOR('T', 1, int)
#define TRACKER_IOC_GET_X_ERROR _IOR('T', 2, double)
#define TRACKER_IOC_GET_Y_ERROR _IOR('T', 3, double)

TrackerInterface::TrackerInterface(QObject *parent)
    : QObject(parent)
    , m_fd(-1)
    , m_mappedMem(nullptr)
    , m_memSize(0)
    , m_baseAddress(0)
    , m_initialized(false)
    , m_pciBus(0x98)
    , m_pciSlot(0x00)
    , m_pciFunc(0x00)
    , m_running(false)
    , m_isTracking(false)
    , m_xError(0.0)
    , m_yError(0.0)
{
    // Connect the thread finished signal
    connect(&m_pollingThread, &QThread::finished, this, [this]() {
        m_running = false;
    });
}

TrackerInterface::~TrackerInterface()
{
    stop();
    cleanupMemoryMapping();
}

bool TrackerInterface::configurePCIDevice()
{
    qDebug() << QString("Attempting to configure PCI device at %1:%2.%3")
        .arg(m_pciBus, 2, 16, QChar('0'))
        .arg(m_pciSlot, 2, 16, QChar('0'))
        .arg(m_pciFunc);

    // Format the command string
    QString pciDeviceAddress = QString("%1:%2.%3")
        .arg(m_pciBus, 2, 16, QChar('0'))
        .arg(m_pciSlot, 2, 16, QChar('0'))
        .arg(m_pciFunc);

    QString cmd = QString("setpci -s %1 04.w=0142").arg(pciDeviceAddress);

    qDebug() << "Executing command:" << cmd;

    // Execute the command
    int result = system(cmd.toStdString().c_str());

    if (result != 0) {
        emit errorOccurred(QString("Failed to execute setpci command: %1").arg(cmd));
        return false;
    }

    qDebug() << "Successfully executed:" << cmd;
    return true;
}

bool TrackerInterface::initialize(uintptr_t baseAddress, size_t memSize,
                                 uint8_t pciBus, uint8_t pciSlot, uint8_t pciFunc)
{
    QMutexLocker locker(&m_mutex);

    // If already initialized, clean up first
    if (m_initialized) {
        cleanupMemoryMapping();
    }

    // Store PCI device location and memory parameters
    m_pciBus = pciBus;
    m_pciSlot = pciSlot;
    m_pciFunc = pciFunc;
    m_baseAddress = baseAddress;
    m_memSize = memSize;

    // First configure the PCI device
    if (!configurePCIDevice()) {
        emit errorOccurred("Failed to configure PCI device");
        return false;
    }

    // Set up memory mapping to access the tracker card
    if (!setupMemoryMapping()) {
        emit errorOccurred("Failed to initialize tracker interface");
        return false;
    }

    // Initialize mailboxes
    writeWord(COMMAND_MAILBOX_OFFSET, 0);
    usleep(100);
    writeWord(STATUS_MAILBOX_OFFSET, 0);
    usleep(100);

    m_initialized = true;
    emit statusChanged("Tracker interface initialized");

    // Send a ping to verify communication
    if (!ping()) {
        emit errorOccurred("Tracker initialization completed but ping failed");
        // Continue anyway as initialization was successful
    }

    return true;
}

bool TrackerInterface::start()
{
    QMutexLocker locker(&m_mutex);

    if (!m_initialized) {
        emit errorOccurred("Cannot start tracker interface: not initialized");
        return false;
    }

    if (m_running) {
        return true; // Already running
    }

    // Start the polling thread
    m_running = true;

    // Move this object to the polling thread
    moveToThread(&m_pollingThread);

    // Connect thread started signal to the polling function
    connect(&m_pollingThread, &QThread::started, this, &TrackerInterface::trackerPollingThread);

    // Start the thread
    m_pollingThread.start(QThread::HighPriority);  // Use high priority for real-time operation

    emit statusChanged("Tracker interface started");
    return true;
}

bool TrackerInterface::stop()
{
    QMutexLocker locker(&m_mutex);

    if (!m_running) {
        return true; // Already stopped
    }

    // Signal the thread to stop
    m_running = false;

    // Wait for thread to finish
    if (m_pollingThread.isRunning()) {
        m_pollingThread.quit();
        m_pollingThread.wait();
    }

    emit statusChanged("Tracker interface stopped");
    return true;
}

void TrackerInterface::getTrackingErrors(double &xError, double &yError)
{
    QMutexLocker locker(&m_mutex);
    xError = m_xError;
    yError = m_yError;
}

bool TrackerInterface::getTrackingError(double &xError, double &yError, QString &state)
{
    QMutexLocker locker(&m_mutex);
    xError = m_xError;
    yError = m_yError;
    
    // Set the state string based on current tracking status
    if (m_isTracking) {
        state = "Tracking";
    } else {
        state = "Not Tracking";
    }
    
    return m_initialized; // Return true if tracker is initialized
}

bool TrackerInterface::isTargetTracked() const
{
    QMutexLocker locker(&m_mutex);
    return m_isTracking;
}

bool TrackerInterface::ping()
{
    QMutexLocker locker(&m_mutex);

    if (!m_initialized) {
        emit errorOccurred("Tracker memory not initialized");
        return false;
    }

    // Wait until the tracker is ready to receive a command
    if (!isReadyForCommand()) {
        emit errorOccurred("Tracker not ready for command");
        return false;
    }

    qDebug() << "Sending ping message to tracker...";

    // Construct ping message (message type 0)
    uint16_t pingMessage[3];
    pingMessage[0] = 0xA5A5; // Sync word
    pingMessage[1] = 0x0000; // Message Type 0 (Ping)

    // Calculate checksum - two's complement of the sum
    pingMessage[2] = calculateChecksum(pingMessage, 2);

    // Write the ping message to the command buffer
    for (int i = 0; i < 3; ++i) {
        writeWord(COMMAND_MESSAGE_OFFSET + i*2, pingMessage[i]);
    }

    // Write a non-zero value to the command mailbox to interrupt the tracker
    writeWord(COMMAND_MAILBOX_OFFSET, 1);

    // Wait for tracker to process (mailbox returns to 0)
    int timeout = 100; // 10 second timeout (100 * 100ms)
    while (readWord(COMMAND_MAILBOX_OFFSET) != 0 && timeout > 0) {
        usleep(100000); // 100ms delay
        timeout--;
    }

    if (timeout <= 0) {
        emit errorOccurred("Timeout waiting for tracker to process ping");
        return false;
    }

    qDebug() << "Ping message processed by tracker";
    return true;
}

void TrackerInterface::trackerPollingThread()
{
    // Create a high-precision timer for consistent timing
    QTimer timer;
    timer.setTimerType(Qt::PreciseTimer);
    timer.setInterval(TRACKER_POLLING_RATE_MS);  // 4ms = 250Hz

    // Use a lambda to poll the tracker at the desired rate
    QObject::connect(&timer, &QTimer::timeout, [this]() {
        if (!m_running) {
            return;
        }

        // Read tracker data
        TrackData data;
        if (readStatusData(data)) {
            QMutexLocker locker(&m_mutex);

            // Update tracking status if changed
            bool newTrackingState = data.isTracking();
            if (m_isTracking != newTrackingState) {
                m_isTracking = newTrackingState;
                emit trackingStatusChanged(m_isTracking);
            }

            // Update tracking errors and scale to -1.0 to 1.0 range
            // Raw error values from the tracker card are already scaled by 32
            m_xError = data.rawErrorX / 10.0; // Scale to appropriate range for our system
            m_yError = data.rawErrorY / 10.0;

            // Emit signal with new tracking errors
            emit trackingErrorsUpdated(m_xError, m_yError);
        }
    });

    // Start the timer
    timer.start();

    // Event loop to keep the thread running
    QEventLoop loop;
    QObject::connect(this, &TrackerInterface::destroyed, &loop, &QEventLoop::quit);
    QObject::connect(&m_pollingThread, &QThread::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Stop the timer when the event loop exits
    timer.stop();
}

bool TrackerInterface::setupMemoryMapping()
{
    // Open /dev/mem for physical memory access
    m_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (m_fd == -1) {
        emit errorOccurred("Failed to open /dev/mem");
        return false;
    }

    // Map the physical memory
    m_mappedMem = mmap(nullptr, m_memSize, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd, m_baseAddress);
    if (m_mappedMem == MAP_FAILED) {
        emit errorOccurred("Failed to map physical memory for tracker card");
        close(m_fd);
        m_fd = -1;
        return false;
    }

    qDebug() << "Memory mapped successfully at" << QString::number(m_baseAddress, 16);
    return true;
}

void TrackerInterface::cleanupMemoryMapping()
{
    if (m_mappedMem != nullptr && m_mappedMem != MAP_FAILED) {
        munmap(m_mappedMem, m_memSize);
        m_mappedMem = nullptr;
    }

    if (m_fd != -1) {
        close(m_fd);
        m_fd = -1;
    }

    m_initialized = false;
}

uint16_t TrackerInterface::readWord(size_t offset)
{
    if (!m_initialized || offset >= m_memSize) {
        return 0;
    }

    volatile uint16_t* ptr = static_cast<volatile uint16_t*>(
        static_cast<volatile void*>(static_cast<volatile char*>(m_mappedMem) + offset));
    return *ptr;
}

void TrackerInterface::writeWord(size_t offset, uint16_t value)
{
    if (!m_initialized || offset >= m_memSize) {
        return;
    }

    volatile uint16_t* ptr = static_cast<volatile uint16_t*>(
        static_cast<volatile void*>(static_cast<volatile char*>(m_mappedMem) + offset));
    *ptr = value;
}

bool TrackerInterface::readStatusData(TrackData &data)
{
    if (!m_initialized) {
        return false;
    }

    // Check if there's a new status message available
    if (readWord(STATUS_MAILBOX_OFFSET) == 0) {
        return false; // No new status available
    }

    // Read the status message header (sync word and message type)
    uint16_t syncWord = readWord(STATUS_MESSAGE_OFFSET);
    uint16_t msgType = readWord(STATUS_MESSAGE_OFFSET + 2);

    // Verify sync word and message type
    if (syncWord != 0xA5A5 || (msgType & 0xFF00) != 0xFF00) {
        // Invalid status message, clear mailbox and return
        writeWord(STATUS_MAILBOX_OFFSET, 0);
        return false;
    }

    // Read raw track errors
    data.rawErrorX = static_cast<float>(static_cast<int16_t>(readWord(STATUS_MESSAGE_OFFSET + 4))) / 32.0f;
    data.rawErrorY = static_cast<float>(static_cast<int16_t>(readWord(STATUS_MESSAGE_OFFSET + 6))) / 32.0f;

    // Read status information
    uint16_t statusWord = readWord(STATUS_MESSAGE_OFFSET + 10);
    data.trackState = (statusWord >> 3) & 0x0007; // Extract track state bits
    data.status = readWord(STATUS_MESSAGE_OFFSET + 12);

    // Clear the status mailbox to indicate we've read the message
    writeWord(STATUS_MAILBOX_OFFSET, 0);

    return true;
}

bool TrackerInterface::isReadyForCommand()
{
    // Check if the command mailbox contains a zero value
    return readWord(COMMAND_MAILBOX_OFFSET) == 0;
}

uint16_t TrackerInterface::calculateChecksum(const uint16_t* data, size_t words)
{
    uint16_t sum = 0;

    // Add each byte separately (endian-aware)
    for (size_t i = 0; i < words; ++i) {
        sum += (data[i] >> 8) & 0xFF;  // High byte
        sum += data[i] & 0xFF;         // Low byte
    }

    // Two's complement
    return (~sum) + 1;
}