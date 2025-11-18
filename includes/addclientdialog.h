#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QPushButton>
#include "client.h"

class AddClientDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit* fullNameEdit;
    QLineEdit* phoneEdit;
    QDoubleSpinBox* balanceSpin;
    
    QDialogButtonBox* buttonBox;

public:
    AddClientDialog(QWidget* parent = nullptr);
    
    Client getClient() const;

private slots:
    void validateAndAccept();
    void updateOkButton();

private:
    bool isValidFullName(const QString& name) const;
    bool isValidPhone(const QString& phone) const;
};