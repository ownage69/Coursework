#include "carcardwidget.h"
#include <QPixmap>
#include <QMessageBox>
#include <QFileInfo>
#include <QPainter>
#include <QFont>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QIcon>
#include <QStyle>
#include <algorithm>

QString CarCardWidget::getImagePathForCar(const Car& car) const {
    if (QString savedPath = QString::fromStdString(car.getImagePath()); !savedPath.isEmpty()) {
        if (QPixmap testPixmap(savedPath); !testPixmap.isNull()) {
            return savedPath;
        }
    }
    
    QString brand = QString::fromStdString(car.getBrand()).toLower();
    QString model = QString::fromStdString(car.getModel()).toLower();
    
    model.replace(" ", "_");
    model.replace("-", "_");
    
    if (brand == "mercedes-benz") {
        brand = "mercedes_benz";
    }
    
    if (model == "gle") {
        model = "gle";
    } else if (model == "glc") {
        model = "glc";
    }
    
    if (brand == "ford" && (model.contains("f-150") || model == "f_150")) {
        model = "f_150";
    }
    
    if (brand == "honda" && model.contains("cr-v")) {
        model = "cr_v";
    }
    
    if (brand == "hyundai" && model.contains("santa-fe")) {
        model = "santa_fe";
    }
    
    QString imagePath = QString(":/images/%1_%2.jpg").arg(brand).arg(model);
    
    if (QPixmap testPixmap(imagePath); !testPixmap.isNull()) {
        return imagePath;
    }
    
    imagePath = QString(":/images/%1_%2.png").arg(brand).arg(model);
    if (QPixmap testPixmap2(imagePath); !testPixmap2.isNull()) {
        return imagePath;
    }
    
    return ":/images/default_car.png";
}

