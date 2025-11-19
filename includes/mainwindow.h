#pragma once

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QHeaderView>
#include <QGridLayout>
#include <QScrollArea>
#include <QWidget>
#include <QCloseEvent>
#include <QTabWidget>
#include <vector>
#include "dealership_manager.h"
#include "addcardialog.h"
#include "addclientdialog.h"
#include "makesaledialog.h"
#include "searchdialog.h"
#include "carcardwidget.h"

class PriceDelegate;

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    DealershipManager manager;
    
    QTableView* clientsTable;
    QTableView* salesTable;
    QStandardItemModel* clientsModel;
    QStandardItemModel* salesModel;
    
    QWidget* carsWidget;
    QScrollArea* carsScrollArea;
    QWidget* carsScrollContent;
    QGridLayout* carsGridLayout;
    std::vector<CarCardWidget*> carCards;
    
    QLabel* inventoryLabel;
    QPushButton* addCarButton;
    QPushButton* addClientButton;
    
    PriceDelegate* priceDelegate;
    
    void setupUI();
    void setupTables();
    void setupCarsGrid();
    
    void populateCarsGrid();
    void populateClientsTable();
    void populateSalesTable();
    void updateTables();
    void updateInventoryLabel();

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void addCar();
    void addClient();
    void makeSale();
    void makeSaleForCar(int index);
    void searchCars();
    void reserveCar();
    void reserveCarForCard(int index);
    void editCar(int index);
    void deleteCar(int index);
    void deleteClient();
    void deleteSale();
    void showSalesReport();

protected:
    void closeEvent(QCloseEvent* event) override;
};