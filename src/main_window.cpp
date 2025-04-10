#include "main_window.h"
#include "ui_main_window.h"
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QProgressBar>
#include <QRadioButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QDir>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_joystickInterface(new JoystickInterface(this))
    , m_fsmController(new FSMController(this))
    , m_gimbalController(new GimbalController(this))
    , m_trackerInterface(new TrackerInterface(this))
    , m_controlLoop(new ControlLoop(this))
    , m_systemRunning(false)
    , m_currentMode(MainWindow::ControlMode::CoarseTrack)
    , m_selectedJoystickIndex(-1)
    , m_fsmOutputEnabled(false)
    , m_fsmXAxisIndex(0)
    , m_fsmYAxisIndex(1)
    , m_invertFsmXAxis(false)
    , m_invertFsmYAxis(false)
    , m_fsmDeadzone(0.05)
    , m_gimbalOutputEnabled(false)
    , m_azimuthAxisIndex(0)
    , m_elevationAxisIndex(1)
    , m_auxElevationAxisIndex(2)
    , m_invertAzimuthAxis(false)
    , m_invertElevationAxis(false)
    , m_invertAuxElevationAxis(false)
    , m_gimbalDeadzone(0.05)
    , m_trackerInitialized(false)
    , m_trackerAutoPoll(false)
    , m_trackerPollTimer(new QTimer(this))
    , m_logFile(nullptr)
    , m_logStream(nullptr)
    , m_loggingActive(false)
    , m_statusUpdateTimer(new QTimer(this))
{
    ui->setupUi(this);

    // Initialize the control system components
    if (!m_controlLoop->initialize()) {
        QMessageBox::critical(this, "Initialization Error", "Failed to initialize the control system.");
    }

    // Set up the UI
    setupSignalsAndSlots();
    createJoystickInputsUI();
    updateJoystickList();
    updateUIForCurrentMode();

    // Set up status update timer (5 Hz)
    m_statusUpdateTimer->setInterval(200);
    connect(m_statusUpdateTimer, &QTimer::timeout, this, &MainWindow::updateSystemStatus);
    m_statusUpdateTimer->start();

    // Set initial status message
    setStatusMessage("System initialized and ready");
}

MainWindow::~MainWindow()
{
    // Stop the control loop
    if (m_controlLoop && m_systemRunning) {
        m_controlLoop->stop();
    }

    // Stop the UI update timer
    if (m_statusUpdateTimer && m_statusUpdateTimer->isActive()) {
        m_statusUpdateTimer->stop();
    }

    // Stop logging if active
    if (m_loggingActive) {
        onStartStopLogging();
    }

    // Clean up resources
    delete m_logStream;
    delete m_logFile;

    delete ui;
}

void MainWindow::onStartSystem()
{
    if (m_systemRunning) {
        return; // Already running
    }

    // Start the control loop
    if (m_controlLoop->start()) {
        m_systemRunning = true;
        
        // Find the buttons by object name
        QPushButton* startButton = findChild<QPushButton*>("startButton");
        QPushButton* stopButton = findChild<QPushButton*>("stopButton");
        
        if (startButton) startButton->setEnabled(false);
        if (stopButton) stopButton->setEnabled(true);
        
        setStatusMessage("System started");
    } else {
        QMessageBox::critical(this, "Start Error", "Failed to start the control system.");
    }
}

void MainWindow::onStopSystem()
{
    if (!m_systemRunning) {
        return; // Already stopped
    }

    // Stop the control loop
    if (m_controlLoop->stop()) {
        m_systemRunning = false;
        
        // Find the buttons by object name
        QPushButton* startButton = findChild<QPushButton*>("startButton");
        QPushButton* stopButton = findChild<QPushButton*>("stopButton");
        
        if (startButton) startButton->setEnabled(true);
        if (stopButton) stopButton->setEnabled(false);
        
        setStatusMessage("System stopped");
    } else {
        QMessageBox::critical(this, "Stop Error", "Failed to stop the control system.");
    }
}

void MainWindow::onModeChanged()
{
    // Get selected mode from radio buttons
    ControlLoop::OperationMode newMode;
    
    if (ui->coarseTrackingRadio->isChecked()) {
        newMode = ControlLoop::OperationMode::COARSE_TRACK;
        m_currentMode = ControlMode::CoarseTrack;
    } else if (ui->fineTrackingRadio->isChecked()) {
        newMode = ControlLoop::OperationMode::FINE_TRACK;
        m_currentMode = ControlMode::FineTrack;
    } else if (ui->autoTrackingRadio->isChecked()) {
        newMode = ControlLoop::OperationMode::AUTO_TRACK;
        m_currentMode = ControlMode::AutoTrack;
    }

    // Update control mode in the control loop
    m_controlLoop->setOperationMode(newMode);
    
    // Update UI for the current mode
    updateUIForCurrentMode();
    
    setStatusMessage(QString("Mode changed to %1")
                    .arg(m_currentMode == ControlMode::CoarseTrack ? "Coarse Track" :
                         m_currentMode == ControlMode::FineTrack ? "Fine Track" : "Auto Track"));
}

