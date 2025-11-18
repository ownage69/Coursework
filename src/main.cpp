#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    app.setStyleSheet(
        "QApplication { background-color: #ffffff; color: #333333; font-family: 'Segoe UI', Arial, sans-serif; }"
        "QMainWindow { background-color: #ffffff; color: #333333; }"
        "QMessageBox { background-color: #ffffff; color: #333333; }"
        "QMessageBox QLabel { color: #333333; }"
        "QMessageBox QPushButton { background-color: #2196f3; color: white; border: none; padding: 10px 16px; border-radius: 6px; }"
        "QMessageBox QPushButton:hover { background-color: #1976d2; }"
        "QMessageBox QPushButton:pressed { background-color: #1565c0; }"
        "QLineEdit { background-color: #ffffff; color: #333333; border: 1px solid #e0e0e0; padding: 8px; border-radius: 4px; }"
        "QLineEdit:focus { border-color: #2196f3; }"
        "QComboBox { background-color: #ffffff; color: #333333; border: 1px solid #e0e0e0; padding: 8px; border-radius: 4px; }"
        "QComboBox::drop-down { border: none; }"
        "QSpinBox, QDoubleSpinBox { background-color: #ffffff; color: #333333; border: 1px solid #e0e0e0; padding: 8px; border-radius: 4px; }"
        "QSpinBox::up-button, QDoubleSpinBox::up-button { background-color: #f5f5f5; border: none; }"
        "QSpinBox::down-button, QDoubleSpinBox::down-button { background-color: #f5f5f5; border: none; }"
        "QCheckBox { color: #333333; }"
        "QCheckBox::indicator { background-color: #ffffff; border: 1px solid #e0e0e0; }"
        "QCheckBox::indicator:checked { background-color: #2196f3; }"
        "QLabel { color: #333333; }"
        "QGroupBox { border: 2px solid #e0e0e0; border-radius: 5px; margin-top: 1ex; color: #333333; }"
        "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }"
        "QPushButton { background-color: #2196f3; color: white; border: none; padding: 10px 16px; border-radius: 6px; }"
        "QPushButton:hover { background-color: #1976d2; }"
        "QPushButton:pressed { background-color: #1565c0; }"
    );
    
    try {
        qDebug() << "Starting application...";
        
        MainWindow window;
        qDebug() << "MainWindow created successfully";
        
        window.show();
        qDebug() << "MainWindow shown, starting event loop";
        
        return app.exec();
        
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Application Error", 
                            QString("A critical error occurred: %1").arg(e.what()));
        qCritical() << "Exception caught:" << e.what();
        return -1;
    } catch (...) {
        QMessageBox::critical(nullptr, "Application Error", 
                            "An unknown error occurred during application startup.");
        qCritical() << "Unknown exception caught";
        return -1;
    }
    
    return 0;
}