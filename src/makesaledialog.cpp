#include "makesaledialog.h"
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>

MakeSaleDialog::MakeSaleDialog(DealershipManager& manager, QWidget* parent) : QDialog(parent), manager(manager) {
    setWindowTitle("Make Sale");
    setStyleSheet(
        "QDialog { background-color: #ffffff; color: #333333; font-family: 'Segoe UI', Arial, sans-serif; }"
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
    setModal(true);
    
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    auto* formLayout = new QFormLayout;
    
    carCombo = new QComboBox;
    const auto& cars = manager.getCars();
    for (size_t i = 0; i < cars.size(); ++i) {
        QString displayText = QString("%1 %2 (%3) - Stock: %4")
            .arg(QString::fromStdString(cars[i].getBrand()))
            .arg(QString::fromStdString(cars[i].getModel()))
            .arg(QString::fromStdString(cars[i].getVin()))
            .arg(cars[i].getStock());
        if (cars[i].isReserved()) {
            displayText += " [RESERVED]";
        }
        carCombo->addItem(displayText, QVariant::fromValue(i));
    }
    formLayout->addRow("Car (VIN):", carCombo);
    
    clientCombo = new QComboBox;
    const auto& clients = manager.getClients();
    for (size_t i = 0; i < clients.size(); ++i) {
        QString displayText = QString("%1 - Balance: $%2")
            .arg(QString::fromStdString(clients[i].getFullName()))
            .arg(clients[i].getBalance(), 0, 'f', 2);
        clientCombo->addItem(displayText, QVariant::fromValue(i));
    }
    formLayout->addRow("Client:", clientCombo);
    
    mainLayout->addLayout(formLayout);
    
    optionsGroup = new QGroupBox("Configure Options");
    auto* optionsLayout = new QVBoxLayout(optionsGroup);
    optionsLayout->addWidget(new QLabel("Options:"));
    const auto& availableOptions = Car::getAvailableOptions();
    for (const auto& [name, price] : availableOptions) {
        auto* checkBox = new QCheckBox(QString("%1 ($%2)").arg(QString::fromStdString(name)).arg(price, 0, 'f', 0));
        optionCheckboxes[name] = checkBox;
        optionsLayout->addWidget(checkBox);
        connect(checkBox, &QCheckBox::toggled, this, &MakeSaleDialog::updatePriceInfo);
    }
    
    mainLayout->addWidget(optionsGroup);
    
    auto* priceLayout = new QFormLayout;
    
    originalPriceLabel = new QLabel("$0.00");
    priceLayout->addRow("Original Price:", originalPriceLabel);
    
    discountLabel = new QLabel("0.0%");
    priceLayout->addRow("Discount:", discountLabel);
    
    finalPriceLabel = new QLabel("$0.00");
    finalPriceLabel->setStyleSheet("font-weight: bold; font-size: 14px; color: #28a745;");
    priceLayout->addRow("Final Price:", finalPriceLabel);
    
    clientBalanceLabel = new QLabel("$0.00");
    priceLayout->addRow("Client Balance:", clientBalanceLabel);
    
    mainLayout->addLayout(priceLayout);
    
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    mainLayout->addWidget(buttonBox);
    
    connect(carCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MakeSaleDialog::onCarChanged);
    connect(clientCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MakeSaleDialog::updatePriceInfo);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &MakeSaleDialog::validateAndAccept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    
    if (!manager.getCars().empty()) {
        updateAddOptionsChecks(manager.getCars()[0]);
    }
    
    updatePriceInfo();
}

void MakeSaleDialog::onCarChanged() {
    size_t carIdx = carCombo->currentData().toULongLong();
    const auto& cars = manager.getCars();
    if (carIdx < cars.size()) {
        updateAddOptionsChecks(cars[carIdx]);
        updatePriceInfo();
    }
}

void MakeSaleDialog::updateAddOptionsChecks(const Car& car) {
    for (const auto& [name, checkbox] : optionCheckboxes) {
        bool hasOption = car.getOptions().count(name) > 0;
        checkbox->setChecked(hasOption);
    }
}

void MakeSaleDialog::updatePriceInfo() {
    selectedCarIndex = carCombo->currentData().toULongLong();
    selectedClientIndex = clientCombo->currentData().toULongLong();
    
    const auto& cars = manager.getCars();
    const auto& clients = manager.getClients();
    
    if (selectedCarIndex >= cars.size() || selectedClientIndex >= clients.size()) {
        return;
    }
    
    const Car& car = cars[selectedCarIndex];
    const Client& client = clients[selectedClientIndex];
    
    double basePrice = car.getTotalPrice();  // Includes car's options
    double optionsAdjustment = 0.0;
    
    for (const auto& [name, checkbox] : optionCheckboxes) {
        bool isOnCar = car.getOptions().count(name) > 0;
        bool isChecked = checkbox->isChecked();
        
        auto it = Car::getAvailableOptions().find(name);
        if (it == Car::getAvailableOptions().end()) continue;
        
        double optionPrice = it->second;
        
        if (isOnCar) {
            if (!isChecked) {
                optionsAdjustment -= optionPrice * 0.5;  // Refund for removing
            }
            // if checked, no adjustment (already included)
        } else {
            if (isChecked) {
                optionsAdjustment += optionPrice;  // Add for new option
            }
            // if not checked, no adjustment
        }
    }
    
    double originalPrice = basePrice + optionsAdjustment;
    double discount = manager.calculateDiscountForSale(client, car);
    double finalPrice = originalPrice * (1.0 - discount / 100.0);
    
    originalPriceLabel->setText(QString("$%1").arg(originalPrice, 0, 'f', 2));
    discountLabel->setText(QString("%1%").arg(discount, 0, 'f', 1));
    finalPriceLabel->setText(QString("$%1").arg(finalPrice, 0, 'f', 2));
    clientBalanceLabel->setText(QString("$%1").arg(client.getBalance(), 0, 'f', 2));
}

void MakeSaleDialog::validateAndAccept() {
    size_t carIdx = carCombo->currentData().toULongLong();
    size_t clientIdx = clientCombo->currentData().toULongLong();
    
    const auto& cars = manager.getCars();
    const auto& clients = manager.getClients();
    
    if (carIdx >= cars.size() || clientIdx >= clients.size()) {
        QMessageBox::warning(this, "Error", "Invalid selection!");
        return;
    }
    
    const Car& car = cars[carIdx];
    const Client& client = clients[clientIdx];
    
    if (car.isReserved() && car.getReservedBy() != client.getFullName()) {
        QMessageBox::warning(this, "Error", "This car is reserved by another client!");
        return;
    }
    
    if (car.getStock() <= 0) {
        QMessageBox::warning(this, "Error", "This car is out of stock!");
        return;
    }
    
    updatePriceInfo();
    if (double finalPrice = finalPriceLabel->text().remove('$').toDouble(); client.getBalance() < finalPrice) {
        QMessageBox::warning(this, "Error", "Insufficient client balance!");
        return;
    }
    
    accept();
}

void MakeSaleDialog::setSelectedCar(size_t index) {
    if (index < static_cast<size_t>(carCombo->count())) {
        carCombo->setCurrentIndex(static_cast<int>(index));
        onCarChanged();
    }
}

size_t MakeSaleDialog::getSelectedCarIndex() const {
    return selectedCarIndex;
}

size_t MakeSaleDialog::getSelectedClientIndex() const {
    return selectedClientIndex;
}

double MakeSaleDialog::getFinalPrice() const {
    return finalPriceLabel->text().remove('$').toDouble();
}

double MakeSaleDialog::getOriginalPrice() const {
    return originalPriceLabel->text().remove('$').toDouble();
}

Car MakeSaleDialog::getCarWithSelectedOptions() const {
    const auto& cars = manager.getCars();
    if (selectedCarIndex >= cars.size()) {
        return Car();
    }
    
    Car car = cars[selectedCarIndex];  // Create a copy
    
    // Clear existing options and apply selected ones
    const auto& currentOptions = car.getOptions();
    for (const auto& [optName, _] : currentOptions) {
        car.removeOption(optName);
    }
    
    // Add selected options
    const auto& availableOptions = Car::getAvailableOptions();
    for (const auto& [name, checkbox] : optionCheckboxes) {
        if (checkbox->isChecked()) {
            auto it = availableOptions.find(name);
            if (it != availableOptions.end()) {
                car.addOption(name, it->second);
            }
        }
    }
    
    return car;
}