void MainWindow::onClearLogsButtonClicked()
{
    QTextEdit* logTextEdit = findChild<QTextEdit*>("logTextEdit");
    if (logTextEdit) {
        logTextEdit->clear();
        logMessage("Log cleared");
    }
}

void MainWindow::onStatusChanged(const QString &message)
{
    logMessage(message);
}

void MainWindow::onErrorOccurred(const QString &error)
{
    logError(error);
}

void MainWindow::onOperationModeChanged(ControlLoop::OperationMode mode)
{
    // Convert ControlLoop::OperationMode to MainWindow::ControlMode
    if (mode == ControlLoop::OperationMode::COARSE_TRACK) {
        m_currentMode = ControlMode::CoarseTrack;
    } else if (mode == ControlLoop::OperationMode::FINE_TRACK) {
        m_currentMode = ControlMode::FineTrack;
    } else if (mode == ControlLoop::OperationMode::AUTO_TRACK) {
        m_currentMode = ControlMode::AutoTrack;
    }
    
    updateModeDisplay(mode);
}

void MainWindow::onTelemetryUpdated(double fsmX, double fsmY,
                                   double gimbalAz, double gimbalEl, double gimbalAuxEl,
                                   double joystickX, double joystickY, double joystickZ,
                                   double trackErrorX, double trackErrorY)
{
    // Update telemetry data
    m_telemetry.fsmX = fsmX;
    m_telemetry.fsmY = fsmY;
    m_telemetry.gimbalAz = gimbalAz;
    m_telemetry.gimbalEl = gimbalEl;
    m_telemetry.gimbalAuxEl = gimbalAuxEl;
    m_telemetry.joystickX = joystickX;
    m_telemetry.joystickY = joystickY;
    m_telemetry.joystickZ = joystickZ;
    m_telemetry.trackErrorX = trackErrorX;
    m_telemetry.trackErrorY = trackErrorY;

    // Update the graphs (this would be implemented depending on the graphing library used)
    // For now, we just update the text display in updateStatusDisplay()
}

void MainWindow::updateStatusDisplay()
{
    // Update system running status
    QLabel* valueRunning = findChild<QLabel*>("valueRunning");
    if (valueRunning) {
        valueRunning->setText(m_systemRunning ? "Yes" : "No");
    }

    // Update FSM display
    QLabel* valueFSM = findChild<QLabel*>("valueFSM");
    if (valueFSM) {
        valueFSM->setText(QString("X: %1, Y: %2")
                         .arg(m_telemetry.fsmX, 0, 'f', 3)
                         .arg(m_telemetry.fsmY, 0, 'f', 3));
    }

    // Update gimbal display
    QLabel* valueGimbal = findChild<QLabel*>("valueGimbal");
    if (valueGimbal) {
        valueGimbal->setText(QString("Az: %1, El: %2, Aux: %3")
                            .arg(m_telemetry.gimbalAz, 0, 'f', 3)
                            .arg(m_telemetry.gimbalEl, 0, 'f', 3)
                            .arg(m_telemetry.gimbalAuxEl, 0, 'f', 3));
    }

    // Update joystick display
    QLabel* valueJoystick = findChild<QLabel*>("valueJoystick");
    if (valueJoystick) {
        valueJoystick->setText(QString("X: %1, Y: %2, Z: %3")
                              .arg(m_telemetry.joystickX, 0, 'f', 3)
                              .arg(m_telemetry.joystickY, 0, 'f', 3)
                              .arg(m_telemetry.joystickZ, 0, 'f', 3));
    }

    // Update tracking error display
    QLabel* valueTrackError = findChild<QLabel*>("valueTrackError");
    if (valueTrackError) {
        valueTrackError->setText(QString("X: %1, Y: %2")
                                .arg(m_telemetry.trackErrorX, 0, 'f', 3)
                                .arg(m_telemetry.trackErrorY, 0, 'f', 3));
    }
}

