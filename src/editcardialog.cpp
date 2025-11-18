#include "editcardialog.h"
#include <QMessageBox>

EditCarDialog::EditCarDialog(const Car& car, QWidget* parent) : QDialog(parent), originalCar(car) {
    setWindowTitle("Edit Car");
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
        "QCheckBox { color: #333333; }"
        "QCheckBox::indicator { background-color: #ffffff; border: 1px solid #e0e0e0; }"
        "QCheckBox::indicator:checked { background-color: #2196f3; }"
        "QLabel { color: #333333; }"
        "QPushButton { background-color: #2196f3; color: white; border: none; padding: 10px 16px; border-radius: 6px; }"
        "QPushButton:hover { background-color: #1976d2; }"
        "QPushButton:pressed { background-color: #1565c0; }"
    );
    
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    QFormLayout* formLayout = new QFormLayout;
    
    brandCombo = new QComboBox;
    brandCombo->addItems({"BMW", "Audi", "Toyota", "Mercedes", "Ford", "Volkswagen", "Honda", "Tesla", "Chevrolet", "Hyundai"});
    brandCombo->setCurrentText(QString::fromStdString(car.getBrand()));
    
    modelCombo = new QComboBox;
    
    yearSpin = new QSpinBox;
    yearSpin->setRange(1900, 2100);
    yearSpin->setValue(car.getYear());
    
    priceSpin = new QDoubleSpinBox;
    priceSpin->setRange(0.01, 1000000);
    priceSpin->setDecimals(2);
    priceSpin->setValue(car.getPrice());
    
    colorCombo = new QComboBox;
    colorCombo->addItems({"Black", "White", "Silver", "Gray", "Blue", "Red", "Green", "Yellow", "Orange", "Brown", "Purple"});
    colorCombo->setCurrentText(QString::fromStdString(car.getColor()));
    
    horsepowerSpin = new QSpinBox;
    horsepowerSpin->setRange(1, 2000);
    horsepowerSpin->setValue(car.getHorsepower());
    
    transmissionCombo = new QComboBox;
    transmissionCombo->addItems({"Automatic", "Manual"});
    transmissionCombo->setCurrentText(QString::fromStdString(car.getTransmission()));
    
    formLayout->addRow("Brand:", brandCombo);
    formLayout->addRow("Model:", modelCombo);
    formLayout->addRow("Year:", yearSpin);
    formLayout->addRow("Price:", priceSpin);
    formLayout->addRow("Color:", colorCombo);
    formLayout->addRow("Horsepower:", horsepowerSpin);
    formLayout->addRow("Transmission:", transmissionCombo);
    
    mainLayout->addLayout(formLayout);
    
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    mainLayout->addWidget(buttonBox);
    
    connect(brandCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &EditCarDialog::onBrandChanged);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditCarDialog::validateAndAccept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    
    onBrandChanged();
}

Car EditCarDialog::getCar() const {
    Car updatedCar = originalCar;
    updatedCar.setBrand(brandCombo->currentText().toStdString());
    updatedCar.setModel(modelCombo->currentText().toStdString());
    updatedCar.setYear(yearSpin->value());
    updatedCar.setPrice(priceSpin->value());
    updatedCar.setColor(colorCombo->currentText().toStdString());
    updatedCar.setHorsepower(horsepowerSpin->value());
    updatedCar.setTransmission(transmissionCombo->currentText().toStdString());
    return updatedCar;
}

void EditCarDialog::onBrandChanged() {
    modelCombo->clear();
    std::string selectedBrand = brandCombo->currentText().toStdString();
    
    if (selectedBrand == "BMW") {
        modelCombo->addItems({"3 Series", "5 Series", "X5", "M3", "i8"});
    } else if (selectedBrand == "Audi") {
        modelCombo->addItems({"A4", "Q7", "RS6", "e-tron", "TT"});
    } else if (selectedBrand == "Toyota") {
        modelCombo->addItems({"Camry", "Corolla", "RAV4", "Prius", "Highlander"});
    } else if (selectedBrand == "Mercedes") {
        modelCombo->addItems({"C-Class", "E-Class", "S-Class", "GLE", "AMG GT"});
    } else if (selectedBrand == "Ford") {
        modelCombo->addItems({"Mustang", "F-150", "Focus", "Explorer", "Bronco"});
    } else if (selectedBrand == "Volkswagen") {
        modelCombo->addItems({"Golf", "Passat", "Tiguan", "Beetle", "ID.4"});
    } else if (selectedBrand == "Honda") {
        modelCombo->addItems({"Civic", "Accord", "CR-V", "Pilot", "Odyssey"});
    } else if (selectedBrand == "Tesla") {
        modelCombo->addItems({"Model 3", "Model Y", "Model S", "Cybertruck", "Model X"});
    } else if (selectedBrand == "Chevrolet") {
        modelCombo->addItems({"Silverado", "Camaro", "Tahoe", "Equinox", "Corvette"});
    } else if (selectedBrand == "Hyundai") {
        modelCombo->addItems({"Sonata", "Tucson", "Santa Fe", "Elantra", "Palisade"});
    }
    
    modelCombo->setCurrentText(QString::fromStdString(originalCar.getModel()));
}

void EditCarDialog::validateAndAccept() {
    if (brandCombo->currentText().isEmpty() || modelCombo->currentText().isEmpty() ||
        yearSpin->value() <= 0 || priceSpin->value() <= 0 || 
        colorCombo->currentText().isEmpty() || horsepowerSpin->value() <= 0 ||
        transmissionCombo->currentText().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "All fields must be filled with valid values!");
        return;
    }
    
    accept();
}