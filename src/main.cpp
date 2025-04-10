#include <QApplication>
#include <QFile>
#include <QStyleFactory>
#include <QCommandLineParser>
#include <QThread>
#include <iostream>

#include "main_window.h"

int main(int argc, char *argv[])
{
    
    QApplication app(argc, argv);

    // Set application information
    QApplication::setApplicationName("BC-TRAIL");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setOrganizationName("Leidos");

    // Use fusion style for a modern look
    app.setStyle(QStyleFactory::create("Fusion"));

    // Set up a dark theme color palette
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    app.setPalette(darkPalette);

    // Load and apply application stylesheet
    QFile styleFile(":/styles/bc-trail.qss");
    if (styleFile.exists()) {
        styleFile.open(QFile::ReadOnly);
        QString style = styleFile.readAll();
        app.setStyleSheet(style);
        styleFile.close();
    }

    // Command line parser
    QCommandLineParser parser;
    parser.setApplicationDescription("BC-TRAIL - Control System for Fast-Steering Mirrors and Gimbals");
    parser.addHelpOption();
    parser.addVersionOption();

    // Add command line options
    QCommandLineOption rtPriorityOption("rt-priority", "Set realtime thread priority");
    parser.addOption(rtPriorityOption);

    // Process the command line
    parser.process(app);

    // If realtime priority requested, try to set process priority
    if (parser.isSet(rtPriorityOption)) {
        // This is just a placeholder - actual priority setting would be
        // done with platform-specific code (pthread_setschedparam on Linux)
        std::cout << "Attempting to set realtime thread priority" << std::endl;
    }

    // Create and show main window
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}