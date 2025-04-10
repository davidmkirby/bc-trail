/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionSettings;
    QAction *actionAbout;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *joystickTab;
    QVBoxLayout *joystickTabLayout;
    QHBoxLayout *joystickSelectionLayout;
    QLabel *joystickLabel;
    QComboBox *joystickComboBox;
    QPushButton *refreshJoystickButton;
    QPushButton *calibrateButton;
    QLabel *joystickInfoLabel;
    QScrollArea *joystickInputsScrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *joystickInputsLayout;
    QWidget *fsmTab;
    QVBoxLayout *fsmTabLayout;
    QGroupBox *fsmJoystickMappingGroup;
    QGridLayout *fsmMappingLayout;
    QLabel *fsmXAxisLabel;
    QComboBox *fsmXAxisComboBox;
    QCheckBox *fsmInvertXCheckbox;
    QLabel *fsmYAxisLabel;
    QComboBox *fsmYAxisComboBox;
    QCheckBox *fsmInvertYCheckbox;
    QLabel *fsmDeadzoneLabel;
    QSpinBox *fsmDeadzoneSpinBox;
    QGroupBox *fsmStatusGroup;
    QGridLayout *fsmStatusLayout;
    QLabel *fsmXPosLabel;
    QProgressBar *fsmXProgressBar;
    QLabel *fsmYPosLabel;
    QProgressBar *fsmYProgressBar;
    QCheckBox *enableFsmOutputCheckbox;
    QSpacerItem *fsmSpacer;
    QWidget *gimbalTab;
    QVBoxLayout *gimbalTabLayout;
    QGroupBox *gimbalJoystickMappingGroup;
    QGridLayout *gimbalMappingLayout;
    QLabel *azimuthAxisLabel;
    QComboBox *azimuthAxisComboBox;
    QCheckBox *invertAzimuthCheckbox;
    QLabel *elevationAxisLabel;
    QComboBox *elevationAxisComboBox;
    QCheckBox *invertElevationCheckbox;
    QLabel *auxElevationAxisLabel;
    QComboBox *auxElevationAxisComboBox;
    QCheckBox *invertAuxElevationCheckbox;
    QLabel *gimbalDeadzoneLabel;
    QSpinBox *gimbalDeadzoneSpinBox;
    QGroupBox *gimbalStatusGroup;
    QGridLayout *gimbalStatusLayout;
    QLabel *azimuthPosLabel;
    QProgressBar *azimuthProgressBar;
    QLabel *elevationPosLabel;
    QProgressBar *elevationProgressBar;
    QLabel *auxElevationPosLabel;
    QProgressBar *auxElevationProgressBar;
    QCheckBox *enableGimbalOutputCheckbox;
    QSpacerItem *gimbalSpacer;
    QWidget *trackingTab;
    QVBoxLayout *trackingTabLayout;
    QGroupBox *trackingModeGroup;
    QVBoxLayout *trackingModeLayout;
    QRadioButton *coarseTrackingRadio;
    QRadioButton *fineTrackingRadio;
    QRadioButton *autoTrackingRadio;
    QGroupBox *trackerStatusGroup;
    QGridLayout *trackerStatusLayout;
    QLabel *trackerXErrorLabel;
    QLineEdit *trackerXErrorEdit;
    QLabel *trackerYErrorLabel;
    QLineEdit *trackerYErrorEdit;
    QLabel *trackerStateLabel;
    QLineEdit *trackerStateEdit;
    QHBoxLayout *trackerControlLayout;
    QPushButton *trackerInitButton;
    QPushButton *trackerPingButton;
    QCheckBox *trackerAutoPollCheckbox;
    QGroupBox *dataLoggingGroup;
    QHBoxLayout *dataLoggingLayout;
    QLineEdit *logFileEdit;
    QPushButton *browseLogButton;
    QPushButton *startStopLoggingButton;
    QSpacerItem *trackingSpacer;
    QGroupBox *statusGroup;
    QHBoxLayout *statusLayout;
    QLabel *statusLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *resetButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName("actionSettings");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        joystickTab = new QWidget();
        joystickTab->setObjectName("joystickTab");
        joystickTabLayout = new QVBoxLayout(joystickTab);
        joystickTabLayout->setObjectName("joystickTabLayout");
        joystickSelectionLayout = new QHBoxLayout();
        joystickSelectionLayout->setObjectName("joystickSelectionLayout");
        joystickLabel = new QLabel(joystickTab);
        joystickLabel->setObjectName("joystickLabel");

        joystickSelectionLayout->addWidget(joystickLabel);

        joystickComboBox = new QComboBox(joystickTab);
        joystickComboBox->setObjectName("joystickComboBox");

        joystickSelectionLayout->addWidget(joystickComboBox);

        refreshJoystickButton = new QPushButton(joystickTab);
        refreshJoystickButton->setObjectName("refreshJoystickButton");

        joystickSelectionLayout->addWidget(refreshJoystickButton);

        calibrateButton = new QPushButton(joystickTab);
        calibrateButton->setObjectName("calibrateButton");

        joystickSelectionLayout->addWidget(calibrateButton);


        joystickTabLayout->addLayout(joystickSelectionLayout);

        joystickInfoLabel = new QLabel(joystickTab);
        joystickInfoLabel->setObjectName("joystickInfoLabel");

        joystickTabLayout->addWidget(joystickInfoLabel);

        joystickInputsScrollArea = new QScrollArea(joystickTab);
        joystickInputsScrollArea->setObjectName("joystickInputsScrollArea");
        joystickInputsScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 758, 390));
        joystickInputsLayout = new QVBoxLayout(scrollAreaWidgetContents);
        joystickInputsLayout->setObjectName("joystickInputsLayout");
        joystickInputsScrollArea->setWidget(scrollAreaWidgetContents);

        joystickTabLayout->addWidget(joystickInputsScrollArea);

        tabWidget->addTab(joystickTab, QString());
        fsmTab = new QWidget();
        fsmTab->setObjectName("fsmTab");
        fsmTabLayout = new QVBoxLayout(fsmTab);
        fsmTabLayout->setObjectName("fsmTabLayout");
        fsmJoystickMappingGroup = new QGroupBox(fsmTab);
        fsmJoystickMappingGroup->setObjectName("fsmJoystickMappingGroup");
        fsmMappingLayout = new QGridLayout(fsmJoystickMappingGroup);
        fsmMappingLayout->setObjectName("fsmMappingLayout");
        fsmXAxisLabel = new QLabel(fsmJoystickMappingGroup);
        fsmXAxisLabel->setObjectName("fsmXAxisLabel");

        fsmMappingLayout->addWidget(fsmXAxisLabel, 0, 0, 1, 1);

        fsmXAxisComboBox = new QComboBox(fsmJoystickMappingGroup);
        fsmXAxisComboBox->setObjectName("fsmXAxisComboBox");

        fsmMappingLayout->addWidget(fsmXAxisComboBox, 0, 1, 1, 1);

        fsmInvertXCheckbox = new QCheckBox(fsmJoystickMappingGroup);
        fsmInvertXCheckbox->setObjectName("fsmInvertXCheckbox");

        fsmMappingLayout->addWidget(fsmInvertXCheckbox, 0, 2, 1, 1);

        fsmYAxisLabel = new QLabel(fsmJoystickMappingGroup);
        fsmYAxisLabel->setObjectName("fsmYAxisLabel");

        fsmMappingLayout->addWidget(fsmYAxisLabel, 1, 0, 1, 1);

        fsmYAxisComboBox = new QComboBox(fsmJoystickMappingGroup);
        fsmYAxisComboBox->setObjectName("fsmYAxisComboBox");

        fsmMappingLayout->addWidget(fsmYAxisComboBox, 1, 1, 1, 1);

        fsmInvertYCheckbox = new QCheckBox(fsmJoystickMappingGroup);
        fsmInvertYCheckbox->setObjectName("fsmInvertYCheckbox");

        fsmMappingLayout->addWidget(fsmInvertYCheckbox, 1, 2, 1, 1);

        fsmDeadzoneLabel = new QLabel(fsmJoystickMappingGroup);
        fsmDeadzoneLabel->setObjectName("fsmDeadzoneLabel");

        fsmMappingLayout->addWidget(fsmDeadzoneLabel, 2, 0, 1, 1);

        fsmDeadzoneSpinBox = new QSpinBox(fsmJoystickMappingGroup);
        fsmDeadzoneSpinBox->setObjectName("fsmDeadzoneSpinBox");
        fsmDeadzoneSpinBox->setMaximum(50);
        fsmDeadzoneSpinBox->setValue(5);

        fsmMappingLayout->addWidget(fsmDeadzoneSpinBox, 2, 1, 1, 1);


        fsmTabLayout->addWidget(fsmJoystickMappingGroup);

        fsmStatusGroup = new QGroupBox(fsmTab);
        fsmStatusGroup->setObjectName("fsmStatusGroup");
        fsmStatusLayout = new QGridLayout(fsmStatusGroup);
        fsmStatusLayout->setObjectName("fsmStatusLayout");
        fsmXPosLabel = new QLabel(fsmStatusGroup);
        fsmXPosLabel->setObjectName("fsmXPosLabel");

        fsmStatusLayout->addWidget(fsmXPosLabel, 0, 0, 1, 1);

        fsmXProgressBar = new QProgressBar(fsmStatusGroup);
        fsmXProgressBar->setObjectName("fsmXProgressBar");
        fsmXProgressBar->setMinimum(-100);
        fsmXProgressBar->setMaximum(100);
        fsmXProgressBar->setValue(0);

        fsmStatusLayout->addWidget(fsmXProgressBar, 0, 1, 1, 1);

        fsmYPosLabel = new QLabel(fsmStatusGroup);
        fsmYPosLabel->setObjectName("fsmYPosLabel");

        fsmStatusLayout->addWidget(fsmYPosLabel, 1, 0, 1, 1);

        fsmYProgressBar = new QProgressBar(fsmStatusGroup);
        fsmYProgressBar->setObjectName("fsmYProgressBar");
        fsmYProgressBar->setMinimum(-100);
        fsmYProgressBar->setMaximum(100);
        fsmYProgressBar->setValue(0);

        fsmStatusLayout->addWidget(fsmYProgressBar, 1, 1, 1, 1);


        fsmTabLayout->addWidget(fsmStatusGroup);

        enableFsmOutputCheckbox = new QCheckBox(fsmTab);
        enableFsmOutputCheckbox->setObjectName("enableFsmOutputCheckbox");

        fsmTabLayout->addWidget(enableFsmOutputCheckbox);

        fsmSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        fsmTabLayout->addItem(fsmSpacer);

        tabWidget->addTab(fsmTab, QString());
        gimbalTab = new QWidget();
        gimbalTab->setObjectName("gimbalTab");
        gimbalTabLayout = new QVBoxLayout(gimbalTab);
        gimbalTabLayout->setObjectName("gimbalTabLayout");
        gimbalJoystickMappingGroup = new QGroupBox(gimbalTab);
        gimbalJoystickMappingGroup->setObjectName("gimbalJoystickMappingGroup");
        gimbalMappingLayout = new QGridLayout(gimbalJoystickMappingGroup);
        gimbalMappingLayout->setObjectName("gimbalMappingLayout");
        azimuthAxisLabel = new QLabel(gimbalJoystickMappingGroup);
        azimuthAxisLabel->setObjectName("azimuthAxisLabel");

        gimbalMappingLayout->addWidget(azimuthAxisLabel, 0, 0, 1, 1);

        azimuthAxisComboBox = new QComboBox(gimbalJoystickMappingGroup);
        azimuthAxisComboBox->setObjectName("azimuthAxisComboBox");

        gimbalMappingLayout->addWidget(azimuthAxisComboBox, 0, 1, 1, 1);

        invertAzimuthCheckbox = new QCheckBox(gimbalJoystickMappingGroup);
        invertAzimuthCheckbox->setObjectName("invertAzimuthCheckbox");

        gimbalMappingLayout->addWidget(invertAzimuthCheckbox, 0, 2, 1, 1);

        elevationAxisLabel = new QLabel(gimbalJoystickMappingGroup);
        elevationAxisLabel->setObjectName("elevationAxisLabel");

        gimbalMappingLayout->addWidget(elevationAxisLabel, 1, 0, 1, 1);

        elevationAxisComboBox = new QComboBox(gimbalJoystickMappingGroup);
        elevationAxisComboBox->setObjectName("elevationAxisComboBox");

        gimbalMappingLayout->addWidget(elevationAxisComboBox, 1, 1, 1, 1);

        invertElevationCheckbox = new QCheckBox(gimbalJoystickMappingGroup);
        invertElevationCheckbox->setObjectName("invertElevationCheckbox");

        gimbalMappingLayout->addWidget(invertElevationCheckbox, 1, 2, 1, 1);

        auxElevationAxisLabel = new QLabel(gimbalJoystickMappingGroup);
        auxElevationAxisLabel->setObjectName("auxElevationAxisLabel");

        gimbalMappingLayout->addWidget(auxElevationAxisLabel, 2, 0, 1, 1);

        auxElevationAxisComboBox = new QComboBox(gimbalJoystickMappingGroup);
        auxElevationAxisComboBox->setObjectName("auxElevationAxisComboBox");

        gimbalMappingLayout->addWidget(auxElevationAxisComboBox, 2, 1, 1, 1);

        invertAuxElevationCheckbox = new QCheckBox(gimbalJoystickMappingGroup);
        invertAuxElevationCheckbox->setObjectName("invertAuxElevationCheckbox");

        gimbalMappingLayout->addWidget(invertAuxElevationCheckbox, 2, 2, 1, 1);

        gimbalDeadzoneLabel = new QLabel(gimbalJoystickMappingGroup);
        gimbalDeadzoneLabel->setObjectName("gimbalDeadzoneLabel");

        gimbalMappingLayout->addWidget(gimbalDeadzoneLabel, 3, 0, 1, 1);

        gimbalDeadzoneSpinBox = new QSpinBox(gimbalJoystickMappingGroup);
        gimbalDeadzoneSpinBox->setObjectName("gimbalDeadzoneSpinBox");
        gimbalDeadzoneSpinBox->setMaximum(50);
        gimbalDeadzoneSpinBox->setValue(5);

        gimbalMappingLayout->addWidget(gimbalDeadzoneSpinBox, 3, 1, 1, 1);


        gimbalTabLayout->addWidget(gimbalJoystickMappingGroup);

        gimbalStatusGroup = new QGroupBox(gimbalTab);
        gimbalStatusGroup->setObjectName("gimbalStatusGroup");
        gimbalStatusLayout = new QGridLayout(gimbalStatusGroup);
        gimbalStatusLayout->setObjectName("gimbalStatusLayout");
        azimuthPosLabel = new QLabel(gimbalStatusGroup);
        azimuthPosLabel->setObjectName("azimuthPosLabel");

        gimbalStatusLayout->addWidget(azimuthPosLabel, 0, 0, 1, 1);

        azimuthProgressBar = new QProgressBar(gimbalStatusGroup);
        azimuthProgressBar->setObjectName("azimuthProgressBar");
        azimuthProgressBar->setMinimum(-100);
        azimuthProgressBar->setMaximum(100);
        azimuthProgressBar->setValue(0);

        gimbalStatusLayout->addWidget(azimuthProgressBar, 0, 1, 1, 1);

        elevationPosLabel = new QLabel(gimbalStatusGroup);
        elevationPosLabel->setObjectName("elevationPosLabel");

        gimbalStatusLayout->addWidget(elevationPosLabel, 1, 0, 1, 1);

        elevationProgressBar = new QProgressBar(gimbalStatusGroup);
        elevationProgressBar->setObjectName("elevationProgressBar");
        elevationProgressBar->setMinimum(-100);
        elevationProgressBar->setMaximum(100);
        elevationProgressBar->setValue(0);

        gimbalStatusLayout->addWidget(elevationProgressBar, 1, 1, 1, 1);

        auxElevationPosLabel = new QLabel(gimbalStatusGroup);
        auxElevationPosLabel->setObjectName("auxElevationPosLabel");

        gimbalStatusLayout->addWidget(auxElevationPosLabel, 2, 0, 1, 1);

        auxElevationProgressBar = new QProgressBar(gimbalStatusGroup);
        auxElevationProgressBar->setObjectName("auxElevationProgressBar");
        auxElevationProgressBar->setMinimum(-100);
        auxElevationProgressBar->setMaximum(100);
        auxElevationProgressBar->setValue(0);

        gimbalStatusLayout->addWidget(auxElevationProgressBar, 2, 1, 1, 1);


        gimbalTabLayout->addWidget(gimbalStatusGroup);

        enableGimbalOutputCheckbox = new QCheckBox(gimbalTab);
        enableGimbalOutputCheckbox->setObjectName("enableGimbalOutputCheckbox");

        gimbalTabLayout->addWidget(enableGimbalOutputCheckbox);

        gimbalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gimbalTabLayout->addItem(gimbalSpacer);

        tabWidget->addTab(gimbalTab, QString());
        trackingTab = new QWidget();
        trackingTab->setObjectName("trackingTab");
        trackingTabLayout = new QVBoxLayout(trackingTab);
        trackingTabLayout->setObjectName("trackingTabLayout");
        trackingModeGroup = new QGroupBox(trackingTab);
        trackingModeGroup->setObjectName("trackingModeGroup");
        trackingModeLayout = new QVBoxLayout(trackingModeGroup);
        trackingModeLayout->setObjectName("trackingModeLayout");
        coarseTrackingRadio = new QRadioButton(trackingModeGroup);
        coarseTrackingRadio->setObjectName("coarseTrackingRadio");
        coarseTrackingRadio->setChecked(true);

        trackingModeLayout->addWidget(coarseTrackingRadio);

        fineTrackingRadio = new QRadioButton(trackingModeGroup);
        fineTrackingRadio->setObjectName("fineTrackingRadio");

        trackingModeLayout->addWidget(fineTrackingRadio);

        autoTrackingRadio = new QRadioButton(trackingModeGroup);
        autoTrackingRadio->setObjectName("autoTrackingRadio");

        trackingModeLayout->addWidget(autoTrackingRadio);


        trackingTabLayout->addWidget(trackingModeGroup);

        trackerStatusGroup = new QGroupBox(trackingTab);
        trackerStatusGroup->setObjectName("trackerStatusGroup");
        trackerStatusLayout = new QGridLayout(trackerStatusGroup);
        trackerStatusLayout->setObjectName("trackerStatusLayout");
        trackerXErrorLabel = new QLabel(trackerStatusGroup);
        trackerXErrorLabel->setObjectName("trackerXErrorLabel");

        trackerStatusLayout->addWidget(trackerXErrorLabel, 0, 0, 1, 1);

        trackerXErrorEdit = new QLineEdit(trackerStatusGroup);
        trackerXErrorEdit->setObjectName("trackerXErrorEdit");
        trackerXErrorEdit->setReadOnly(true);

        trackerStatusLayout->addWidget(trackerXErrorEdit, 0, 1, 1, 1);

        trackerYErrorLabel = new QLabel(trackerStatusGroup);
        trackerYErrorLabel->setObjectName("trackerYErrorLabel");

        trackerStatusLayout->addWidget(trackerYErrorLabel, 1, 0, 1, 1);

        trackerYErrorEdit = new QLineEdit(trackerStatusGroup);
        trackerYErrorEdit->setObjectName("trackerYErrorEdit");
        trackerYErrorEdit->setReadOnly(true);

        trackerStatusLayout->addWidget(trackerYErrorEdit, 1, 1, 1, 1);

        trackerStateLabel = new QLabel(trackerStatusGroup);
        trackerStateLabel->setObjectName("trackerStateLabel");

        trackerStatusLayout->addWidget(trackerStateLabel, 2, 0, 1, 1);

        trackerStateEdit = new QLineEdit(trackerStatusGroup);
        trackerStateEdit->setObjectName("trackerStateEdit");
        trackerStateEdit->setReadOnly(true);

        trackerStatusLayout->addWidget(trackerStateEdit, 2, 1, 1, 1);


        trackingTabLayout->addWidget(trackerStatusGroup);

        trackerControlLayout = new QHBoxLayout();
        trackerControlLayout->setObjectName("trackerControlLayout");
        trackerInitButton = new QPushButton(trackingTab);
        trackerInitButton->setObjectName("trackerInitButton");

        trackerControlLayout->addWidget(trackerInitButton);

        trackerPingButton = new QPushButton(trackingTab);
        trackerPingButton->setObjectName("trackerPingButton");

        trackerControlLayout->addWidget(trackerPingButton);

        trackerAutoPollCheckbox = new QCheckBox(trackingTab);
        trackerAutoPollCheckbox->setObjectName("trackerAutoPollCheckbox");

        trackerControlLayout->addWidget(trackerAutoPollCheckbox);


        trackingTabLayout->addLayout(trackerControlLayout);

        dataLoggingGroup = new QGroupBox(trackingTab);
        dataLoggingGroup->setObjectName("dataLoggingGroup");
        dataLoggingLayout = new QHBoxLayout(dataLoggingGroup);
        dataLoggingLayout->setObjectName("dataLoggingLayout");
        logFileEdit = new QLineEdit(dataLoggingGroup);
        logFileEdit->setObjectName("logFileEdit");

        dataLoggingLayout->addWidget(logFileEdit);

        browseLogButton = new QPushButton(dataLoggingGroup);
        browseLogButton->setObjectName("browseLogButton");

        dataLoggingLayout->addWidget(browseLogButton);

        startStopLoggingButton = new QPushButton(dataLoggingGroup);
        startStopLoggingButton->setObjectName("startStopLoggingButton");

        dataLoggingLayout->addWidget(startStopLoggingButton);


        trackingTabLayout->addWidget(dataLoggingGroup);

        trackingSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        trackingTabLayout->addItem(trackingSpacer);

        tabWidget->addTab(trackingTab, QString());

        verticalLayout->addWidget(tabWidget);

        statusGroup = new QGroupBox(centralwidget);
        statusGroup->setObjectName("statusGroup");
        statusLayout = new QHBoxLayout(statusGroup);
        statusLayout->setObjectName("statusLayout");
        statusLabel = new QLabel(statusGroup);
        statusLabel->setObjectName("statusLabel");

        statusLayout->addWidget(statusLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        statusLayout->addItem(horizontalSpacer);

        resetButton = new QPushButton(statusGroup);
        resetButton->setObjectName("resetButton");

        statusLayout->addWidget(resetButton);


        verticalLayout->addWidget(statusGroup);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuTools = new QMenu(menubar);
        menuTools->setObjectName("menuTools");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTools->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionExit);
        menuTools->addAction(actionSettings);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "BC-TRAIL Control System", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionSettings->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        joystickLabel->setText(QCoreApplication::translate("MainWindow", "Select Joystick:", nullptr));
        refreshJoystickButton->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        calibrateButton->setText(QCoreApplication::translate("MainWindow", "Calibrate", nullptr));
        joystickInfoLabel->setText(QCoreApplication::translate("MainWindow", "No joystick selected", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(joystickTab), QCoreApplication::translate("MainWindow", "Joystick Input", nullptr));
        fsmJoystickMappingGroup->setTitle(QCoreApplication::translate("MainWindow", "Joystick to FSM Mapping", nullptr));
        fsmXAxisLabel->setText(QCoreApplication::translate("MainWindow", "X-Axis:", nullptr));
        fsmInvertXCheckbox->setText(QCoreApplication::translate("MainWindow", "Invert", nullptr));
        fsmYAxisLabel->setText(QCoreApplication::translate("MainWindow", "Y-Axis:", nullptr));
        fsmInvertYCheckbox->setText(QCoreApplication::translate("MainWindow", "Invert", nullptr));
        fsmDeadzoneLabel->setText(QCoreApplication::translate("MainWindow", "Deadzone:", nullptr));
        fsmDeadzoneSpinBox->setSuffix(QCoreApplication::translate("MainWindow", "%", nullptr));
        fsmStatusGroup->setTitle(QCoreApplication::translate("MainWindow", "FSM Status", nullptr));
        fsmXPosLabel->setText(QCoreApplication::translate("MainWindow", "X Position:", nullptr));
        fsmXProgressBar->setFormat(QCoreApplication::translate("MainWindow", "%v", nullptr));
        fsmYPosLabel->setText(QCoreApplication::translate("MainWindow", "Y Position:", nullptr));
        fsmYProgressBar->setFormat(QCoreApplication::translate("MainWindow", "%v", nullptr));
        enableFsmOutputCheckbox->setText(QCoreApplication::translate("MainWindow", "Enable FSM Output", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(fsmTab), QCoreApplication::translate("MainWindow", "FSM Control", nullptr));
        gimbalJoystickMappingGroup->setTitle(QCoreApplication::translate("MainWindow", "Joystick to Gimbal Mapping", nullptr));
        azimuthAxisLabel->setText(QCoreApplication::translate("MainWindow", "Azimuth:", nullptr));
        invertAzimuthCheckbox->setText(QCoreApplication::translate("MainWindow", "Invert", nullptr));
        elevationAxisLabel->setText(QCoreApplication::translate("MainWindow", "Elevation:", nullptr));
        invertElevationCheckbox->setText(QCoreApplication::translate("MainWindow", "Invert", nullptr));
        auxElevationAxisLabel->setText(QCoreApplication::translate("MainWindow", "Aux Elevation:", nullptr));
        invertAuxElevationCheckbox->setText(QCoreApplication::translate("MainWindow", "Invert", nullptr));
        gimbalDeadzoneLabel->setText(QCoreApplication::translate("MainWindow", "Deadzone:", nullptr));
        gimbalDeadzoneSpinBox->setSuffix(QCoreApplication::translate("MainWindow", "%", nullptr));
        gimbalStatusGroup->setTitle(QCoreApplication::translate("MainWindow", "Gimbal Status", nullptr));
        azimuthPosLabel->setText(QCoreApplication::translate("MainWindow", "Azimuth:", nullptr));
        azimuthProgressBar->setFormat(QCoreApplication::translate("MainWindow", "%v", nullptr));
        elevationPosLabel->setText(QCoreApplication::translate("MainWindow", "Elevation:", nullptr));
        elevationProgressBar->setFormat(QCoreApplication::translate("MainWindow", "%v", nullptr));
        auxElevationPosLabel->setText(QCoreApplication::translate("MainWindow", "Aux Elevation:", nullptr));
        auxElevationProgressBar->setFormat(QCoreApplication::translate("MainWindow", "%v", nullptr));
        enableGimbalOutputCheckbox->setText(QCoreApplication::translate("MainWindow", "Enable Gimbal Output", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(gimbalTab), QCoreApplication::translate("MainWindow", "Gimbal Control", nullptr));
        trackingModeGroup->setTitle(QCoreApplication::translate("MainWindow", "Tracking Mode", nullptr));
        coarseTrackingRadio->setText(QCoreApplication::translate("MainWindow", "Coarse Tracking (Manual Gimbal and FSM)", nullptr));
        fineTrackingRadio->setText(QCoreApplication::translate("MainWindow", "Fine Tracking (Manual FSM Only)", nullptr));
        autoTrackingRadio->setText(QCoreApplication::translate("MainWindow", "Auto Tracking (Tracker Card)", nullptr));
        trackerStatusGroup->setTitle(QCoreApplication::translate("MainWindow", "Tracker Status", nullptr));
        trackerXErrorLabel->setText(QCoreApplication::translate("MainWindow", "X Error:", nullptr));
        trackerYErrorLabel->setText(QCoreApplication::translate("MainWindow", "Y Error:", nullptr));
        trackerStateLabel->setText(QCoreApplication::translate("MainWindow", "Track State:", nullptr));
        trackerInitButton->setText(QCoreApplication::translate("MainWindow", "Initialize Tracker", nullptr));
        trackerPingButton->setText(QCoreApplication::translate("MainWindow", "Ping Tracker", nullptr));
        trackerAutoPollCheckbox->setText(QCoreApplication::translate("MainWindow", "Auto Poll", nullptr));
        dataLoggingGroup->setTitle(QCoreApplication::translate("MainWindow", "Data Logging", nullptr));
        logFileEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Select log file location...", nullptr));
        browseLogButton->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        startStopLoggingButton->setText(QCoreApplication::translate("MainWindow", "Start Logging", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(trackingTab), QCoreApplication::translate("MainWindow", "Tracking", nullptr));
        statusGroup->setTitle(QCoreApplication::translate("MainWindow", "System Status", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "System Ready", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset System", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuTools->setTitle(QCoreApplication::translate("MainWindow", "Tools", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
