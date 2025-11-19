#include "mainwindow.h"
#include <QApplication>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QScrollArea>
#include <QGridLayout>
#include <QCloseEvent>
#include <vector>
#include "addcardialog.h"
#include "addclientdialog.h"
#include "makesaledialog.h"
#include "searchdialog.h"
#include "reservationdialog.h"
#include "editcardialog.h"
#include "carcardwidget.h"
#include "salesreportdialog.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    qDebug() << "MainWindow constructor called";
    manager.loadData();
    setupUI();
    updateTables();
    qDebug() << "MainWindow setup completed";
}

MainWindow::~MainWindow() {
    qDebug() << "MainWindow destructor called";
}

void MainWindow::setupUI() {
    qDebug() << "setupUI: Setting window properties...";
    setWindowTitle("Car Dealership Management System");
    setMinimumSize(1200, 800);
    
    auto* centralWidget = new QWidget;
    setCentralWidget(centralWidget);
    
    auto* mainLayout = new QVBoxLayout(centralWidget);
    
    auto* titleWidget = new QWidget;
    titleWidget->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #f0f0f0, stop:1 #ffffff); border-bottom: 2px solid #e0e0e0; padding: 15px;");
    auto* titleLabel = new QLabel("Car Dealership Management System");
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2c3e50; font-family: 'Segoe UI', Arial, sans-serif;");
    auto* titleLayout = new QHBoxLayout(titleWidget);
    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch();
    inventoryLabel = new QLabel("Total Cars in Stock: 0 (0 unique models)");
    inventoryLabel->setStyleSheet("color: #555555; font-size: 14px; font-family: 'Segoe UI', Arial, sans-serif;");
    titleLayout->addWidget(inventoryLabel);
    
    mainLayout->addWidget(titleWidget);
    
    clientsTable = new QTableView;
    salesTable = new QTableView;
    
    setupCarsGrid();
    
    // Create wrapper widgets for tabs with buttons
    auto* carsTabWidget = new QWidget;
    auto* carsTabLayout = new QVBoxLayout(carsTabWidget);
    carsTabLayout->setContentsMargins(0, 0, 0, 0);
    carsTabLayout->setSpacing(0);
    
    auto* carsButtonLayout = new QHBoxLayout;
    carsButtonLayout->setContentsMargins(10, 10, 10, 10);
    carsButtonLayout->addStretch();
    addCarButton = new QPushButton("+ Add Car");
    addCarButton->setStyleSheet(
        "QPushButton { background-color: #4caf50; color: white; border: none; padding: 10px 20px; border-radius: 6px; font-size: 14px; font-weight: bold; font-family: 'Segoe UI', Arial, sans-serif; }"
        "QPushButton:hover { background-color: #45a049; }"
        "QPushButton:pressed { background-color: #3d8b40; }"
    );
    connect(addCarButton, &QPushButton::clicked, this, &MainWindow::addCar);
    carsButtonLayout->addWidget(addCarButton);
    carsTabLayout->addLayout(carsButtonLayout);
    carsTabLayout->addWidget(carsScrollArea);
    
    auto* clientsTabWidget = new QWidget;
    auto* clientsTabLayout = new QVBoxLayout(clientsTabWidget);
    clientsTabLayout->setContentsMargins(0, 0, 0, 0);
    clientsTabLayout->setSpacing(0);
    
    auto* clientsButtonLayout = new QHBoxLayout;
    clientsButtonLayout->setContentsMargins(10, 10, 10, 10);
    clientsButtonLayout->addStretch();
    addClientButton = new QPushButton("+ Add Client");
    addClientButton->setStyleSheet(
        "QPushButton { background-color: #4caf50; color: white; border: none; padding: 10px 20px; border-radius: 6px; font-size: 14px; font-weight: bold; font-family: 'Segoe UI', Arial, sans-serif; }"
        "QPushButton:hover { background-color: #45a049; }"
        "QPushButton:pressed { background-color: #3d8b40; }"
    );
    connect(addClientButton, &QPushButton::clicked, this, &MainWindow::addClient);
    clientsButtonLayout->addWidget(addClientButton);
    clientsTabLayout->addLayout(clientsButtonLayout);
    clientsTabLayout->addWidget(clientsTable);
    
    auto* salesTabWidget = new QWidget;
    auto* salesTabLayout = new QVBoxLayout(salesTabWidget);
    salesTabLayout->setContentsMargins(0, 0, 0, 0);
    salesTabLayout->setSpacing(0);
    
    auto* salesButtonLayout = new QHBoxLayout;
    salesButtonLayout->setContentsMargins(10, 10, 10, 10);
    salesButtonLayout->addStretch();
    auto* salesReportButton = new QPushButton("📊 Sales Report");
    salesReportButton->setStyleSheet(
        "QPushButton { background-color: #2196f3; color: white; border: none; padding: 10px 20px; border-radius: 6px; font-size: 14px; font-weight: bold; font-family: 'Segoe UI', Arial, sans-serif; }"
        "QPushButton:hover { background-color: #1976d2; }"
        "QPushButton:pressed { background-color: #1565c0; }"
    );
    connect(salesReportButton, &QPushButton::clicked, this, &MainWindow::showSalesReport);
    salesButtonLayout->addWidget(salesReportButton);
    salesTabLayout->addLayout(salesButtonLayout);
    salesTabLayout->addWidget(salesTable);
    
    auto* tabWidget = new QTabWidget;
    tabWidget->addTab(carsTabWidget, "🚗 Cars");
    tabWidget->addTab(clientsTabWidget, "👨🏻‍💼 Clients");
    tabWidget->addTab(salesTabWidget, "🏷️ Sales");
    
    mainLayout->addWidget(tabWidget);
    
    setupTables();
    
    setStyleSheet(
        "QMainWindow { background-color: #ffffff; color: #333333; font-family: 'Segoe UI', Arial, sans-serif; }"
        "QTableView { background-color: #ffffff; color: #333333; border: 1px solid #e0e0e0; gridline-color: #f0f0f0; }"
        "QTableView::item { background-color: #ffffff; color: #333333; padding: 8px; border: none; }"
        "QTableView::item:selected { background-color: #e3f2fd; color: #1976d2; }"
        "QTableView::item:alternate { background-color: #fafafa; }"
        "QHeaderView::section { background-color: #f5f5f5; color: #555555; padding: 12px 8px; border: none; border-bottom: 2px solid #2196f3; font-weight: bold; font-size: 13px; }"
        "QTabWidget::pane { border: 1px solid #e0e0e0; background-color: #ffffff; border-top: none; }"
        "QTabBar::tab { background-color: #f5f5f5; color: #666666; padding: 12px 24px; margin-right: 2px; border: 1px solid #e0e0e0; border-bottom: none; border-top-left-radius: 6px; border-top-right-radius: 6px; font-size: 14px; }"
        "QTabBar::tab:selected { background-color: #ffffff; color: #2196f3; border-bottom: 2px solid #2196f3; font-weight: bold; }"
        "QTabBar::tab:hover { background-color: #fafafa; color: #1976d2; }"
    );
}

