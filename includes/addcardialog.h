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
#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>
#include "car.h"

class AddCarDialog : public QDialog {
    Q_OBJECT

private:
    QComboBox* brandCombo;
    QComboBox* modelCombo;
    QSpinBox* yearSpin;
    QDoubleSpinBox* priceSpin;
    QComboBox* colorCombo;
    QSpinBox* horsepowerSpin;
    QComboBox* transmissionCombo;
    QSpinBox* stockSpin;
    QLineEdit* vinEdit;
    
    QGroupBox* optionsGroup;
    QVBoxLayout* optionsLayout;
    std::map<std::string, QCheckBox*> optionCheckboxes;
    
    QLabel* imagePreviewLabel;
    QLabel* totalPriceLabel;
    
    QDialogButtonBox* buttonBox;
    
    QString getImagePathForBrandModel(const QString& brand, const QString& model) const;

public:
    AddCarDialog(QWidget* parent = nullptr);
    
    Car getCar() const;

private slots:
    void onBrandChanged(int index);
    void onModelChanged();
    void updateImagePreview();
    void updateTotalPrice();
    void validateAndAccept();
};