void MainWindow::setupUi()
{
    // Create control panel widgets programmatically since they're not in the UI file
    QWidget* controlPanel = new QWidget(this);
    QVBoxLayout* controlLayout = new QVBoxLayout(controlPanel);
    
    // System control buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* startButton = new QPushButton("Start System", controlPanel);
    QPushButton* stopButton = new QPushButton("Stop System", controlPanel);
    QPushButton* modeButton = new QPushButton("Change Mode", controlPanel);
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(modeButton);
    controlLayout->addLayout(buttonLayout);
    
    // Status display
    QGroupBox* statusGroup = new QGroupBox("System Status", controlPanel);
    QGridLayout* statusLayout = new QGridLayout(statusGroup);
    
    QLabel* runningLabel = new QLabel("Running:", statusGroup);
    QLabel* modeLabel = new QLabel("Mode:", statusGroup);
    QLabel* trackingLabel = new QLabel("Tracking:", statusGroup);
    QLabel* fsmLabel = new QLabel("FSM:", statusGroup);
    QLabel* gimbalLabel = new QLabel("Gimbal:", statusGroup);
    QLabel* joystickLabel = new QLabel("Joystick:", statusGroup);
    QLabel* trackErrorLabel = new QLabel("Track Error:", statusGroup);
    
    QLabel* valueRunning = new QLabel("No", statusGroup);
    QLabel* valueMode = new QLabel("Coarse Track", statusGroup);
    QLabel* valueTracking = new QLabel("Manual", statusGroup);
    QLabel* valueFSM = new QLabel("X: 0.000, Y: 0.000", statusGroup);
    QLabel* valueGimbal = new QLabel("Az: 0.000, El: 0.000, Aux: 0.000", statusGroup);
    QLabel* valueJoystick = new QLabel("X: 0.000, Y: 0.000, Z: 0.000", statusGroup);
    QLabel* valueTrackError = new QLabel("X: 0.000, Y: 0.000", statusGroup);
    
    statusLayout->addWidget(runningLabel, 0, 0);
    statusLayout->addWidget(valueRunning, 0, 1);
    statusLayout->addWidget(modeLabel, 1, 0);
    statusLayout->addWidget(valueMode, 1, 1);
    statusLayout->addWidget(trackingLabel, 2, 0);
    statusLayout->addWidget(valueTracking, 2, 1);
    statusLayout->addWidget(fsmLabel, 3, 0);
    statusLayout->addWidget(valueFSM, 3, 1);
    statusLayout->addWidget(gimbalLabel, 4, 0);
    statusLayout->addWidget(valueGimbal, 4, 1);
    statusLayout->addWidget(joystickLabel, 5, 0);
    statusLayout->addWidget(valueJoystick, 5, 1);
    statusLayout->addWidget(trackErrorLabel, 6, 0);
    statusLayout->addWidget(valueTrackError, 6, 1);
    
    controlLayout->addWidget(statusGroup);
    
    // Logs
    QGroupBox* logsGroup = new QGroupBox("System Logs", controlPanel);
    QVBoxLayout* logsLayout = new QVBoxLayout(logsGroup);
    QTextEdit* logTextEdit = new QTextEdit(logsGroup);
    logTextEdit->setReadOnly(true);
    QPushButton* clearLogsButton = new QPushButton("Clear Logs", logsGroup);
    logsLayout->addWidget(logTextEdit);
    logsLayout->addWidget(clearLogsButton);
    
    controlLayout->addWidget(logsGroup);
    
    // Add the control panel to the main window
    ui->centralwidget->layout()->addWidget(controlPanel);
    
    // Store references to created widgets in member variables
    startButton->setObjectName("startButton");
    stopButton->setObjectName("stopButton");
    modeButton->setObjectName("modeButton");
    valueRunning->setObjectName("valueRunning");
    valueMode->setObjectName("valueMode");
    valueTracking->setObjectName("valueTracking");
    valueFSM->setObjectName("valueFSM");
    valueGimbal->setObjectName("valueGimbal");
    valueJoystick->setObjectName("valueJoystick");
    valueTrackError->setObjectName("valueTrackError");
    logTextEdit->setObjectName("logTextEdit");
    clearLogsButton->setObjectName("clearLogsButton");
    
    // Set initial state
    stopButton->setEnabled(false);

    // Set initial mode display
    ControlLoop::OperationMode loopMode;
    if (m_currentMode == ControlMode::CoarseTrack) {
        loopMode = ControlLoop::OperationMode::COARSE_TRACK;
    } else if (m_currentMode == ControlMode::FineTrack) {
        loopMode = ControlLoop::OperationMode::FINE_TRACK;
    } else { // AutoTrack
        loopMode = ControlLoop::OperationMode::AUTO_TRACK;
    }
    updateModeDisplay(loopMode);
    
    // Connect signals
    connect(startButton, &QPushButton::clicked, this, &MainWindow::onStartSystem);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::onStopSystem);
    connect(modeButton, &QPushButton::clicked, this, &MainWindow::onModeChanged);
    connect(clearLogsButton, &QPushButton::clicked, this, &MainWindow::onClearLogsButtonClicked);
}

void MainWindow::setupSignals()
{
    // Connect control loop signals
    connect(m_controlLoop, &ControlLoop::statusChanged, this, &MainWindow::onStatusChanged);
    connect(m_controlLoop, &ControlLoop::errorOccurred, this, &MainWindow::onErrorOccurred);
    connect(m_controlLoop, &ControlLoop::operationModeChanged, this, &MainWindow::onOperationModeChanged);
    connect(m_controlLoop, &ControlLoop::telemetryUpdated, this, &MainWindow::onTelemetryUpdated);
}

void MainWindow::setupGraphs()
{
    // Set up graphs for visualization
    // This would be implemented with the specific graphing library used (e.g., QCustomPlot)
    // For now, we'll leave this as a placeholder
}