void MainWindow::setupCarsGrid() {
    carsScrollArea = new QScrollArea;
    carsScrollArea->setWidgetResizable(true);
    carsScrollArea->setStyleSheet("QScrollArea { border: none; background-color: #f8f9fa; } QScrollBar:vertical { background: #f0f0f0; width: 12px; border: none; } QScrollBar::handle:vertical { background: #c0c0c0; border-radius: 6px; min-height: 20px; } QScrollBar::handle:vertical:hover { background: #a0a0a0; }");
    
    carsScrollContent = new QWidget;
    carsGridLayout = new QGridLayout(carsScrollContent);
    carsGridLayout->setSpacing(20);
    carsGridLayout->setContentsMargins(20, 20, 20, 20);
    
    carsScrollArea->setWidget(carsScrollContent);
}

void MainWindow::setupTables() {
    qDebug() << "setupTables: Creating table models...";
    
    clientsModel = new QStandardItemModel;
    clientsModel->setHorizontalHeaderLabels({"Full Name", "Phone", "Balance"});
    clientsTable->setModel(clientsModel);
    clientsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    clientsTable->verticalHeader()->setDefaultSectionSize(50);
    clientsTable->setAlternatingRowColors(true);
    clientsTable->setSortingEnabled(true);
    clientsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    clientsTable->sortByColumn(0, Qt::AscendingOrder);
    
    salesModel = new QStandardItemModel;
    salesModel->setHorizontalHeaderLabels({"Date", "Car", "Client", "Original Price", "Discount %", "Final Price", "Options"});
    salesTable->setModel(salesModel);
    salesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    salesTable->verticalHeader()->setDefaultSectionSize(50);
    salesTable->setAlternatingRowColors(true);
    salesTable->setSortingEnabled(true);
    salesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    salesTable->sortByColumn(0, Qt::DescendingOrder);
}


