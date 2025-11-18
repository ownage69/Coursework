#include "salesreportdialog.h"
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QDate>
#include <QStandardPaths>
#include <map>
#include <algorithm>
#include <iomanip>
#include <sstream>

SalesReportDialog::SalesReportDialog(DealershipManager* manager, QWidget* parent)
    : QDialog(parent), manager(manager) {
    setWindowTitle("Sales Report");
    setMinimumSize(900, 600);
    setupUI();
    generateReport();
}

void SalesReportDialog::setupUI() {
    auto* mainLayout = new QVBoxLayout(this);
    
    // Date range selection
    auto* dateGroup = new QGroupBox("Date Range");
    auto* dateLayout = new QHBoxLayout;
    
    dateLayout->addWidget(new QLabel("From:"));
    startDateEdit = new QDateEdit;
    startDateEdit->setDate(QDate::currentDate().addMonths(-1));
    startDateEdit->setCalendarPopup(true);
    dateLayout->addWidget(startDateEdit);
    
    dateLayout->addWidget(new QLabel("To:"));
    endDateEdit = new QDateEdit;
    endDateEdit->setDate(QDate::currentDate());
    endDateEdit->setCalendarPopup(true);
    dateLayout->addWidget(endDateEdit);
    
    dateLayout->addStretch();
    
    QPushButton* generateButton = new QPushButton("Generate Report");
    generateButton->setStyleSheet(
        "QPushButton { background-color: #2196f3; color: white; border: none; padding: 8px 16px; border-radius: 4px; font-size: 13px; font-weight: bold; }"
        "QPushButton:hover { background-color: #1976d2; }"
    );
    connect(generateButton, &QPushButton::clicked, this, &SalesReportDialog::onGenerateClicked);
    dateLayout->addWidget(generateButton);
    
    dateGroup->setLayout(dateLayout);
    mainLayout->addWidget(dateGroup);
    
    // Summary labels
    auto* summaryLayout = new QHBoxLayout;
    totalSalesLabel = new QLabel("Total Sales: 0");
    totalSalesLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #2c3e50;");
    totalRevenueLabel = new QLabel("Total Revenue: $0.00");
    totalRevenueLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #2c3e50;");
    summaryLayout->addWidget(totalSalesLabel);
    summaryLayout->addWidget(totalRevenueLabel);
    summaryLayout->addStretch();
    mainLayout->addLayout(summaryLayout);
    
    // Report table
    reportTable = new QTableWidget;
    reportTable->setColumnCount(5);
    reportTable->setHorizontalHeaderLabels({"Date", "Car", "Client", "Price", "Discount %"});
    reportTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    reportTable->setAlternatingRowColors(true);
    reportTable->setSortingEnabled(true);
    reportTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(reportTable);
    
    // Export buttons
    auto* buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    
    QPushButton* exportExcelButton = new QPushButton("Export to Excel");
    exportExcelButton->setStyleSheet(
        "QPushButton { background-color: #4caf50; color: white; border: none; padding: 8px 16px; border-radius: 4px; font-size: 13px; font-weight: bold; }"
        "QPushButton:hover { background-color: #45a049; }"
    );
    connect(exportExcelButton, &QPushButton::clicked, this, &SalesReportDialog::onExportExcelClicked);
    buttonLayout->addWidget(exportExcelButton);
    
    QPushButton* exportWordButton = new QPushButton("Export to Word");
    exportWordButton->setStyleSheet(
        "QPushButton { background-color: #ff9800; color: white; border: none; padding: 8px 16px; border-radius: 4px; font-size: 13px; font-weight: bold; }"
        "QPushButton:hover { background-color: #f57c00; }"
    );
    connect(exportWordButton, &QPushButton::clicked, this, &SalesReportDialog::onExportWordClicked);
    buttonLayout->addWidget(exportWordButton);
    
    QPushButton* closeButton = new QPushButton("Close");
    closeButton->setStyleSheet(
        "QPushButton { background-color: #757575; color: white; border: none; padding: 8px 16px; border-radius: 4px; font-size: 13px; font-weight: bold; }"
        "QPushButton:hover { background-color: #616161; }"
    );
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    buttonLayout->addWidget(closeButton);
    
    mainLayout->addLayout(buttonLayout);
}