void MainWindow::setupStatusBar()
{
    // Set up status bar with a fixed-width font
    m_statusFont = QFont("Courier New", 10);
    m_statusFont.setFixedPitch(true);
    statusBar()->setFont(m_statusFont);

    // Set initial status
    statusBar()->showMessage("BC-TRAIL Ready");
}

void MainWindow::updateModeDisplay(ControlLoop::OperationMode mode)
{
    QString modeText;
    
    QLabel* valueTracking = findChild<QLabel*>("valueTracking");
    QLabel* valueMode = findChild<QLabel*>("valueMode");

    switch (mode) {
        case ControlLoop::OperationMode::COARSE_TRACK:
            modeText = "Coarse Track";
            if (valueTracking) valueTracking->setText("Manual");
            break;

        case ControlLoop::OperationMode::FINE_TRACK:
            modeText = "Fine Track";
            if (valueTracking) valueTracking->setText("Manual");
            break;

        case ControlLoop::OperationMode::AUTO_TRACK:
            modeText = "Auto Track";
            if (valueTracking) valueTracking->setText("Automatic");
            break;
    }

    if (valueMode) valueMode->setText(modeText);
}

void MainWindow::logMessage(const QString &message)
{
    // Add timestamp to message
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString formattedMessage = QString("[%1] %2").arg(timestamp).arg(message);

    // Add to log
    QTextEdit* logTextEdit = findChild<QTextEdit*>("logTextEdit");
    if (logTextEdit) {
        logTextEdit->append(formattedMessage);
    }

    // Update status bar
    statusBar()->showMessage(message, 5000);
}

void MainWindow::logError(const QString &error)
{
    // Add timestamp to error
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString formattedError = QString("[%1] ERROR: %2").arg(timestamp).arg(error);

    // Add to log in red
    QTextEdit* logTextEdit = findChild<QTextEdit*>("logTextEdit");
    if (logTextEdit) {
        logTextEdit->append(QString("<span style=\"color:red;\">%1</span>").arg(formattedError));
    }

    // Update status bar
    statusBar()->showMessage(error, 10000);

    // Log to debug output as well
    qDebug() << "ERROR:" << error;
}

void MainWindow::setupSignalsAndSlots()
{
    // Joystick signals
    connect(ui->refreshJoystickButton, &QPushButton::clicked, this, &MainWindow::onRefreshJoysticks);
    connect(ui->joystickComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onJoystickSelected);
    connect(ui->calibrateButton, &QPushButton::clicked, this, &MainWindow::onCalibrateJoystick);

    connect(m_joystickInterface, &JoystickInterface::buttonStateChanged,
            this, &MainWindow::onButtonStateChanged);
    connect(m_joystickInterface, &JoystickInterface::joystickPositionChanged,
            [this](double x, double y, double z) {
                // Update joystick position data
                // This will be used in the control loop
            });
    connect(m_joystickInterface, &JoystickInterface::hatStateChanged,
            this, &MainWindow::onHatStateChanged);
    connect(m_joystickInterface, &JoystickInterface::errorOccurred,
            [this](const QString &error) {
                setStatusMessage("Joystick error: " + error);
            });

    // FSM controls
    connect(ui->fsmXAxisComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onFsmAxisMappingChanged);
    connect(ui->fsmYAxisComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onFsmAxisMappingChanged);
    connect(ui->fsmInvertXCheckbox, &QCheckBox::toggled, this, &MainWindow::onFsmInvertAxisToggled);
    connect(ui->fsmInvertYCheckbox, &QCheckBox::toggled, this, &MainWindow::onFsmInvertAxisToggled);
    connect(ui->fsmDeadzoneSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onFsmDeadzoneChanged);
    connect(ui->enableFsmOutputCheckbox, &QCheckBox::toggled, this, &MainWindow::onEnableFsmOutput);

    // Gimbal controls
    connect(ui->azimuthAxisComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onGimbalAxisMappingChanged);
    connect(ui->elevationAxisComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onGimbalAxisMappingChanged);
    connect(ui->auxElevationAxisComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onGimbalAxisMappingChanged);
    connect(ui->invertAzimuthCheckbox, &QCheckBox::toggled, this, &MainWindow::onGimbalInvertAxisToggled);
    connect(ui->invertElevationCheckbox, &QCheckBox::toggled, this, &MainWindow::onGimbalInvertAxisToggled);
    connect(ui->invertAuxElevationCheckbox, &QCheckBox::toggled, this, &MainWindow::onGimbalInvertAxisToggled);
    connect(ui->gimbalDeadzoneSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onGimbalDeadzoneChanged);
    connect(ui->enableGimbalOutputCheckbox, &QCheckBox::toggled, this, &MainWindow::onEnableGimbalOutput);

    // Tracker controls
    connect(ui->trackerInitButton, &QPushButton::clicked, this, &MainWindow::onTrackerInitialize);
    connect(ui->trackerPingButton, &QPushButton::clicked, this, &MainWindow::onTrackerPing);
    connect(ui->trackerAutoPollCheckbox, &QCheckBox::toggled, this, &MainWindow::onTrackerAutoPollToggled);

    // Tracking mode controls
    connect(ui->coarseTrackingRadio, &QRadioButton::toggled,
            [this](bool checked) { if (checked) onModeChanged(); });
    connect(ui->fineTrackingRadio, &QRadioButton::toggled,
            [this](bool checked) { if (checked) onModeChanged(); });
    connect(ui->autoTrackingRadio, &QRadioButton::toggled,
            [this](bool checked) { if (checked) onModeChanged(); });

    // Logging controls
    connect(ui->browseLogButton, &QPushButton::clicked, this, &MainWindow::onBrowseLogFile);
    connect(ui->startStopLoggingButton, &QPushButton::clicked, this, &MainWindow::onStartStopLogging);

    // System control
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::onResetSystem);
}

