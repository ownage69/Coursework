#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class AdminLoginDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    
    QDialogButtonBox* buttonBox;

public:
    AdminLoginDialog(QWidget* parent = nullptr);

private slots:
    void attemptLogin();
};