void MainWindow::populateCarsGrid() {
    qDebug() << "populateCarsGrid: Clearing existing cards...";
    
    for (auto* card : carCards) {
        carsGridLayout->removeWidget(card);
        delete card;
    }
    carCards.clear();
    
    qDebug() << "populateCarsGrid: Getting cars data...";
    const auto& cars = manager.getCars();
    
    qDebug() << "populateCarsGrid: Populating" << cars.size() << "cars...";
    
    const int columnsPerRow = 3;
    for (size_t i = 0; i < cars.size(); ++i) {
        auto* card = new CarCardWidget(cars[i], i);
        connect(card, &CarCardWidget::editRequested, this, &MainWindow::editCar);
        connect(card, &CarCardWidget::deleteRequested, this, &MainWindow::deleteCar);
        connect(card, &CarCardWidget::sellRequested, this, &MainWindow::makeSaleForCar);
        connect(card, &CarCardWidget::reserveRequested, this, &MainWindow::reserveCarForCard);
        
        int row = static_cast<int>(i) / columnsPerRow;
        int col = static_cast<int>(i) % columnsPerRow;
        carsGridLayout->addWidget(card, row, col);
        
        carCards.push_back(card);
    }
    
    qDebug() << "populateCarsGrid completed";
}

void MainWindow::populateClientsTable() {
    qDebug() << "populateClientsTable: Clearing existing data...";
    clientsModel->removeRows(0, clientsModel->rowCount());
    
    qDebug() << "populateClientsTable: Getting clients data...";
    const auto& clients = manager.getClients();
    
    qDebug() << "populateClientsTable: Populating" << clients.size() << "clients...";
    for (const auto& client : clients) {
        QList<QStandardItem*> row;
        auto* c1 = new QStandardItem(QString::fromStdString(client.getFullName()));
        auto* c2 = new QStandardItem(QString::fromStdString(client.getPhone()));
        auto* c3 = new QStandardItem("$" + QString::number(client.getBalance(), 'f', 2));
        row << c1;
        row << c2;
        row << c3;
        clientsModel->appendRow(row);
    }
    qDebug() << "populateClientsTable completed";
}

void MainWindow::populateSalesTable() {
    qDebug() << "populateSalesTable: Clearing existing data...";
    salesModel->removeRows(0, salesModel->rowCount());
    
    qDebug() << "populateSalesTable: Getting sales data...";
    const auto& sales = manager.getSales();
    
    qDebug() << "populateSalesTable: Populating" << sales.size() << "sales...";
    for (const auto& sale : sales) {
        QList<QStandardItem*> row;
        std::string carInfo = sale.getCar().getBrand() + " " + sale.getCar().getModel() + " (" + sale.getCar().getVin() + ")";
        std::string clientInfo = sale.getClient().getFullName();
        
        // Build options string
        std::string optionsStr = "";
        {
            // Copy to avoid dangling reference to temporary returned by getCar()
            auto options = sale.getCar().getOptions();
            if (!options.empty()) {
                std::vector<std::string> optionNames;
                optionNames.reserve(options.size());
                for (const auto& [name, price] : options) {
                    optionNames.push_back(name);
                }
                optionsStr = "[" + optionNames[0];
                for (size_t j = 1; j < optionNames.size(); ++j) {
                    optionsStr += ", " + optionNames[j];
                }
                optionsStr += "]";
            } else {
                optionsStr = "None";
            }
        }
        
        auto* s1 = new QStandardItem(QString::fromStdString(sale.getDate()));
        auto* s2 = new QStandardItem(QString::fromStdString(carInfo));
        auto* s3 = new QStandardItem(QString::fromStdString(clientInfo));
        auto* s4 = new QStandardItem("$" + QString::number(sale.getOriginalPrice(), 'f', 2));
        auto* s5 = new QStandardItem(QString("%1%").arg(sale.getDiscountPercentage(), 0, 'f', 1));
        auto* s6 = new QStandardItem("$" + QString::number(sale.getFinalPrice(), 'f', 2));
        auto* s7 = new QStandardItem(QString::fromStdString(optionsStr));
        row << s1;
        row << s2;
        row << s3;
        row << s4;
        row << s5;
        row << s6;
        row << s7;
        salesModel->appendRow(row);
    }
    qDebug() << "populateSalesTable completed";
}

void MainWindow::updateTables() {
    qDebug() << "updateTables: Starting table updates...";
    populateCarsGrid();
    populateClientsTable();
    populateSalesTable();
    updateInventoryLabel();
    qDebug() << "updateTables completed";
}

void MainWindow::updateInventoryLabel() {
    int totalStock = manager.getTotalCarsInStock();
    int uniqueModels = manager.getTotalUniqueModels();
    inventoryLabel->setText(QString("Total Cars in Stock: %1 (%2 unique models)").arg(totalStock).arg(uniqueModels));
}

void MainWindow::addCar() {
    AddCarDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Car newCar = dialog.getCar();
        if (manager.addCar(newCar)) {
            updateTables();
            QMessageBox::information(this, "Success", "Car added successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to add car!");
        }
    }
}

void MainWindow::addClient() {
    AddClientDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Client newClient = dialog.getClient();
        if (manager.addClient(newClient)) {
            updateTables();
            QMessageBox::information(this, "Success", "Client added successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to add client!");
        }
    }
}