void MainWindow::createJoystickInputsUI()
{
    // Clear any existing UI elements
    clearJoystickInputsUI();

    // Get layout for joystick inputs
    QVBoxLayout *layout = ui->joystickInputsLayout;

    // No joystick selected yet
    if (!m_joystickInterface->isJoystickOpen()) {
        QLabel *noJoystickLabel = new QLabel("No joystick selected");
        layout->addWidget(noJoystickLabel);
        return;
    }

    // Create buttons section
    QGroupBox *buttonsGroup = new QGroupBox("Buttons");
    QGridLayout *buttonsLayout = new QGridLayout(buttonsGroup);
    int numButtons = m_joystickInterface->getNumButtons();
    int buttonsPerRow = 4;

    for (int i = 0; i < numButtons; ++i) {
        QLabel *label = new QLabel(QString("Button %1:").arg(i));
        QLabel *stateLabel = new QLabel("Released");
        stateLabel->setMinimumWidth(80);

        buttonsLayout->addWidget(label, i / buttonsPerRow, (i % buttonsPerRow) * 2);
        buttonsLayout->addWidget(stateLabel, i / buttonsPerRow, (i % buttonsPerRow) * 2 + 1);

        m_buttonLabels.append(stateLabel);
    }

    layout->addWidget(buttonsGroup);

    // Create axes section
    QGroupBox *axesGroup = new QGroupBox("Axes");
    QGridLayout *axesLayout = new QGridLayout(axesGroup);
    int numAxes = m_joystickInterface->getNumAxes();

    for (int i = 0; i < numAxes; ++i) {
        QLabel *label = new QLabel(QString("Axis %1:").arg(i));
        QProgressBar *bar = new QProgressBar();
        bar->setMinimum(-100);
        bar->setMaximum(100);
        bar->setValue(0);
        bar->setFormat("%v");
        bar->setTextVisible(true);

        axesLayout->addWidget(label, i, 0);
        axesLayout->addWidget(bar, i, 1);

        m_axisProgressBars.append(bar);
    }

    layout->addWidget(axesGroup);

    // Create hats section
    int numHats = m_joystickInterface->getNumHats();
    if (numHats > 0) {
        QGroupBox *hatsGroup = new QGroupBox("Hats");
        QGridLayout *hatsLayout = new QGridLayout(hatsGroup);

        for (int i = 0; i < numHats; ++i) {
            QLabel *label = new QLabel(QString("Hat %1:").arg(i));
            QLabel *valueLabel = new QLabel("Centered");

            hatsLayout->addWidget(label, i, 0);
            hatsLayout->addWidget(valueLabel, i, 1);

            m_hatLabels.append(valueLabel);
        }

        layout->addWidget(hatsGroup);
    }

    // Add a stretch at the end
    layout->addStretch();
}