void SalesReportDialog::generateReport() {
    reportTable->setRowCount(0);
    
    QDate startDate = startDateEdit->date();
    QDate endDate = endDateEdit->date();
    
    const auto& sales = manager->getSales();
    int totalSales = 0;
    double totalRevenue = 0.0;
    
    // Group sales by date
    std::map<std::string, std::vector<const Sale*>, std::less<>> salesByDate;
    
    for (const auto& sale : sales) {
        QString dateStr = QString::fromStdString(sale.getDate());
        QDate saleDate = QDate::fromString(dateStr, "yyyy-MM-dd");
        
        if (saleDate.isValid() && saleDate >= startDate && saleDate <= endDate) {
            salesByDate[sale.getDate()].push_back(&sale);
            totalSales++;
            totalRevenue += sale.getFinalPrice();
        }
    }
    
    // Populate table
    for (const auto& [date, salesList] : salesByDate) {
        for (const auto* sale : salesList) {
            int row = reportTable->rowCount();
            reportTable->insertRow(row);
            
            std::string carInfo = sale->getCar().getBrand() + " " + sale->getCar().getModel();
            std::string clientInfo = sale->getClient().getFullName();
            
            reportTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(sale->getDate())));
            reportTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(carInfo)));
            reportTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(clientInfo)));
            reportTable->setItem(row, 3, new QTableWidgetItem("$" + QString::number(sale->getFinalPrice(), 'f', 2)));
            reportTable->setItem(row, 4, new QTableWidgetItem(QString("%1%").arg(sale->getDiscountPercentage(), 0, 'f', 1)));
        }
    }
    
    totalSalesLabel->setText(QString("Total Sales: %1").arg(totalSales));
    totalRevenueLabel->setText(QString("Total Revenue: $%1").arg(totalRevenue, 0, 'f', 2));
}

void SalesReportDialog::onGenerateClicked() {
    generateReport();
}

void SalesReportDialog::exportToExcel() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export to Excel", 
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/sales_report.xls",
        "Excel Files (*.xls *.xlsx);;HTML Files (*.html);;CSV Files (*.csv)");
    
    if (fileName.isEmpty()) {
        return;
    }
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot write to file: " + fileName);
        return;
    }
    
    QTextStream out(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    out.setCodec("UTF-8");
#else
    out.setEncoding(QStringConverter::Utf8);
#endif
    
    // Use HTML format for Excel - allows column width control
    if (fileName.endsWith(".html", Qt::CaseInsensitive) || fileName.endsWith(".xls", Qt::CaseInsensitive)) {
        out << "<html><head><meta charset=\"UTF-8\">\n";
        out << "<style>\n";
        out << "table { border-collapse: collapse; width: 100%; font-family: Arial, sans-serif; }\n";
        out << "th { background-color: #4CAF50; color: white; padding: 12px; text-align: left; font-weight: bold; }\n";
        out << "td { border: 1px solid #ddd; padding: 8px; }\n";
        out << "tr:nth-child(even) { background-color: #f2f2f2; }\n";
        out << ".number { text-align: right; }\n";
        out << ".summary { font-weight: bold; background-color: #e8f5e9; }\n";
        out << "</style></head><body>\n";
        out << "<h1>SALES REPORT</h1>\n";
        out << "<p><strong>Date Range:</strong> " << startDateEdit->date().toString("yyyy-MM-dd") 
            << " to " << endDateEdit->date().toString("yyyy-MM-dd") << "</p>\n";
        out << "<p><strong>" << totalSalesLabel->text() << "</strong></p>\n";
        out << "<p><strong>" << totalRevenueLabel->text() << "</strong></p>\n";
        out << "<table>\n";
        
        // Table header with column widths
        out << "<tr>\n";
        out << "<th style=\"width: 120px;\">Date</th>\n";
        out << "<th style=\"width: 200px;\">Car</th>\n";
        out << "<th style=\"width: 150px;\">Client</th>\n";
        out << "<th style=\"width: 120px;\">Price</th>\n";
        out << "<th style=\"width: 100px;\">Discount %</th>\n";
        out << "</tr>\n";
        
        // Table data
        for (int i = 0; i < reportTable->rowCount(); ++i) {
            out << "<tr>\n";
            out << "<td>" << reportTable->item(i, 0)->text() << "</td>\n";
            out << "<td>" << reportTable->item(i, 1)->text().toHtmlEscaped() << "</td>\n";
            out << "<td>" << reportTable->item(i, 2)->text().toHtmlEscaped() << "</td>\n";
            out << "<td class=\"number\">" << reportTable->item(i, 3)->text() << "</td>\n";
            out << "<td class=\"number\">" << reportTable->item(i, 4)->text() << "</td>\n";
            out << "</tr>\n";
        }
        
        // Summary row
        out << "<tr class=\"summary\">\n";
        out << "<td colspan=\"3\">Total Sales</td>\n";
        out << "<td class=\"number\">" << totalSalesLabel->text().split(": ")[1] << "</td>\n";
        out << "<td></td>\n";
        out << "</tr>\n";
        out << "<tr class=\"summary\">\n";
        out << "<td colspan=\"3\">Total Revenue</td>\n";
        out << "<td class=\"number\">" << totalRevenueLabel->text().split(": ")[1] << "</td>\n";
        out << "<td></td>\n";
        out << "</tr>\n";
        
        out << "</table></body></html>\n";
    } else {
        // CSV format with proper quoting
        out << "Date,Car,Client,Price,Discount %\n";
        
        for (int i = 0; i < reportTable->rowCount(); ++i) {
            QString date = reportTable->item(i, 0)->text();
            QString car = "\"" + reportTable->item(i, 1)->text().replace("\"", "\"\"") + "\"";
            QString client = "\"" + reportTable->item(i, 2)->text().replace("\"", "\"\"") + "\"";
            QString price = reportTable->item(i, 3)->text();
            QString discount = reportTable->item(i, 4)->text();
            
            out << date << "," << car << "," << client << "," << price << "," << discount << "\n";
        }
        
        out << "\n";
        out << "Total Sales," << totalSalesLabel->text().split(": ")[1] << "\n";
        out << "Total Revenue," << totalRevenueLabel->text().split(": ")[1] << "\n";
    }
    
    file.close();
    QMessageBox::information(this, "Success", "Report exported to: " + fileName + 
        "\n\nNote: If exported as HTML/XLS, open in Excel for best formatting.");
}

