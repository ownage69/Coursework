#include "addcardialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QMessageBox>
#include <QPushButton>
#include <QPixmap>
#include <QDebug>
#include <random>
#include <string>

std::string generateVIN() {
    std::string vin;
    std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd; // Using std::random_device directly for non-cryptographic VIN
    std::uniform_int_distribution dis(0, static_cast<int>(chars.size()) - 1);
    for (int i = 0; i < 17; ++i) {
        vin += chars[dis(rd)]; // Use rd directly instead of mt19937
    }
    return vin;
}

AddCarDialog::AddCarDialog(QWidget* parent) 
    : QDialog(parent)
    , brandCombo(new QComboBox(this))
    , modelCombo(new QComboBox(this))
    , yearSpin(new QSpinBox(this))
    , priceSpin(new QDoubleSpinBox(this))
    , colorCombo(new QComboBox(this))
    , horsepowerSpin(new QSpinBox(this))
    , transmissionCombo(new QComboBox(this))
    , stockSpin(new QSpinBox(this))
    , vinEdit(new QLineEdit(this))
    , optionsGroup(new QGroupBox("Optional Features", this))
    , optionsLayout(new QVBoxLayout(optionsGroup))
    , imagePreviewLabel(new QLabel(this))
    , totalPriceLabel(new QLabel("Final Price: <span style='color: #28a745;'>$0.00</span>", this))
    , buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this)) {
    setWindowTitle("Add Car");
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
        "QGroupBox { border: 2px solid #e0e0e0; border-radius: 5px; margin-top: 1ex; color: #333333; }"
        "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }"
        "QPushButton { background-color: #2196f3; color: white; border: none; padding: 10px 16px; border-radius: 6px; }"
        "QPushButton:hover { background-color: #1976d2; }"
        "QPushButton:pressed { background-color: #1565c0; }"
    );

    auto* mainLayout = new QVBoxLayout(this);
    
    auto* topLayout = new QHBoxLayout;
    
    auto* formLayout = new QFormLayout;

    brandCombo->addItems({"Toyota", "Honda", "Ford", "Chevrolet", "BMW", "Mercedes-Benz", "Audi", "Nissan", "Hyundai"});
    formLayout->addRow("Brand:", brandCombo);

    formLayout->addRow("Model:", modelCombo);

    yearSpin->setRange(1900, 2100);
    yearSpin->setValue(2023);
    formLayout->addRow("Year:", yearSpin);

    priceSpin->setRange(0, 1000000);
    priceSpin->setSingleStep(1000);
    formLayout->addRow("Price ($):", priceSpin);

    colorCombo->addItems({"White", "Black", "Silver", "Gray", "Blue", "Red", "Green", "Yellow", "Orange", "Purple"});
    formLayout->addRow("Color:", colorCombo);

    horsepowerSpin->setRange(50, 1000);
    horsepowerSpin->setValue(200);
    formLayout->addRow("Horsepower:", horsepowerSpin);

    transmissionCombo->addItems({"Manual", "Automatic", "CVT"});
    formLayout->addRow("Transmission:", transmissionCombo);

    stockSpin->setRange(1, 1000);
    stockSpin->setValue(1);
    formLayout->addRow("Stock:", stockSpin);

    vinEdit->setReadOnly(true);
    vinEdit->setText(QString::fromStdString(generateVIN()));
    formLayout->addRow("VIN:", vinEdit);
    
    topLayout->addLayout(formLayout);
    
    imagePreviewLabel->setFixedSize(300, 200);
    imagePreviewLabel->setAlignment(Qt::AlignCenter);
    imagePreviewLabel->setStyleSheet("border: 2px solid #004080; border-radius: 5px; background-color: #1e1e1e;");
    imagePreviewLabel->setScaledContents(true);
    imagePreviewLabel->setText("Car Preview");
    topLayout->addWidget(imagePreviewLabel);
    
    mainLayout->addLayout(topLayout);
    
    auto availableOptions = Car::getAvailableOptions();
    for (const auto& [optName, optPrice] : availableOptions) {
        auto* checkbox = new QCheckBox(QString("$%1 - %2").arg(optPrice).arg(QString::fromStdString(optName)));
        optionCheckboxes[optName] = checkbox;
        optionsLayout->addWidget(checkbox);
        connect(checkbox, &QCheckBox::toggled, this, &AddCarDialog::updateTotalPrice);
    }
    
    mainLayout->addWidget(optionsGroup);
    
    totalPriceLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
    mainLayout->addWidget(totalPriceLabel);
    
    mainLayout->addWidget(buttonBox);
    
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddCarDialog::validateAndAccept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(brandCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AddCarDialog::onBrandChanged);
    connect(modelCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AddCarDialog::onModelChanged);
    connect(priceSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &AddCarDialog::updateTotalPrice);
    
    onBrandChanged(0);
    updateImagePreview();
    updateTotalPrice();
}

