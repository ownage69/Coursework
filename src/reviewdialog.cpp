#include "reviewdialog.h"
#include <QMessageBox>
#include <QLabel>

ReviewDialog::ReviewDialog(DealershipManager& manager, QWidget* parent) 
    : QDialog(parent), manager(manager), selectedCarIndex(0), ratingValue(1) {
    setWindowTitle("Add Review");
    setModal(true);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    QFormLayout* formLayout = new QFormLayout;
    
    carCombo = new QComboBox;
    
    const auto& cars = manager.getCars();
    
    if (cars.empty()) {
        QMessageBox::warning(this, "Error", "No cars available!");
        return;
    }
    
    for (size_t i = 0; i < cars.size(); ++i) {
        std::string carInfo = cars[i].getBrand() + " " + cars[i].getModel() + " (Rating: " + 
                             QString::number(cars[i].getAverageRating(), 'f', 1).toStdString() + ")";
        carCombo->addItem(QString::fromStdString(carInfo));
    }
    
    reviewEdit = new QTextEdit;
    reviewEdit->setMaximumHeight(100);
    
    ratingSpin = new QSpinBox;
    ratingSpin->setRange(1, 5);
    
    formLayout->addRow("Select Car:", carCombo);
    formLayout->addRow("Review:", reviewEdit);
    formLayout->addRow("Rating (1-5):", ratingSpin);
    
    mainLayout->addLayout(formLayout);
    
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    mainLayout->addWidget(buttonBox);
    
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ReviewDialog::validateAndAccept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

size_t ReviewDialog::getSelectedCarIndex() const {
    return selectedCarIndex;
}

std::string ReviewDialog::getReviewText() const {
    return reviewText;
}

int ReviewDialog::getRating() const {
    return ratingValue;
}

void ReviewDialog::validateAndAccept() {
    selectedCarIndex = carCombo->currentIndex();
    reviewText = reviewEdit->toPlainText().toStdString();
    ratingValue = ratingSpin->value();
    
    if (reviewText.empty()) {
        QMessageBox::warning(this, "Validation Error", "Review text cannot be empty!");
        return;
    }
    
    if (ratingValue < 1 || ratingValue > 5) {
        QMessageBox::warning(this, "Validation Error", "Rating must be between 1 and 5!");
        return;
    }
    
    accept();
}