void SalesReportDialog::exportToWord() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export to Word", 
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/sales_report.rtf",
        "RTF Files (*.rtf);;Word Documents (*.doc);;All Files (*.*)");
    
    if (fileName.isEmpty()) {
        return;
    }
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot write to file: " + fileName);
        return;
    }
    
    QTextStream out(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    out.setCodec("UTF-8");
#else
    out.setEncoding(QStringConverter::Utf8);
#endif
    
    // RTF header
    out << "{\\rtf1\\ansi\\deff0 {\\fonttbl {\\f0 Times New Roman;}}\n";
    out << "{\\colortbl;\\red0\\green0\\blue0;\\red0\\green0\\blue255;}\n";
    out << "\\paperw12240\\paperh15840\\margl1800\\margr1800\\margt1440\\margb1440\n";
    
    // Title
    out << "{\\f0\\fs32\\b SALES REPORT\\par}\n";
    out << "{\\f0\\fs24\\par}\n";
    
    // Date range
    out << "{\\f0\\fs20 Date Range: " << startDateEdit->date().toString("yyyy-MM-dd") 
        << " to " << endDateEdit->date().toString("yyyy-MM-dd") << "\\par}\n";
    out << "{\\f0\\fs20\\par}\n";
    
    // Summary
    out << "{\\f0\\fs20\\b " << totalSalesLabel->text() << "\\par}\n";
    out << "{\\f0\\fs20\\b " << totalRevenueLabel->text() << "\\par}\n";
    out << "{\\f0\\fs20\\par}\n";
    
    // Table header with proper column widths (in twips: 1 inch = 1440 twips)
    out << "{\\f0\\fs18\\b\\trowd\\trgaph108\\trleft-108\n";
    out << "\\cellx2500\\cellx5500\\cellx8500\\cellx11000\\cellx13000\n";
    out << "\\intbl Date\\cell\n";
    out << "\\intbl Car\\cell\n";
    out << "\\intbl Client\\cell\n";
    out << "\\intbl Price\\cell\n";
    out << "\\intbl Discount %\\cell\n";
    out << "\\row}\n";
    
    // Table data
    for (int i = 0; i < reportTable->rowCount(); ++i) {
        out << "{\\f0\\fs16\\trowd\\trgaph108\\trleft-108\n";
        out << "\\cellx2500\\cellx5500\\cellx8500\\cellx11000\\cellx13000\n";
        out << "\\intbl " << reportTable->item(i, 0)->text() << "\\cell\n";
        out << "\\intbl " << reportTable->item(i, 1)->text() << "\\cell\n";
        out << "\\intbl " << reportTable->item(i, 2)->text() << "\\cell\n";
        out << "\\intbl " << reportTable->item(i, 3)->text() << "\\cell\n";
        out << "\\intbl " << reportTable->item(i, 4)->text() << "\\cell\n";
        out << "\\row}\n";
    }
    
    // Summary rows
    out << "{\\f0\\fs16\\b\\trowd\\trgaph108\\trleft-108\n";
    out << "\\cellx2500\\cellx5500\\cellx8500\\cellx11000\\cellx13000\n";
    out << "\\intbl Total Sales\\cell\n";
    out << "\\intbl \\cell\n";
    out << "\\intbl \\cell\n";
    out << "\\intbl " << totalSalesLabel->text().split(": ")[1] << "\\cell\n";
    out << "\\intbl \\cell\n";
    out << "\\row}\n";
    
    out << "{\\f0\\fs16\\b\\trowd\\trgaph108\\trleft-108\n";
    out << "\\cellx2500\\cellx5500\\cellx8500\\cellx11000\\cellx13000\n";
    out << "\\intbl Total Revenue\\cell\n";
    out << "\\intbl \\cell\n";
    out << "\\intbl \\cell\n";
    out << "\\intbl " << totalRevenueLabel->text().split(": ")[1] << "\\cell\n";
    out << "\\intbl \\cell\n";
    out << "\\row}\n";
    
    // RTF footer
    out << "}\n";
    
    file.close();
    QMessageBox::information(this, "Success", "Report exported to: " + fileName + "\n\nThe file can be opened in Microsoft Word or any RTF-compatible word processor.");
}

void SalesReportDialog::onExportExcelClicked() {
    exportToExcel();
}

void SalesReportDialog::onExportWordClicked() {
    exportToWord();
}

