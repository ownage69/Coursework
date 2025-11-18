#include "searchdialog.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QScrollArea>
#include <QGridLayout>
#include <algorithm>
#include "carcardwidget.h"

SearchDialog::SearchDialog(DealershipManager& manager, QWidget* parent) 
    : QDialog(parent), manager(manager) {
    setWindowTitle("Search Cars");
    setModal(true);
    resize(1000, 700);
    
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
        "QPushButton { background-color: #2196f3; color: white; border: none; padding: 10px 16px; border-radius: 6px; }"
        "QPushButton:hover { background-color: #1976d2; }"
        "QPushButton:pressed { background-color: #1565c0; }"
    );
    
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    QFormLayout* formLayout = new QFormLayout;
    
    searchTypeCombo = new QComboBox;
    searchTypeCombo->addItems({"By Brand", "By Model", "By Price Range", "By Color", "By Horsepower Range", "By Transmission"});
    
    brandCombo = new QComboBox;
    brandCombo->addItems({"BMW", "Audi", "Toyota", "Mercedes", "Ford", "Volkswagen", 
                         "Nissan", "Honda", "Hyundai", "Kia", "Lexus", "Mazda", 
                         "Renault", "Skoda", "Volvo", "Peugeot", "Chevrolet", 
                         "Subaru", "Tesla"});
    
    modelEdit = new QLineEdit;
    
    minPriceSpin = new QDoubleSpinBox;
    minPriceSpin->setRange(0, 1000000);
    minPriceSpin->setDecimals(2);
    
    maxPriceSpin = new QDoubleSpinBox;
    maxPriceSpin->setRange(0, 1000000);
    maxPriceSpin->setDecimals(2);
    maxPriceSpin->setValue(100000);
    
    colorCombo = new QComboBox;
    colorCombo->addItems({"Black", "White", "Silver", "Gray", "Blue", "Red", "Green", "Yellow", "Orange", "Brown", "Purple"});
    
    minHpSpin = new QSpinBox;
    minHpSpin->setRange(0, 2000);
    
    maxHpSpin = new QSpinBox;
    maxHpSpin->setRange(0, 2000);
    maxHpSpin->setValue(1000);
    
    transmissionCombo = new QComboBox;
    transmissionCombo->addItems({"Automatic", "Manual"});
    
    formLayout->addRow("Search Type:", searchTypeCombo);
    formLayout->addRow("Brand:", brandCombo);
    formLayout->addRow("Model:", modelEdit);
    formLayout->addRow("Min Price:", minPriceSpin);
    formLayout->addRow("Max Price:", maxPriceSpin);
    formLayout->addRow("Color:", colorCombo);
    formLayout->addRow("Min Horsepower:", minHpSpin);
    formLayout->addRow("Max Horsepower:", maxHpSpin);
    formLayout->addRow("Transmission:", transmissionCombo);
    
    mainLayout->addLayout(formLayout);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    searchButton = new QPushButton("Search");
    QPushButton* closeButton = new QPushButton("Close");
    
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(closeButton);
    buttonLayout->addStretch();
    
    mainLayout->addLayout(buttonLayout);
    
    resultsScrollArea = new QScrollArea;
    resultsScrollArea->setWidgetResizable(true);
    resultsScrollArea->setStyleSheet("QScrollArea { border: 1px solid #e0e0e0; background-color: #f8f9fa; border-radius: 4px; }");
    
    resultsScrollContent = new QWidget;
    resultsGridLayout = new QGridLayout(resultsScrollContent);
    resultsGridLayout->setSpacing(20);
    resultsGridLayout->setContentsMargins(20, 20, 20, 20);
    
    resultsScrollArea->setWidget(resultsScrollContent);
    mainLayout->addWidget(resultsScrollArea);
    
    connect(searchTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SearchDialog::onSearchTypeChanged);
    connect(searchButton, &QPushButton::clicked, this, &SearchDialog::performSearch);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    
    onSearchTypeChanged();
}

void SearchDialog::onSearchTypeChanged() {
    brandCombo->setVisible(false);
    modelEdit->setVisible(false);
    minPriceSpin->setVisible(false);
    maxPriceSpin->setVisible(false);
    colorCombo->setVisible(false);
    minHpSpin->setVisible(false);
    maxHpSpin->setVisible(false);
    transmissionCombo->setVisible(false);
    
    int currentIndex = searchTypeCombo->currentIndex();
    switch (currentIndex) {
        case 0:
            brandCombo->setVisible(true);
            break;
        case 1:
            modelEdit->setVisible(true);
            break;
        case 2:
            minPriceSpin->setVisible(true);
            maxPriceSpin->setVisible(true);
            break;
        case 3:
            colorCombo->setVisible(true);
            break;
        case 4:
            minHpSpin->setVisible(true);
            maxHpSpin->setVisible(true);
            break;
        case 5:
            transmissionCombo->setVisible(true);
            break;
    }
}

void SearchDialog::performSearch() {
    for (auto* card : resultCards) {
        resultsGridLayout->removeWidget(card);
        delete card;
    }
    resultCards.clear();
    
    std::vector<Car> results;
    int searchType = searchTypeCombo->currentIndex();
    
    switch (searchType) {
        case 0:
            results = manager.searchCarsByBrand(brandCombo->currentText().toStdString());
            break;
        case 1:
            results = manager.searchCarsByModel(modelEdit->text().toStdString());
            break;
        case 2:
            results = manager.searchCarsByPriceRange(minPriceSpin->value(), maxPriceSpin->value());
            break;
        case 3:
            results = manager.searchCarsByColor(colorCombo->currentText().toStdString());
            break;
        case 4:
            results = manager.searchCarsByHorsepower(minHpSpin->value(), maxHpSpin->value());
            break;
        case 5:
            results = manager.searchCarsByTransmission(transmissionCombo->currentText().toStdString());
            break;
    }
    
    const auto& allCars = manager.getCars();
    const int columnsPerRow = 3;
    
    for (size_t i = 0; i < results.size(); ++i) {
        auto it = std::find_if(allCars.begin(), allCars.end(), 
            [&results, i](const Car& c) {
                return c.getVin() == results[i].getVin();
            });
        
        if (it != allCars.end()) {
            size_t cardIndex = std::distance(allCars.begin(), it);
            CarCardWidget* card = new CarCardWidget(results[i], cardIndex);
            
            int row = static_cast<int>(i) / columnsPerRow;
            int col = static_cast<int>(i) % columnsPerRow;
            resultsGridLayout->addWidget(card, row, col);
            
            resultCards.push_back(card);
        } else {
            size_t cardIndex = i;
            CarCardWidget* card = new CarCardWidget(results[i], cardIndex);
            
            int row = static_cast<int>(i) / columnsPerRow;
            int col = static_cast<int>(i) % columnsPerRow;
            resultsGridLayout->addWidget(card, row, col);
            
            resultCards.push_back(card);
        }
    }
    
    if (results.empty()) {
        QMessageBox::information(this, "Search Results", "No cars found matching the criteria.");
    }
}