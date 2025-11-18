#include "logindialog.h"
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>

LoginDialog::LoginDialog(QWidget* parent) : QDialog(parent), adminMode(false) {
    setWindowTitle("Car Dealership - Access Mode");
    setModal(true);
    setFixedSize(400, 250);
    
    setStyleSheet(
        "QDialog { background-color: #f5f5f5; }"
        "QLabel { color: #333; font-size: 14px; }"
        "QLineEdit { padding: 8px; border: 2px solid #ccc; border-radius: 4px; font-size: 14px; }"
        "QLineEdit:focus { border-color: #4CAF50; }"
        "QPushButton { background-color: #4CAF50; color: white; border: none; padding: 10px 20px; border-radius: 4px; font-size: 14px; min-width: 80px; }"
        "QPushButton:hover { background-color: #45a049; }"
        "QPushButton#skipButton { background-color: #2196F3; }"
        "QPushButton#skipButton:hover { background-color: #1976D2; }"
    );
    
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    QLabel* titleLabel = new QLabel("Welcome to Car Dealership Management System");
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2E7D32; text-align: center;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    QLabel* subtitleLabel = new QLabel("Please select your access mode:");
    subtitleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(subtitleLabel);
    
    QVBoxLayout* modeLayout = new QVBoxLayout;
    
    QLabel* adminLabel = new QLabel("Administrator Mode");
    adminLabel->setStyleSheet("font-weight: bold; color: #D32F2F;");
    modeLayout->addWidget(adminLabel);
    
    QLabel* adminDesc = new QLabel("• Full access to all features\n• Add/Edit/Delete cars, clients, and sales\n• Advanced management tools");
    adminDesc->setStyleSheet("color: #666; margin-left: 10px;");
    modeLayout->addWidget(adminDesc);
    
    QFormLayout* formLayout = new QFormLayout;
    formLayout->setSpacing(10);
    
    usernameEdit = new QLineEdit;
    usernameEdit->setPlaceholderText("Enter username");
    passwordEdit = new QLineEdit;
    passwordEdit->setPlaceholderText("Enter password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    
    formLayout->addRow("Username:", usernameEdit);
    formLayout->addRow("Password:", passwordEdit);
    
    modeLayout->addLayout(formLayout);
    
    QLabel* userLabel = new QLabel("Standard Mode");
    userLabel->setStyleSheet("font-weight: bold; color: #1976D2; margin-top: 15px;");
    modeLayout->addWidget(userLabel);
    
    QLabel* userDesc = new QLabel("• View cars, clients, and sales\n• Make purchases and reservations\n• Leave reviews\n• Limited to read-only operations");
    userDesc->setStyleSheet("color: #666; margin-left: 10px;");
    modeLayout->addWidget(userDesc);
    
    mainLayout->addLayout(modeLayout);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    
    QPushButton* skipButton = new QPushButton("Use Standard Mode");
    skipButton->setObjectName("skipButton");
    buttonLayout->addWidget(skipButton);
    
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->button(QDialogButtonBox::Ok)->setText("Login as Admin");
    buttonLayout->addWidget(buttonBox);
    
    mainLayout->addLayout(buttonLayout);
    
    connect(buttonBox, &QDialogButtonBox::accepted, this, &LoginDialog::attemptLogin);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(skipButton, &QPushButton::clicked, this, &LoginDialog::skipLogin);
}

void LoginDialog::attemptLogin() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    
    if (username == "admin" && password == "admin") {
        adminMode = true;
        accept();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password!\n\nHint: Use 'admin' for both username and password.");
    }
}

void LoginDialog::skipLogin() {
    adminMode = false;
    accept();
}