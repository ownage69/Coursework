#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QDateEdit>
#include <QGroupBox>
#include "dealership_manager.h"

class SalesReportDialog : public QDialog {
    Q_OBJECT

private:
    DealershipManager* manager;
    QTableWidget* reportTable;
    QLabel* totalSalesLabel;
    QLabel* totalRevenueLabel;
    QDateEdit* startDateEdit;
    QDateEdit* endDateEdit;
    
    void setupUI();
    void generateReport();
    void exportToExcel();
    void exportToWord();

public:
    explicit SalesReportDialog(DealershipManager* manager, QWidget* parent = nullptr);

private slots:
    void onGenerateClicked();
    void onExportExcelClicked();
    void onExportWordClicked();
};