void MainWindow::makeSale() {
    MakeSaleDialog dialog(manager, this);
    if (dialog.exec() == QDialog::Accepted) {
        size_t carIndex = dialog.getSelectedCarIndex();
        size_t clientIndex = dialog.getSelectedClientIndex();

        double originalPrice = dialog.getOriginalPrice();
        double finalPrice = dialog.getFinalPrice();
        Car carWithOptions = dialog.getCarWithSelectedOptions();
        double discount = manager.calculateDiscountForSale(manager.getClients()[clientIndex], carWithOptions);

        if (manager.makeSaleWithCar(carWithOptions, carIndex, clientIndex, originalPrice, finalPrice, discount)) {
            updateTables();
            QMessageBox::information(this, "Success", "Sale completed successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Sale failed! Insufficient balance, no stock, or car is reserved.");
        }
    }
}

void MainWindow::makeSaleForCar(int index) {
    if (const auto& cars = manager.getCars(); index >= static_cast<int>(cars.size())) {
        QMessageBox::warning(this, "Error", "Invalid car selection.");
        return;
    }
    
    MakeSaleDialog dialog(manager, this);
    dialog.setSelectedCar(index);
    
    if (dialog.exec() == QDialog::Accepted) {
        size_t carIndex = dialog.getSelectedCarIndex();
        size_t clientIndex = dialog.getSelectedClientIndex();

        double originalPrice = dialog.getOriginalPrice();
        double finalPrice = dialog.getFinalPrice();
        Car carWithOptions = dialog.getCarWithSelectedOptions();
        double discount = manager.calculateDiscountForSale(manager.getClients()[clientIndex], carWithOptions);

        if (manager.makeSaleWithCar(carWithOptions, carIndex, clientIndex, originalPrice, finalPrice, discount)) {
            updateTables();
            QMessageBox::information(this, "Success", "Sale completed successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Sale failed! Insufficient balance, no stock, or car is reserved.");
        }
    }
}

void MainWindow::searchCars() {
    SearchDialog dialog(manager, this);
    dialog.exec();
}

void MainWindow::reserveCar() {
    ReservationDialog dialog(manager, this);
    if (dialog.exec() == QDialog::Accepted) {
        size_t carIndex = dialog.getSelectedCarIndex();
        size_t clientIndex = dialog.getSelectedClientIndex();

        if (manager.reserveCar(carIndex, clientIndex)) {
            updateTables();
            QMessageBox::information(this, "Success", "Car reserved successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to reserve car!");
        }
    }
}

void MainWindow::reserveCarForCard(int index) {
    if (const auto& cars = manager.getCars(); index >= static_cast<int>(cars.size())) {
        QMessageBox::warning(this, "Error", "Invalid car selection.");
        return;
    }
    
    ReservationDialog dialog(manager, this);
    dialog.setSelectedCar(index);
    
    if (dialog.exec() == QDialog::Accepted) {
        size_t carIndex = dialog.getSelectedCarIndex();
        size_t clientIndex = dialog.getSelectedClientIndex();

        if (manager.reserveCar(carIndex, clientIndex)) {
            updateTables();
            QMessageBox::information(this, "Success", "Car reserved successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to reserve car!");
        }
    }
}

void MainWindow::editCar(int index) {
    const auto& cars = manager.getCars();
    if (index >= static_cast<int>(cars.size())) {
        QMessageBox::warning(this, "Error", "Invalid car selection.");
        return;
    }
    Car selectedCar = cars[index];
    EditCarDialog dialog(selectedCar, this);
    if (dialog.exec() == QDialog::Accepted) {
        Car newCar = dialog.getCar();
        if (manager.editCar(index, newCar)) {
            updateTables();
            QMessageBox::information(this, "Success", "Car edited successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to edit car!");
        }
    }
}

void MainWindow::deleteCar(int index) {
    if (manager.deleteCar(index)) {
        updateTables();
        QMessageBox::information(this, "Success", "Car deleted successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete car!");
    }
}

void MainWindow::deleteClient() {
    QModelIndex index = clientsTable->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Error", "Please select a client to delete.");
        return;
    }
    int row = index.row();
    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this client?") == QMessageBox::Yes) {
        if (manager.deleteClient(row)) {
            updateTables();
            QMessageBox::information(this, "Success", "Client deleted successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete client!");
        }
    }
}

void MainWindow::deleteSale() {
    QModelIndex index = salesTable->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Error", "Please select a sale to delete.");
        return;
    }
    int row = index.row();
    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this sale?") == QMessageBox::Yes) {
        if (manager.deleteSale(row)) {
            updateTables();
            QMessageBox::information(this, "Success", "Sale deleted successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete sale!");
        }
    }
}

void MainWindow::showSalesReport() {
    SalesReportDialog dialog(&manager, this);
    dialog.exec();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    manager.saveData();
    event->accept();
}