void MainWindow::clearJoystickInputsUI()
{
    // Clear all dynamically created UI elements
    m_buttonLabels.clear();
    m_axisProgressBars.clear();
    m_hatLabels.clear();

    // Delete all items in the layout
    QLayoutItem *item;
    while ((item = ui->joystickInputsLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void MainWindow::updateJoystickList()
{
    ui->joystickComboBox->clear();
    QStringList joysticks = m_joystickInterface->getAvailableJoysticks();

    for (const QString &joystick : joysticks) {
        ui->joystickComboBox->addItem(joystick);
    }

    // Update joystick info display
    updateJoystickInfo();
}

void MainWindow::updateJoystickInfo()
{
    if (m_joystickInterface->isJoystickOpen()) {
        int numAxes = m_joystickInterface->getNumAxes();
        int numButtons = m_joystickInterface->getNumButtons();
        int numHats = m_joystickInterface->getNumHats();

        QString info = QString("%1 connected: %2 axes, %3 buttons, %4 hats")
                            .arg(m_joystickInterface->getJoystickName())
                            .arg(numAxes)
                            .arg(numButtons)
                            .arg(numHats);

        ui->joystickInfoLabel->setText(info);

        // Update FSM and gimbal axis combo boxes
        ui->fsmXAxisComboBox->clear();
        ui->fsmYAxisComboBox->clear();
        ui->azimuthAxisComboBox->clear();
        ui->elevationAxisComboBox->clear();
        ui->auxElevationAxisComboBox->clear();

        for (int i = 0; i < numAxes; ++i) {
            QString axisName = QString("Axis %1").arg(i);
            ui->fsmXAxisComboBox->addItem(axisName, i);
            ui->fsmYAxisComboBox->addItem(axisName, i);
            ui->azimuthAxisComboBox->addItem(axisName, i);
            ui->elevationAxisComboBox->addItem(axisName, i);
            ui->auxElevationAxisComboBox->addItem(axisName, i);
        }

        // Set default mappings
        ui->fsmXAxisComboBox->setCurrentIndex(m_fsmXAxisIndex);
        ui->fsmYAxisComboBox->setCurrentIndex(m_fsmYAxisIndex);
        ui->azimuthAxisComboBox->setCurrentIndex(m_azimuthAxisIndex);
        ui->elevationAxisComboBox->setCurrentIndex(m_elevationAxisIndex);
        ui->auxElevationAxisComboBox->setCurrentIndex(m_auxElevationAxisIndex);
    } else {
        ui->joystickInfoLabel->setText("No joystick selected");
    }
}

void MainWindow::onRefreshJoysticks()
{
    m_joystickInterface->refreshJoysticks();
    updateJoystickList();
    setStatusMessage("Joystick list refreshed");
}

void MainWindow::onJoystickSelected(int index)
{
    if (index >= 0) {
        int result = m_joystickInterface->openJoystick(index);
        if (result >= 0) {
            m_selectedJoystickIndex = index;
            createJoystickInputsUI();
            updateJoystickInfo();
            setStatusMessage(QString("Selected joystick: %1").arg(m_joystickInterface->getJoystickName()));
        } else {
            setStatusMessage("Failed to open joystick");
        }
    }
}

void MainWindow::onCalibrateJoystick()
{
    if (m_joystickInterface->isJoystickOpen()) {
        m_joystickInterface->calibrateAxes();
        setStatusMessage("Joystick calibrated");
    } else {
        setStatusMessage("No joystick selected to calibrate");
    }
}

void MainWindow::onButtonStateChanged(int button, bool pressed)
{
    if (button >= m_buttonLabels.size()) {
        return;
    }

    // Update button state label
    m_buttonLabels[button]->setText(pressed ? "Pressed" : "Released");

    // Process button presses
    if (pressed) {
        // Check if it's the mode button
        if (button == static_cast<int>(JoystickInterface::Button::MODE_SWITCH)) {
            // Cycle through modes
            if (m_currentMode == ControlMode::CoarseTrack) {
                ui->fineTrackingRadio->setChecked(true);
            } else if (m_currentMode == ControlMode::FineTrack) {
                ui->autoTrackingRadio->setChecked(true);
            } else {
                ui->coarseTrackingRadio->setChecked(true);
            }
            onModeChanged();
        }
    }
}

void MainWindow::onAxisChanged(int axis, int value)
{
    // Update axis progress bars
    if (axis < m_axisProgressBars.size()) {
        // Scale from -32768...32767 to -100...100 for display
        int scaled = value * 100 / 32767;
        m_axisProgressBars[axis]->setValue(scaled);
    }
}

void MainWindow::onHatStateChanged(int hat, int value)
{
    // Update hat labels
    if (hat < m_hatLabels.size()) {
        m_hatLabels[hat]->setText(hatValueToString(value));
    }
}

QString MainWindow::hatValueToString(int value)
{
    switch (value) {
        case SDL_HAT_CENTERED: return "Centered";
        case SDL_HAT_UP: return "Up";
        case SDL_HAT_RIGHT: return "Right";
        case SDL_HAT_DOWN: return "Down";
        case SDL_HAT_LEFT: return "Left";
        case SDL_HAT_RIGHTUP: return "Right+Up";
        case SDL_HAT_RIGHTDOWN: return "Right+Down";
        case SDL_HAT_LEFTUP: return "Left+Up";
        case SDL_HAT_LEFTDOWN: return "Left+Down";
        default: return "Unknown";
    }
}

void MainWindow::updateUIForCurrentMode()
{
    // Update radio buttons to match current mode
    switch (m_currentMode) {
        case ControlMode::CoarseTrack:
            ui->coarseTrackingRadio->setChecked(true);
            ui->fineTrackingRadio->setChecked(false);
            ui->autoTrackingRadio->setChecked(false);
            break;

        case ControlMode::FineTrack:
            ui->coarseTrackingRadio->setChecked(false);
            ui->fineTrackingRadio->setChecked(true);
            ui->autoTrackingRadio->setChecked(false);
            break;

        case ControlMode::AutoTrack:
            ui->coarseTrackingRadio->setChecked(false);
            ui->fineTrackingRadio->setChecked(false);
            ui->autoTrackingRadio->setChecked(true);
            break;
    }

    // Enable/disable controls based on mode
    bool manualMode = (m_currentMode != ControlMode::AutoTrack);
    ui->fsmJoystickMappingGroup->setEnabled(manualMode);
    ui->gimbalJoystickMappingGroup->setEnabled(m_currentMode == ControlMode::CoarseTrack);
}

void MainWindow::onFsmDeadzoneChanged(int value)
{
    m_fsmDeadzone = value / 100.0;
}

void MainWindow::onFsmAxisMappingChanged()
{
    m_fsmXAxisIndex = ui->fsmXAxisComboBox->currentIndex();
    m_fsmYAxisIndex = ui->fsmYAxisComboBox->currentIndex();
}

void MainWindow::onFsmInvertAxisToggled(bool checked)
{
    if (sender() == ui->fsmInvertXCheckbox) {
        m_invertFsmXAxis = checked;
    } else if (sender() == ui->fsmInvertYCheckbox) {
        m_invertFsmYAxis = checked;
    }
}

void MainWindow::onEnableFsmOutput(bool enabled)
{
    m_fsmOutputEnabled = enabled;
    if (enabled) {
        setStatusMessage("FSM output enabled");
    } else {
        setStatusMessage("FSM output disabled");
    }
}

void MainWindow::onGimbalDeadzoneChanged(int value)
{
    m_gimbalDeadzone = value / 100.0;
}

void MainWindow::onGimbalAxisMappingChanged()
{
    m_azimuthAxisIndex = ui->azimuthAxisComboBox->currentIndex();
    m_elevationAxisIndex = ui->elevationAxisComboBox->currentIndex();
    m_auxElevationAxisIndex = ui->auxElevationAxisComboBox->currentIndex();
}

void MainWindow::onGimbalInvertAxisToggled(bool checked)
{
    if (sender() == ui->invertAzimuthCheckbox) {
        m_invertAzimuthAxis = checked;
    } else if (sender() == ui->invertElevationCheckbox) {
        m_invertElevationAxis = checked;
    } else if (sender() == ui->invertAuxElevationCheckbox) {
        m_invertAuxElevationAxis = checked;
    }
}

void MainWindow::onEnableGimbalOutput(bool enabled)
{
    m_gimbalOutputEnabled = enabled;
    if (enabled) {
        setStatusMessage("Gimbal output enabled");
    } else {
        setStatusMessage("Gimbal output disabled");
    }
}

void MainWindow::onTrackerInitialize()
{
    if (m_trackerInterface->initialize()) {
        m_trackerInitialized = true;
        ui->trackerInitButton->setEnabled(false);
        ui->trackerPingButton->setEnabled(true);
        ui->trackerAutoPollCheckbox->setEnabled(true);
        setStatusMessage("Tracker initialized successfully");
    } else {
        setStatusMessage("Failed to initialize tracker");
    }
}

void MainWindow::onTrackerPing()
{
    if (m_trackerInitialized) {
        if (m_trackerInterface->ping()) {
            setStatusMessage("Tracker ping successful");
        } else {
            setStatusMessage("Tracker ping failed");
        }
    } else {
        setStatusMessage("Tracker not initialized");
    }
}

void MainWindow::onTrackerAutoPollToggled(bool checked)
{
    m_trackerAutoPoll = checked;
    if (checked) {
        m_trackerPollTimer->start();
        setStatusMessage("Tracker auto polling enabled");
    } else {
        m_trackerPollTimer->stop();
        setStatusMessage("Tracker auto polling disabled");
    }
}

void MainWindow::pollTracker()
{
    if (m_trackerInitialized) {
        double xError, yError;
        QString state;

        if (m_trackerInterface->getTrackingError(xError, yError, state)) {
            updateTrackerStatus(xError, yError, state);
        }
    }
}

void MainWindow::updateTrackerStatus(double xError, double yError, const QString &state)
{
    ui->trackerXErrorEdit->setText(QString::number(xError, 'f', 3));
    ui->trackerYErrorEdit->setText(QString::number(yError, 'f', 3));
    ui->trackerStateEdit->setText(state);
}

void MainWindow::handleTrackerError(const QString &errorMsg)
{
    setStatusMessage("Tracker error: " + errorMsg);
}

void MainWindow::onBrowseLogFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Select Log File",
                                                   QDir::homePath(),
                                                   "Log Files (*.csv)");
    if (!fileName.isEmpty()) {
        ui->logFileEdit->setText(fileName);
    }
}

void MainWindow::onStartStopLogging()
{
    if (m_loggingActive) {
        // Stop logging
        m_loggingActive = false;
        ui->startStopLoggingButton->setText("Start Logging");
        setStatusMessage("Data logging stopped");

        // Close log file
        if (m_logStream) {
            delete m_logStream;
            m_logStream = nullptr;
        }

        if (m_logFile) {
            m_logFile->close();
            delete m_logFile;
            m_logFile = nullptr;
        }
    } else {
        // Start logging
        QString fileName = ui->logFileEdit->text();
        if (fileName.isEmpty()) {
            QMessageBox::warning(this, "Logging Error", "Please select a log file first");
            return;
        }

        m_logFile = new QFile(fileName);
        if (!m_logFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Logging Error", "Could not open log file for writing");
            delete m_logFile;
            m_logFile = nullptr;
            return;
        }

        m_logStream = new QTextStream(m_logFile);

        // Write header row
        *m_logStream << "Timestamp,FSM_X,FSM_Y,Gimbal_Az,Gimbal_El,Gimbal_AuxEl,Track_Error_X,Track_Error_Y\n";

        m_loggingActive = true;
        m_loggingTimer.start();
        ui->startStopLoggingButton->setText("Stop Logging");
        setStatusMessage("Data logging started");
    }
}

void MainWindow::logData(const QString &data)
{
    if (m_loggingActive && m_logStream) {
        *m_logStream << data << '\n';
        m_logStream->flush();
    }
}

void MainWindow::onResetSystem()
{
    // First stop if running
    if (m_systemRunning) {
        onStopSystem();
    }

    // Reset all controllers
    m_fsmController->reset();
    m_gimbalController->reset();

    // Reset joystick if open
    if (m_joystickInterface->isJoystickOpen()) {
        m_joystickInterface->stop();
        m_joystickInterface->start();
    }

    // Reset tracker if initialized
    if (m_trackerInitialized) {
        m_trackerInterface->stop();
        m_trackerInterface->initialize();
    }

    // Reset UI state
    ui->fsmXProgressBar->setValue(0);
    ui->fsmYProgressBar->setValue(0);
    ui->azimuthProgressBar->setValue(0);
    ui->elevationProgressBar->setValue(0);
    ui->auxElevationProgressBar->setValue(0);

    setStatusMessage("System reset complete");
}

void MainWindow::updateSystemStatus()
{
    // Update FSM and gimbal positions from controllers
    if (m_fsmController->isInitialized()) {
        double fsmX, fsmY;
        m_fsmController->getCurrentPosition(fsmX, fsmY);
        updateFsmPosition(fsmX, fsmY);
    }

    if (m_gimbalController->isInitialized()) {
        double az, el, auxEl;
        m_gimbalController->getCurrentPosition(az, el, auxEl);
        updateGimbalPosition(az, el, auxEl);
    }

    // If we're logging data, write a record
    if (m_loggingActive) {
        QString timestamp = QString::number(m_loggingTimer.elapsed());
        double fsmX, fsmY;
        double gimbalAz, gimbalEl, gimbalAuxEl;
        double trackErrorX, trackErrorY;

        m_fsmController->getCurrentPosition(fsmX, fsmY);
        m_gimbalController->getCurrentPosition(gimbalAz, gimbalEl, gimbalAuxEl);

        QString trackState;
        m_trackerInterface->getTrackingError(trackErrorX, trackErrorY, trackState);

        QString record = QString("%1,%2,%3,%4,%5,%6,%7,%8")
                          .arg(timestamp)
                          .arg(fsmX).arg(fsmY)
                          .arg(gimbalAz).arg(gimbalEl).arg(gimbalAuxEl)
                          .arg(trackErrorX).arg(trackErrorY);

        logData(record);
    }
}

void MainWindow::updateFsmPosition(double x, double y)
{
    // Update FSM position display
    ui->fsmXProgressBar->setValue(static_cast<int>(x * 100));
    ui->fsmYProgressBar->setValue(static_cast<int>(y * 100));
}

void MainWindow::updateGimbalPosition(double azimuth, double elevation, double auxElevation)
{
    // Update gimbal position display
    ui->azimuthProgressBar->setValue(static_cast<int>(azimuth * 100));
    ui->elevationProgressBar->setValue(static_cast<int>(elevation * 100));
    ui->auxElevationProgressBar->setValue(static_cast<int>(auxElevation * 100));
}

double MainWindow::mapAxisToPosition(int axisValue, double deadzone, bool invert)
{
    // Normalize to -1.0...1.0 range
    double normalized = static_cast<double>(axisValue) / 32767.0;

    // Apply deadzone
    if (std::abs(normalized) < deadzone) {
        normalized = 0.0;
    } else {
        // Rescale the remaining range to still use the full -1.0...1.0
        double scale = 1.0 / (1.0 - deadzone);
        normalized = (std::abs(normalized) - deadzone) * scale * (normalized < 0 ? -1.0 : 1.0);
    }

    // Apply inversion if needed
    if (invert) {
        normalized = -normalized;
    }

    return normalized;
}

void MainWindow::setStatusMessage(const QString &message)
{
    ui->statusLabel->setText(message);
    qDebug() << "Status: " << message;
}