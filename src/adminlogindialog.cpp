#include "adminlogindialog.h"
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>

AdminLoginDialog::AdminLoginDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Administrator Login");
    setModal(true);
    setFixedSize(700, 350);

    setStyleSheet(
        "QDialog { background-color: #fff8e1; border: 3px solid #ff9800; border-radius: 12px; }"
        "QLabel { color: #333; font-size: 14px; }"
        "QLineEdit { padding: 10px; border: 2px solid #ff9800; border-radius: 6px; font-size: 14px; background-color: white; min-width: 280px; }"
        "QLineEdit:focus { border-color: #f57c00; background-color: #fffde7; }"
        "QPushButton { background-color: #ff9800; color: white; border: none; padding: 12px 24px; border-radius: 8px; font-size: 14px; font-weight: 500; min-width: 100px; }"
        "QPushButton:hover { background-color: #f57c00; transform: translateY(-1px); }"
        "QPushButton:pressed { background-color: #ef6c00; transform: translateY(0); }"
    );

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    auto* titleLabel = new QLabel("🔐 Administrator Access Required");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #e65100; margin-bottom: 5px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    auto* subtitleLabel = new QLabel("Please enter your administrator credentials:");
    subtitleLabel->setStyleSheet("font-size: 14px; color: #666; margin-bottom: 15px;");
    subtitleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(subtitleLabel);

    auto* formLayout = new QGridLayout;
    formLayout->setSpacing(12);
    formLayout->setColumnStretch(1, 1);

    auto* usernameLabel = new QLabel("Username:");
    usernameLabel->setStyleSheet("font-weight: 500; min-width: 120px;");
    usernameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    usernameEdit = new QLineEdit;
    usernameEdit->setPlaceholderText("Enter administrator username");
    usernameEdit->setMinimumWidth(280);

    auto* passwordLabel = new QLabel("Password:");
    passwordLabel->setStyleSheet("font-weight: 500; min-width: 120px;");
    passwordLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    passwordEdit = new QLineEdit;
    passwordEdit->setPlaceholderText("Enter administrator password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setMinimumWidth(280);

    formLayout->addWidget(usernameLabel, 0, 0);
    formLayout->addWidget(usernameEdit, 0, 1);
    formLayout->addWidget(passwordLabel, 1, 0);
    formLayout->addWidget(passwordEdit, 1, 1);

    mainLayout->addLayout(formLayout);

    mainLayout->addStretch();

    auto* buttonLayout = new QHBoxLayout;
    buttonLayout->setSpacing(15);

    auto* cancelButton = new QPushButton("Cancel");
    cancelButton->setStyleSheet("QPushButton { background-color: #757575; } QPushButton:hover { background-color: #616161; }");

    buttonBox = new QDialogButtonBox;
    auto* okButton = buttonBox->addButton("Login", QDialogButtonBox::AcceptRole);
    okButton->setDefault(true);

    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(okButton);

    mainLayout->addLayout(buttonLayout);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &AdminLoginDialog::attemptLogin);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    usernameEdit->setFocus();
}

void AdminLoginDialog::attemptLogin() {
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text().trimmed();

    if (username == "ownage" && password == "YfhenJ") {
        accept();
    } else {
        QMessageBox::warning(this, "Login Failed", 
                           "Invalid administrator credentials!\n\n"
                           "Please check your username and password.\n\n"
                           "Contact system administrator for credentials.");
        usernameEdit->selectAll();
        usernameEdit->setFocus();
    }
}