CarCardWidget::CarCardWidget(const Car& car, size_t index, QWidget* parent) 
    : QWidget(parent), car(car), carIndex(index) {
    
    setFixedSize(320, 450);
    setStyleSheet(
        "QWidget { background-color: white; border-radius: 10px; border: 1px solid #e0e0e0; }"
        "QLabel { color: #333333; font-family: 'Segoe UI', Arial, sans-serif; }"
    );
    setAttribute(Qt::WA_TranslucentBackground, false);
    
    auto* shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(10);
    shadow->setXOffset(0);
    shadow->setYOffset(2);
    shadow->setColor(QColor(0, 0, 0, 30));
    setGraphicsEffect(shadow);
    
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(8);
    
    auto* headerLayout = new QHBoxLayout;
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(4);
    headerLayout->addStretch();
    
    QIcon editIcon;
    if (QPixmap editPixmap(":/icons/pencil.png"); !editPixmap.isNull()) {
        editIcon = QIcon(editPixmap);
    } else {
        editIcon = QIcon::fromTheme("document-edit", QIcon::fromTheme("edit"));
    }
    
    editButton = new QPushButton;
    editButton->setIcon(editIcon);
    editButton->setFixedSize(20, 20);
    editButton->setIconSize(QSize(16, 16));
    editButton->setToolTip("Edit Car");
    editButton->setCursor(Qt::PointingHandCursor);
    editButton->setStyleSheet(
        "QPushButton { border: none; background-color: transparent; padding: 2px; }"
        "QPushButton:hover { background-color: #e3f2fd; border-radius: 10px; }"
        "QPushButton:pressed { background-color: #bbdefb; border-radius: 10px; }"
    );
    connect(editButton, &QPushButton::clicked, this, &CarCardWidget::onEditClicked);
    headerLayout->addWidget(editButton);
    
    QIcon deleteIcon;
    if (QPixmap deletePixmap(":/icons/trash.png"); !deletePixmap.isNull()) {
        deleteIcon = QIcon(deletePixmap);
    } else {
        deleteIcon = QIcon::fromTheme("edit-delete", QIcon::fromTheme("trash-empty"));
    }
    
    deleteButton = new QPushButton;
    deleteButton->setIcon(deleteIcon);
    deleteButton->setFixedSize(20, 20);
    deleteButton->setIconSize(QSize(16, 16));
    deleteButton->setToolTip("Delete Car");
    deleteButton->setCursor(Qt::PointingHandCursor);
    deleteButton->setStyleSheet(
        "QPushButton { border: none; background-color: transparent; padding: 2px; }"
        "QPushButton:hover { background-color: #ffebee; border-radius: 10px; }"
        "QPushButton:pressed { background-color: #ffcdd2; border-radius: 10px; }"
    );
    connect(deleteButton, &QPushButton::clicked, this, &CarCardWidget::onDeleteClicked);
    headerLayout->addWidget(deleteButton);
    
    mainLayout->addLayout(headerLayout);
    
    imageLabel = new QLabel;
    imageLabel->setFixedSize(300, 200);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet("border: 1px solid #e0e0e0; border-radius: 8px; background-color: #f5f5f5;");
    imageLabel->setScaledContents(false);
    
    QString imagePath = getImagePathForCar(car);
    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        pixmap = QPixmap(300, 200);
        pixmap.fill(QColor(240, 240, 240));
        QPainter painter(&pixmap);
        painter.setPen(QColor(180, 180, 180));
        painter.setFont(QFont("Arial", 14));
        painter.drawText(pixmap.rect(), Qt::AlignCenter, "No Image");
    } else {
        pixmap = pixmap.scaled(300, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    imageLabel->setPixmap(pixmap);
    mainLayout->addWidget(imageLabel);
    
    brandModelLabel = new QLabel(QString("%1 %2").arg(QString::fromStdString(car.getBrand())).arg(QString::fromStdString(car.getModel())));
    brandModelLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; font-family: 'Segoe UI', Arial, sans-serif;");
    mainLayout->addWidget(brandModelLabel);
    
    yearEngineLabel = new QLabel(QString("%1, %2 HP").arg(car.getYear()).arg(car.getHorsepower()));
    yearEngineLabel->setStyleSheet("font-size: 14px; color: #666666; font-family: 'Segoe UI', Arial, sans-serif;");
    mainLayout->addWidget(yearEngineLabel);
    
    priceLabel = new QLabel(QString("$%1").arg(car.getTotalPrice(), 0, 'f', 2));
    priceLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2196f3; font-family: 'Segoe UI', Arial, sans-serif;");
    mainLayout->addWidget(priceLabel);
    
    mainLayout->addStretch();
    
    reserveButton = new QPushButton("Reserve Car");
    reserveButton->setFixedHeight(40);
    if (car.getStock() > 0 && !car.isReserved()) {
        reserveButton->setStyleSheet(
            "QPushButton { background-color: #ffc107; color: #333333; border-radius: 6px; font-size: 14px; font-weight: bold; font-family: 'Segoe UI', Arial, sans-serif; }"
            "QPushButton:hover { background-color: #ffb300; }"
            "QPushButton:pressed { background-color: #ffa000; }"
        );
        connect(reserveButton, &QPushButton::clicked, this, &CarCardWidget::onReserveClicked);
    } else {
        reserveButton->setEnabled(false);
        reserveButton->setStyleSheet(
            "QPushButton { background-color: #cccccc; color: #666666; border-radius: 6px; font-size: 14px; font-weight: bold; font-family: 'Segoe UI', Arial, sans-serif; }"
        );
        if (car.isReserved()) {
            reserveButton->setText("Reserved");
        } else {
            reserveButton->setText("Out of Stock");
        }
    }
    mainLayout->addWidget(reserveButton);
    
    sellButton = new QPushButton(car.getStock() > 0 ? "Sell Car" : "Out of Stock");
    sellButton->setFixedHeight(40);
    if (car.getStock() > 0) {
        sellButton->setStyleSheet(
            "QPushButton { background-color: #4caf50; color: #ffffff; border-radius: 6px; font-size: 14px; font-weight: bold; font-family: 'Segoe UI', Arial, sans-serif; }"
            "QPushButton:hover { background-color: #45a049; }"
            "QPushButton:pressed { background-color: #3d8b40; }"
        );
        connect(sellButton, &QPushButton::clicked, this, &CarCardWidget::onSellClicked);
    } else {
        sellButton->setEnabled(false);
        sellButton->setStyleSheet(
            "QPushButton { background-color: #cccccc; color: #666666; border-radius: 6px; font-size: 14px; font-weight: bold; font-family: 'Segoe UI', Arial, sans-serif; }"
        );
    }
    mainLayout->addWidget(sellButton);
}

void CarCardWidget::updateCar(const Car& updatedCar) {
    car = updatedCar;
    
    QString imagePath = getImagePathForCar(car);
    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        pixmap = QPixmap(300, 200);
        pixmap.fill(QColor(240, 240, 240));
        QPainter painter(&pixmap);
        painter.setPen(QColor(180, 180, 180));
        painter.setFont(QFont("Arial", 14));
        painter.drawText(pixmap.rect(), Qt::AlignCenter, "No Image");
    } else {
        pixmap = pixmap.scaled(300, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    imageLabel->setPixmap(pixmap);
    
    brandModelLabel->setText(QString("%1 %2").arg(QString::fromStdString(car.getBrand())).arg(QString::fromStdString(car.getModel())));
    yearEngineLabel->setText(QString("%1, %2 HP").arg(car.getYear()).arg(car.getHorsepower()));
    priceLabel->setText(QString("$%1").arg(car.getTotalPrice(), 0, 'f', 2));
    
    if (car.getStock() > 0 && !car.isReserved()) {
        reserveButton->setText("Reserve Car");
        reserveButton->setEnabled(true);
        reserveButton->setStyleSheet(
            "QPushButton { background-color: #ffc107; color: #333333; border-radius: 6px; font-size: 14px; font-weight: bold; font-family: 'Segoe UI', Arial, sans-serif; }"
            "QPushButton:hover { background-color: #ffb300; }"
            "QPushButton:pressed { background-color: #ffa000; }"
        );
    } else {
        reserveButton->setEnabled(false);
        reserveButton->setStyleSheet(
            "QPushButton { background-color: #cccccc; color: #666666; border-radius: 6px; font-size: 14px; font-weight: bold; font-family: 'Segoe UI', Arial, sans-serif; }"
        );
        if (car.isReserved()) {
            reserveButton->setText("Reserved");
        } else {
            reserveButton->setText("Out of Stock");
        }
    }
    
    if (car.getStock() > 0) {
        sellButton->setText("Sell Car");
        sellButton->setEnabled(true);
        sellButton->setStyleSheet(
            "QPushButton { background-color: #4caf50; color: #ffffff; border-radius: 6px; font-size: 14px; font-weight: bold; font-family: 'Segoe UI', Arial, sans-serif; }"
            "QPushButton:hover { background-color: #45a049; }"
            "QPushButton:pressed { background-color: #3d8b40; }"
        );
    } else {
        sellButton->setText("Out of Stock");
        sellButton->setEnabled(false);
        sellButton->setStyleSheet(
            "QPushButton { background-color: #cccccc; color: #666666; border-radius: 6px; font-size: 14px; font-weight: bold; font-family: 'Segoe UI', Arial, sans-serif; }"
        );
    }
}

void CarCardWidget::onEditClicked() {
    emit editRequested(carIndex);
}

void CarCardWidget::onDeleteClicked() {
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Delete",
        QString("Are you sure you want to delete %1 %2?").arg(QString::fromStdString(car.getBrand())).arg(QString::fromStdString(car.getModel())),
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        emit deleteRequested(carIndex);
    }
}

void CarCardWidget::onSellClicked() {
    if (car.getStock() > 0) {
        emit sellRequested(carIndex);
    }
}

void CarCardWidget::onReserveClicked() {
    if (car.getStock() > 0 && !car.isReserved()) {
        emit reserveRequested(carIndex);
    }
}

