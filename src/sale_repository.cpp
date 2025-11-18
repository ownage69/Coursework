#include "sale_repository.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

SaleRepository::SaleRepository(const std::string& dataPath) : dataPath(dataPath) {
    if (!dataPath.empty()) {
        loadFromFile();
    }
}

const std::vector<Sale>& SaleRepository::getAll() const {
    return sales;
}

bool SaleRepository::add(const Sale& sale) {
    sales.push_back(sale);
    return saveToFile();
}

bool SaleRepository::remove(size_t index) {
    if (index >= sales.size()) {
        return false;
    }
    sales.erase(sales.begin() + index);
    return saveToFile();
}

bool SaleRepository::loadFromFile() {
    if (dataPath.empty()) {
        return false;
    }
    
    sales.clear();
    if (QFile saleFile(QString::fromStdString(dataPath + "sales.txt")); saleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&saleFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.isEmpty()) {
                try {
                    sales.push_back(Sale::fromString(line.toStdString()));
                } catch (const std::invalid_argument& e) {
                    qCritical() << "Error parsing sale (invalid argument): " << e.what();
                } catch (const std::exception& e) {
                    qCritical() << "Error parsing sale: " << e.what();
                }
            }
        }
        saleFile.close();
        qDebug() << "Loaded" << sales.size() << "sales";
        return true;
    }
    return false;
}

bool SaleRepository::saveToFile() const {
    if (dataPath.empty()) {
        return false;
    }
    
    if (QFile saleFile(QString::fromStdString(dataPath + "sales.txt")); saleFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&saleFile);
        for (const auto& sale : sales) {
            out << QString::fromStdString(sale.toString()) << "\n";
        }
        saleFile.close();
        qDebug() << "Saved" << sales.size() << "sales";
        return true;
    }
    return false;
}

