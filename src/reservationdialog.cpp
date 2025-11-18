#include "reservationdialog.h"
#include <QMessageBox>
#include <QVariant>

ReservationDialog::ReservationDialog(DealershipManager& manager, QWidget* parent) 
    : QDialog(parent), manager(manager), selectedCarIndex(0), selectedClientIndex(0) {
    setWindowTitle("Reserve Car");
    setModal(true);

    setStyleSheet(
        "QDialog { background-color: #ffffff; color: #333333; font-family: 'Segoe UI', Arial, sans-serif; }"
        "QLineEdit { background-color: #ffffff; color: #333333; border: 1px solid #e0e0e0; padding: 8px; border-radius: 4px; }"
        "QLineEdit:focus { border-color: #2196f3; }"
        "QComboBox { background-color: #ffffff; color: #333333; border: 1px solid #e0e0e0; padding: 8px; border-radius: 4px; }"
        "QComboBox::drop-down { border: none; }"
        "QSpinBox, QDoubleSpinBox { background-color: #ffffff; color: #333333; border: 1px solid #e0e0e0; padding: 8px; border-radius: 4px; }"
        "QSpinBox::up-button, QDoubleSpinBox::up-button { background-color: #f5f5f5; border: none; }"
        "QSpinBox::down-button, QDoubleSpinBox::down-button { background-color: #f5f5f5; border: none; }"
        "QLabel { color: #333333; }"
        "QPushButton { background-color: #2196f3; color: #ffffff; border: none; padding: 10px 16px; border-radius: 6px; }"
        "QPushButton:hover { background-color: #1976d2; }"
        "QPushButton:pressed { background-color: #1565c0; }"
    );
    
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    QFormLayout* formLayout = new QFormLayout;
    
    carCombo = new QComboBox;
    clientCombo = new QComboBox;
    
    const auto& cars = manager.getCars();
    const auto& clients = manager.getClients();
    
    if (cars.empty() || clients.empty()) {
        QMessageBox::warning(this, "Error", "No cars or clients available!");
        return;
    }
    
    for (size_t i = 0; i < cars.size(); ++i) {
        if (!cars[i].isReserved() && cars[i].getStock() > 0) {
            QString displayText = QString("%1 %2 ($%3)").arg(QString::fromStdString(cars[i].getBrand()))
                                                         .arg(QString::fromStdString(cars[i].getModel()))
                                                         .arg(cars[i].getPrice(), 0, 'f', 2);
            carCombo->addItem(displayText, QVariant::fromValue(i));
        }
    }
    
    for (size_t i = 0; i < clients.size(); ++i) {
        clientCombo->addItem(QString::fromStdString(clients[i].getFullName()));
    }
    
    if (carCombo->count() == 0) {
        QMessageBox::warning(this, "Error", "No available cars for reservation!");
        return;
    }
    
    formLayout->addRow("Select Car:", carCombo);
    formLayout->addRow("Select Client:", clientCombo);
    
    mainLayout->addLayout(formLayout);
    
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    mainLayout->addWidget(buttonBox);
    
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ReservationDialog::validateAndAccept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void ReservationDialog::setSelectedCar(size_t index) {
    const auto& cars = manager.getCars();
    if (index >= cars.size()) {
        return;
    }
    
    for (int i = 0; i < carCombo->count(); ++i) {
        QVariant data = carCombo->itemData(i);
        if (data.isValid() && data.value<size_t>() == index) {
            carCombo->setCurrentIndex(i);
            break;
        }
    }
}

size_t ReservationDialog::getSelectedCarIndex() const {
    return selectedCarIndex;
}

size_t ReservationDialog::getSelectedClientIndex() const {
    return selectedClientIndex;
}

void ReservationDialog::validateAndAccept() {
    QVariant data = carCombo->currentData();
    if (data.isValid()) {
        selectedCarIndex = data.value<size_t>();
    } else {
        selectedCarIndex = 0;
    }
    selectedClientIndex = clientCombo->currentIndex();
    
    accept();
}