QString AddCarDialog::getImagePathForBrandModel(const QString& brand, const QString& model) const {
    QString brandLower = brand.toLower();
    QString modelLower = model.toLower();
    
    modelLower.replace(" ", "_");
    modelLower.replace("-", "_");
    
    if (brandLower == "mercedes-benz") {
        brandLower = "mercedes_benz";
    }
    
    QString imagePath = QString(":/images/%1_%2.jpg").arg(brandLower).arg(modelLower);
    
    if (QPixmap testPixmap(imagePath); testPixmap.isNull()) {
        imagePath = QString(":/images/%1_%2.png").arg(brandLower).arg(modelLower);
        if (QPixmap testPixmap2(imagePath); testPixmap2.isNull()) {
            return ":/images/default_car.png";
        }
    }
    
    return imagePath;
}

void AddCarDialog::onBrandChanged([[maybe_unused]] int index) {
    modelCombo->clear();
    
    if (QString brand = brandCombo->currentText(); brand == "BMW") {
        modelCombo->addItems({"3 Series", "5 Series", "7 Series", "X3", "X5"});
    } else if (brand == "Mercedes-Benz") {
        modelCombo->addItems({"C-Class", "E-Class", "S-Class", "GLC", "GLE"});
    } else if (brand == "Audi") {
        modelCombo->addItems({"A3", "A4", "A6", "Q5", "Q7"});
    } else if (brand == "Toyota") {
        modelCombo->addItems({"Camry", "Corolla", "RAV4", "Highlander", "Prius"});
    } else if (brand == "Honda") {
        modelCombo->addItems({"Civic", "Accord", "CR-V", "Pilot", "Fit"});
    } else if (brand == "Ford") {
        modelCombo->addItems({"F-150", "Mustang", "Explorer", "Focus", "Escape"});
    } else if (brand == "Chevrolet") {
        modelCombo->addItems({"Silverado", "Malibu", "Equinox", "Tahoe", "Camaro"});
    } else if (brand == "Nissan") {
        modelCombo->addItems({"Altima", "Sentra", "Rogue", "Pathfinder", "Titan"});
    } else if (brand == "Hyundai") {
        modelCombo->addItems({"Sonata", "Elantra", "Tucson", "Santa Fe", "Kona"});
    }
    
    updateImagePreview();
}

void AddCarDialog::onModelChanged() {
    updateImagePreview();
}

void AddCarDialog::updateImagePreview() {
    QString brand = brandCombo->currentText();
    QString model = modelCombo->currentText();
    
    if (brand.isEmpty() || model.isEmpty()) {
        QPixmap defaultPixmap(300, 200);
        defaultPixmap.fill(QColor(30, 30, 30));
        imagePreviewLabel->setPixmap(defaultPixmap);
        return;
    }
    
    QString imagePath = getImagePathForBrandModel(brand, model);
    QPixmap pixmap(imagePath);
    
    if (pixmap.isNull()) {
        pixmap = QPixmap(300, 200);
        pixmap.fill(QColor(30, 30, 30));
    } else {
        pixmap = pixmap.scaled(300, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    
    imagePreviewLabel->setPixmap(pixmap);
}

void AddCarDialog::updateTotalPrice() {
    double total = priceSpin->value();
    for (const auto& [name, price] : Car::getAvailableOptions()) {
        if (optionCheckboxes[name]->isChecked()) {
            total += price;
        }
    }
    totalPriceLabel->setText(QString("Final Price: <span style='color: #28a745;'>$%1</span>").arg(total, 0, 'f', 2));
}

void AddCarDialog::validateAndAccept() {
    QString brand = brandCombo->currentText();
    QString model = modelCombo->currentText();
    int year = yearSpin->value();
    double price = priceSpin->value();
    QString color = colorCombo->currentText();
    int horsepower = horsepowerSpin->value();
    QString transmission = transmissionCombo->currentText();
    int stock = stockSpin->value();
    QString vin = vinEdit->text().trimmed();
    
    if (brand.isEmpty() || model.isEmpty() || vin.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "All fields must be filled!");
        return;
    }
    
    if (year < 1900 || year > 2100) {
        QMessageBox::warning(this, "Validation Error", "Invalid year!");
        return;
    }
    
    if (price <= 0) {
        QMessageBox::warning(this, "Validation Error", "Price must be positive!");
        return;
    }
    
    if (horsepower <= 0) {
        QMessageBox::warning(this, "Validation Error", "Horsepower must be positive!");
        return;
    }
    
    if (stock <= 0) {
        QMessageBox::warning(this, "Validation Error", "Stock must be positive!");
        return;
    }
    
    if (QRegularExpression vinRegex("[A-Z0-9]{17}"); !vinRegex.match(vin).hasMatch()) {
        QMessageBox::warning(this, "Validation Error", "VIN must be 17 alphanumeric characters!");
        return;
    }
    
    accept();
}

Car AddCarDialog::getCar() const {
    Car::CarSpec spec{
        brandCombo->currentText().toStdString(),
        modelCombo->currentText().toStdString(),
        yearSpin->value(),
        priceSpin->value(),
        colorCombo->currentText().toStdString(),
        horsepowerSpin->value(),
        transmissionCombo->currentText().toStdString(),
        stockSpin->value(),
        vinEdit->text().trimmed().toStdString()
    };
    Car car(spec);
    
    QString imagePath = getImagePathForBrandModel(brandCombo->currentText(), modelCombo->currentText());
    car.setImagePath(imagePath.toStdString());
    
    for (const auto& [name, price] : Car::getAvailableOptions()) {
        if (optionCheckboxes.at(name)->isChecked()) {
            car.addOption(name, price);
        }
    }
    
    return car;
}