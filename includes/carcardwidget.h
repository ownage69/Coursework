#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include "car.h"

class CarCardWidget : public QWidget {
    Q_OBJECT

private:
    Car car;
    size_t carIndex;
    
    QLabel* imageLabel;
    QLabel* brandModelLabel;
    QLabel* yearEngineLabel;
    QLabel* priceLabel;
    QPushButton* reserveButton;
    QPushButton* sellButton;
    QPushButton* editButton;
    QPushButton* deleteButton;
    
    QString getImagePathForCar(const Car& car) const;

public:
    CarCardWidget(const Car& car, size_t index, QWidget* parent = nullptr);
    void updateCar(const Car& updatedCar);

signals:
    void editRequested(size_t index);
    void deleteRequested(size_t index);
    void sellRequested(size_t index);
    void reserveRequested(size_t index);

private slots:
    void onEditClicked();
    void onDeleteClicked();
    void onSellClicked();
    void onReserveClicked();
};

