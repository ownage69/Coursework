#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "car.h"

class EditCarDialog : public QDialog {
    Q_OBJECT

private:
    Car originalCar;
    
    QComboBox* brandCombo;
    QComboBox* modelCombo;
    QSpinBox* yearSpin;
    QDoubleSpinBox* priceSpin;
    QComboBox* colorCombo;
    QSpinBox* horsepowerSpin;
    QComboBox* transmissionCombo;
    
    QDialogButtonBox* buttonBox;

public:
    EditCarDialog(const Car& car, QWidget* parent = nullptr);
    
    Car getCar() const;

private slots:
    void onBrandChanged();
    void validateAndAccept();
};