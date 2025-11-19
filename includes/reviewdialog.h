#pragma once

#include <QDialog>
#include <QComboBox>
#include <QTextEdit>
#include <QSpinBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include "dealership_manager.h"

class ReviewDialog : public QDialog {
    Q_OBJECT

private:
    DealershipManager& manager;
    
    QComboBox* carCombo;
    QTextEdit* reviewEdit;
    QSpinBox* ratingSpin;
    
    QDialogButtonBox* buttonBox;
    
    size_t selectedCarIndex;
    std::string reviewText;
    int ratingValue;

public:
    explicit ReviewDialog(DealershipManager& manager, QWidget* parent = nullptr);
    
    size_t getSelectedCarIndex() const;
    std::string getReviewText() const;
    int getRating() const;

private slots:
    void validateAndAccept();
};