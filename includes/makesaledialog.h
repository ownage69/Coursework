#pragma once

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QHBoxLayout>
#include "dealership_manager.h"

class MakeSaleDialog : public QDialog {
    Q_OBJECT

private:
    DealershipManager& manager;
    
    QComboBox* carCombo;
    QComboBox* clientCombo;
    
    QLabel* originalPriceLabel;
    QLabel* discountLabel;
    QLabel* finalPriceLabel;
    QLabel* clientBalanceLabel;
    
    QGroupBox* optionsGroup;
    std::map<std::string, QCheckBox*> optionCheckboxes;
    
    QDialogButtonBox* buttonBox;
    
    size_t selectedCarIndex;
    size_t selectedClientIndex;

    void updateAddOptionsChecks(const Car& car);

public:
    MakeSaleDialog(DealershipManager& manager, QWidget* parent = nullptr);
    
    void setSelectedCar(size_t index);
    size_t getSelectedCarIndex() const;
    size_t getSelectedClientIndex() const;
    double getFinalPrice() const;
    double getOriginalPrice() const;
    Car getCarWithSelectedOptions() const;

private slots:
    void updatePriceInfo();
    void validateAndAccept();
    void onCarChanged();
};