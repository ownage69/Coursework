#pragma once

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QToolBar>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QDebug>
#include <QHeaderView>
#include <QGridLayout>
#include <QScrollArea>
#include <QWidget>
#include <QCloseEvent>
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
    
    QToolBar* toolBar;
    QToolButton* operationsButton;
    QLabel* inventoryLabel;
    
    PriceDelegate* priceDelegate;
    
    void setupUI();
    void setupTables();
    void setupCarsGrid();
    void setupToolBar();
    QMenu* createOperationsMenu();
    
    void populateCarsGrid();
    void populateClientsTable();
    void populateSalesTable();
    void updateTables();
    void updateInventoryLabel();

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

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

protected:
    void closeEvent(QCloseEvent* event) override;
};