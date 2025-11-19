#include "addclientdialog.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QPushButton>

AddClientDialog::AddClientDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Add Client");
    setModal(true);
    
    auto* mainLayout = new QVBoxLayout(this);
    
    auto* formLayout = new QFormLayout;
    
    fullNameEdit = new QLineEdit;
    QRegularExpression nameRegExp("^[A-Za-z\\s\\-]+$");
    const QRegularExpressionValidator* nameValidator = new QRegularExpressionValidator(nameRegExp, this);
    fullNameEdit->setValidator(nameValidator);
    
    phoneEdit = new QLineEdit;
    QRegularExpression phoneRegExp("^\\+?\\d{10,15}$");
    const QRegularExpressionValidator* phoneValidator = new QRegularExpressionValidator(phoneRegExp, this);
    phoneEdit->setValidator(phoneValidator);
    
    balanceSpin = new QDoubleSpinBox;
    balanceSpin->setRange(0.01, 10000000);
    balanceSpin->setDecimals(2);
    
    formLayout->addRow("Full Name:", fullNameEdit);
    formLayout->addRow("Phone:", phoneEdit);
    formLayout->addRow("Balance:", balanceSpin);
    
    mainLayout->addLayout(formLayout);
    
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    if (auto* okButton = buttonBox->button(QDialogButtonBox::Ok); okButton) {
        okButton->setEnabled(false);
    }
    mainLayout->addWidget(buttonBox);
    
    connect(fullNameEdit, &QLineEdit::textChanged, this, &AddClientDialog::updateOkButton);
    connect(phoneEdit, &QLineEdit::textChanged, this, &AddClientDialog::updateOkButton);
    connect(balanceSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &AddClientDialog::updateOkButton);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddClientDialog::validateAndAccept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    setStyleSheet(
        "QDialog { background-color: #ffffff; color: #333333; font-family: 'Segoe UI', Arial, sans-serif; }"
        "QLineEdit { background-color: #ffffff; color: #333333; border: 1px solid #e0e0e0; padding: 8px; border-radius: 4px; }"
        "QLineEdit:focus { border-color: #2196f3; }"
        "QSpinBox, QDoubleSpinBox { background-color: #ffffff; color: #333333; border: 1px solid #e0e0e0; padding: 8px; border-radius: 4px; }"
        "QSpinBox::up-button, QDoubleSpinBox::up-button { background-color: #f5f5f5; border: none; }"
        "QSpinBox::down-button, QDoubleSpinBox::down-button { background-color: #f5f5f5; border: none; }"
        "QLabel { color: #333333; }"
        "QPushButton { background-color: #2196f3; color: white; border: none; padding: 10px 16px; border-radius: 6px; }"
        "QPushButton:hover { background-color: #1976d2; }"
        "QPushButton:pressed { background-color: #1565c0; }"
    );
}

Client AddClientDialog::getClient() const {
    return Client(fullNameEdit->text().toStdString(),
                  phoneEdit->text().toStdString(),
                  balanceSpin->value());
}

bool AddClientDialog::isValidFullName(const QString& name) const {
    QRegularExpression re("^[A-Za-z\\s\\-]+$");
    return !name.trimmed().isEmpty() && re.match(name).hasMatch();
}

bool AddClientDialog::isValidPhone(const QString& phone) const {
    QRegularExpression re("^\\+?\\d{10,15}$");
    return !phone.trimmed().isEmpty() && re.match(phone).hasMatch();
}

void AddClientDialog::validateAndAccept() {
    QString fullName = fullNameEdit->text().trimmed();
    QString phone = phoneEdit->text().trimmed();
    double balance = balanceSpin->value();
    
    if (!isValidFullName(fullName)) {
        QMessageBox::warning(this, "Validation Error", "Full name must contain only letters, spaces, and hyphens!");
        return;
    }
    
    if (!isValidPhone(phone)) {
        QMessageBox::warning(this, "Validation Error", "Phone must be 10-15 digits, optionally starting with +!");
        return;
    }
    
    if (balance <= 0) {
        QMessageBox::warning(this, "Validation Error", "Balance must be greater than 0!");
        return;
    }
    
    accept();
}

void AddClientDialog::updateOkButton() {
    QString fullName = fullNameEdit->text().trimmed();
    QString phone = phoneEdit->text().trimmed();
    double balance = balanceSpin->value();
    
    bool isValid = isValidFullName(fullName) && isValidPhone(phone) && balance > 0;
    if (auto* okButton = buttonBox->button(QDialogButtonBox::Ok); okButton) {
        okButton->setEnabled(isValid);
    }
}