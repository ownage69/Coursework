#pragma once

#include <QDialog>
#include <QComboBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include "dealership_manager.h"

class ReservationDialog : public QDialog {
    Q_OBJECT

private:
    DealershipManager& manager;
    
    QComboBox* carCombo;
    QComboBox* clientCombo;
    
    QDialogButtonBox* buttonBox;
    
    size_t selectedCarIndex{0};
    size_t selectedClientIndex{0};

public:
    explicit ReservationDialog(DealershipManager& manager, QWidget* parent = nullptr);
    
    void setSelectedCar(size_t index);
    size_t getSelectedCarIndex() const;
    size_t getSelectedClientIndex() const;

private slots:
    void validateAndAccept();
};