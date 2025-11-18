#pragma once

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QTableView>
#include <QStandardItemModel>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QScrollArea>
#include <QGridLayout>
#include <QWidget>
#include <vector>
#include "dealership_manager.h"
#include "carcardwidget.h"

class SearchDialog : public QDialog {
    Q_OBJECT

private:
    DealershipManager& manager;
    
    QComboBox* searchTypeCombo;
    QComboBox* brandCombo;
    QLineEdit* modelEdit;
    QDoubleSpinBox* minPriceSpin;
    QDoubleSpinBox* maxPriceSpin;
    QComboBox* colorCombo;
    QSpinBox* minHpSpin;
    QSpinBox* maxHpSpin;
    QComboBox* transmissionCombo;
    
    QScrollArea* resultsScrollArea;
    QWidget* resultsScrollContent;
    QGridLayout* resultsGridLayout;
    std::vector<CarCardWidget*> resultCards;
    
    QPushButton* searchButton;

public:
    SearchDialog(DealershipManager& manager, QWidget* parent = nullptr);

private slots:
    void onSearchTypeChanged();
    void performSearch();
};