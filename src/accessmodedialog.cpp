#include "accessmodedialog.h"
#include "adminlogindialog.h"
#include <QApplication>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QScrollArea>
#include <QTextDocument>

AccessModeDialog::AccessModeDialog(QWidget* parent) : QDialog(parent) {
    qDebug() << "AccessModeDialog constructor called";

    try {
        setWindowTitle("Car Dealership - Select Access Mode");
        setModal(true);
        setMinimumSize(650, 550);
        setMaximumSize(800, 700);

        setStyleSheet(
            "QDialog { background-color: #ffffff; border: 2px solid #e0e0e0; border-radius: 10px; }"
            "QLabel { color: #333; font-size: 14px; }"
            "QGroupBox { font-weight: bold; font-size: 16px; border: 2px solid #ddd; border-radius: 8px; margin-top: 10px; padding-top: 10px; }"
            "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 8px; }"
            "QPushButton { background-color: #4CAF50; color: white; border: none; padding: 12px 24px; border-radius: 6px; font-size: 14px; font-weight: 500; min-width: 160px; }"
            "QPushButton:hover { background-color: #45a049; }"
            "QPushButton#adminButton { background-color: #FF6F00; }"
            "QPushButton#adminButton:hover { background-color: #E65100; }"
            "QPushButton#standardButton { background-color: #1976D2; }"
            "QPushButton#standardButton:hover { background-color: #1565C0; }"
            "QPushButton#exitButton { background-color: #f44336; }"
            "QPushButton#exitButton:hover { background-color: #d32f2f; }"
        );

        auto* mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(20);
        mainLayout->setContentsMargins(30, 30, 30, 30);

        auto* titleLabel = new QLabel("🚗 Welcome to Car Dealership Management System");
        titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #2E7D32; margin-bottom: 10px;");
        titleLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(titleLabel);

        auto* subtitleLabel = new QLabel("Please select your preferred access mode:");
        subtitleLabel->setStyleSheet("font-size: 16px; color: #666; margin-bottom: 20px;");
        subtitleLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(subtitleLabel);

        auto* scrollArea = new QScrollArea;
        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setStyleSheet("QScrollArea { border: none; background-color: transparent; }");

        auto* scrollWidget = new QWidget;
        auto* scrollLayout = new QVBoxLayout(scrollWidget);
        scrollLayout->setSpacing(20);
        scrollLayout->setContentsMargins(10, 10, 10, 10);

        auto* adminGroup = new QGroupBox("Administrator Mode");
        adminGroup->setStyleSheet("QGroupBox { border-color: #FF6F00; } QGroupBox::title { color: #E65100; }");
        auto* adminLayout = new QVBoxLayout(adminGroup);
        adminLayout->setSpacing(15);

        auto* adminDesc = new QLabel(
            "<b>Full System Access</b><br><br>"
            "<b>✓</b> Add, edit, and delete cars, clients, and sales<br>"
            "<b>✓</b> Advanced management and reporting tools<br>"
            "<b>✓</b> Modify system data and settings<br>"
            "<b>✓</b> Access to all administrative functions<br><br>"
            "<i>⚠️ Requires administrator login credentials</i>"
        );
        adminDesc->setStyleSheet("color: #333; line-height: 1.6; padding: 5px;");
        adminDesc->setTextFormat(Qt::RichText);
        adminDesc->setWordWrap(true);
        adminDesc->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        adminLayout->addWidget(adminDesc);

        auto* adminButton = new QPushButton("Login as Administrator");
        adminButton->setObjectName("adminButton");
        adminLayout->addWidget(adminButton, 0, Qt::AlignCenter);

        scrollLayout->addWidget(adminGroup);

        auto* standardGroup = new QGroupBox("Standard Mode");
        standardGroup->setStyleSheet("QGroupBox { border-color: #1976D2; } QGroupBox::title { color: #1565C0; }");
        auto* standardLayout = new QVBoxLayout(standardGroup);
        standardLayout->setSpacing(15);

        auto* standardDesc = new QLabel(
            "<b>User Access</b><br><br>"
            "<b>✓</b> View available cars, clients, and sales<br>"
            "<b>✓</b> Make purchases and car reservations<br>"
            "<b>✓</b> Leave reviews and ratings<br>"
            "<b>✓</b> Standard user operations<br><br>"
            "<i>✅ No login required - immediate access</i>"
        );
        standardDesc->setStyleSheet("color: #333; line-height: 1.6; padding: 5px;");
        standardDesc->setTextFormat(Qt::RichText);
        standardDesc->setWordWrap(true);
        standardDesc->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        standardLayout->addWidget(standardDesc);

        auto* standardButton = new QPushButton("Continue in Standard Mode");
        standardButton->setObjectName("standardButton");
        standardLayout->addWidget(standardButton, 0, Qt::AlignCenter);

        scrollLayout->addWidget(standardGroup);

        scrollArea->setWidget(scrollWidget);
        mainLayout->addWidget(scrollArea);

        auto* buttonLayout = new QHBoxLayout;
        buttonLayout->addStretch();

        auto* exitButton = new QPushButton("Exit Application");
        exitButton->setObjectName("exitButton");
        exitButton->setMinimumWidth(140);
        buttonLayout->addWidget(exitButton);

        mainLayout->addLayout(buttonLayout);

        connect(adminButton, &QPushButton::clicked, this, &AccessModeDialog::selectAdminMode);
        connect(standardButton, &QPushButton::clicked, this, &AccessModeDialog::selectStandardMode);
        connect(exitButton, &QPushButton::clicked, this, &QDialog::reject);

        adjustSize();

        qDebug() << "AccessModeDialog initialization completed";

    } catch (const std::exception& e) {
        qCritical() << "Exception in AccessModeDialog constructor:" << e.what();
        throw;
    }
}

void AccessModeDialog::selectStandardMode() {
    qDebug() << "Standard mode selected";
    adminMode = false;
    accept();
}

void AccessModeDialog::selectAdminMode() {
    qDebug() << "Admin mode selected, opening login dialog";
    AdminLoginDialog loginDialog(this);
    if (loginDialog.exec() == QDialog::Accepted) {
        qDebug() << "Admin login successful";
        adminMode = true;
        accept();
    } else {
        qDebug() << "Admin login cancelled";
    }
}