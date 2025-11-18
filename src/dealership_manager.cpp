#include "dealership_manager.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QCoreApplication>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <QMessageBox>
#include <QtGlobal>
#include <chrono>
#include <ctime>

DealershipManager::DealershipManager() : dataLoaded(false) {
    loadDataFromFiles();
    dataLoaded = true;
}

const std::vector<Car>& DealershipManager::getCars() const {
    return cars;
}

const std::vector<Client>& DealershipManager::getClients() const {
    return clients;
}

const std::vector<Sale>& DealershipManager::getSales() const {
    return sales;
}

bool DealershipManager::addCar(Car car) {
    cars.push_back(car);
    saveDataToFiles();
    return true;
}

bool DealershipManager::addClient(Client client) {
    clients.push_back(client);
    saveDataToFiles();
    return true;
}

bool DealershipManager::addSale(Sale sale) {
    sales.push_back(sale);
    saveDataToFiles();
    return true;
}

bool DealershipManager::makeSale(size_t carIndex, size_t clientIndex, double originalPrice, double finalPrice, double discount) {
    if (carIndex >= cars.size() || clientIndex >= clients.size()) {
        return false;
    }

    Car& car = cars[carIndex];
    Client& client = clients[clientIndex];

    if (car.getStock() <= 0 || client.getBalance() < finalPrice) {
        return false;
    }
    
    if (car.isReserved() && car.getReservedBy() != client.getFullName()) {
        return false;
    }

    client.setBalance(client.getBalance() - finalPrice);
    car.setStock(car.getStock() - 1);

    // Use the car as-is (options are already in the car object)
    Sale sale(car, client, getCurrentDate(), originalPrice, finalPrice, discount, 0.0);
    sales.push_back(sale);

    if (car.getStock() == 0) {
        cars.erase(cars.begin() + carIndex);
    }

    saveDataToFiles();
    return true;
}

bool DealershipManager::makeSaleWithCar(const Car& carWithOptions, size_t carIndex, size_t clientIndex, double originalPrice, double finalPrice, double discount) {
    if (carIndex >= cars.size() || clientIndex >= clients.size()) {
        return false;
    }

    Car& car = cars[carIndex];
    Client& client = clients[clientIndex];

    if (car.getStock() <= 0 || client.getBalance() < finalPrice) {
        return false;
    }
    
    if (car.isReserved() && car.getReservedBy() != client.getFullName()) {
        return false;
    }

    client.setBalance(client.getBalance() - finalPrice);
    car.setStock(car.getStock() - 1);

    // Use the car with selected options for the sale
    Sale sale(carWithOptions, client, getCurrentDate(), originalPrice, finalPrice, discount, 0.0);
    sales.push_back(sale);

    if (car.getStock() == 0) {
        cars.erase(cars.begin() + carIndex);
    }

    saveDataToFiles();
    return true;
}

double DealershipManager::calculateDiscountForSale(const Client& client, const Car& car) const {
    Q_UNUSED(car);
    double discount = 0.0;
    if (Sale::isFirstTimeBuyer(client, sales)) {
        discount += 10.0;
    }
    if (Sale::isReturningClient(client, sales)) {
        discount += 5.0;
    }
    if (Sale::isWinterMonth()) {
        discount += 7.0;
    }
    return discount;
}

bool DealershipManager::loadData() {
    dataLoaded = true;
    return loadDataFromFiles();
}

bool DealershipManager::saveData() {
    return saveDataToFiles();
}

bool DealershipManager::loadDataFromFiles() {
    cars.clear();
    clients.clear();
    sales.clear();
    QString dataPath = "D:/Labs/3sem/labsBSUIR3rdTerm/coursework/";
    qDebug() << "Loading from:" << dataPath;
    try {
        QFile carFile(dataPath + "cars.txt");
        if (carFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&carFile);
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (!line.isEmpty()) {
                    try {
                        cars.push_back(Car::fromString(line.toStdString()));
                    } catch (const std::exception& e) {
                        qCritical() << "Error parsing car: " << e.what();
                    }
                }
            }
            carFile.close();
        }

        QFile clientFile(dataPath + "clients.txt");
        if (clientFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&clientFile);
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (!line.isEmpty()) {
                    try {
                        clients.push_back(Client::fromString(line.toStdString()));
                    } catch (const std::exception& e) {
                        qCritical() << "Error parsing client: " << e.what();
                    }
                }
            }
            clientFile.close();
        }

        QFile saleFile(dataPath + "sales.txt");
        if (saleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&saleFile);
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (!line.isEmpty()) {
                    try {
                        sales.push_back(Sale::fromString(line.toStdString()));
                    } catch (const std::exception& e) {
                        qCritical() << "Error parsing sale: " << e.what();
                    }
                }
            }
            saleFile.close();
        }
        qDebug() << "Loaded" << sales.size() << "sales";
        return true;
    } catch (const std::exception& e) {
        qCritical() << "Error loading data: " << e.what();
        return false;
    }
}

bool DealershipManager::saveDataToFiles() {
    QString dataPath = "D:/Labs/3sem/labsBSUIR3rdTerm/coursework/";
    qDebug() << "Saving to:" << dataPath;
    try {
        QFile carFile(dataPath + "cars.txt");
        if (carFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&carFile);
            for (const auto& car : cars) {
                out << QString::fromStdString(car.toString()) << "\n";
            }
            carFile.close();
        }

        QFile clientFile(dataPath + "clients.txt");
        if (clientFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&clientFile);
            for (const auto& client : clients) {
                out << QString::fromStdString(client.toString()) << "\n";
            }
            clientFile.close();
        }

        QFile saleFile(dataPath + "sales.txt");
        if (saleFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&saleFile);
            for (const auto& sale : sales) {
                out << QString::fromStdString(sale.toString()) << "\n";
            }
            saleFile.close();
        }
        qDebug() << "Saved" << sales.size() << "sales";
        return true;
    } catch (const std::exception& e) {
        qCritical() << "Error saving data: " << e.what();
        return false;
    }
}

int DealershipManager::getTotalCarsInStock() const {
    int total = 0;
    for (const auto& car : cars) {
        total += car.getStock();
    }
    return total;
}

int DealershipManager::getTotalUniqueModels() const {
    std::set<std::string> models;
    for (const auto& car : cars) {
        models.insert(car.getBrand() + " " + car.getModel());
    }
    return models.size();
}

bool DealershipManager::clearData() {
    cars.clear();
    clients.clear();
    sales.clear();
    dataLoaded = false;
    return saveDataToFiles();
}

bool DealershipManager::reserveCar(size_t carIndex, size_t clientIndex) {
    if (carIndex >= cars.size() || clientIndex >= clients.size()) {
        return false;
    }
    Car& car = cars[carIndex];
    if (car.isReserved() || car.getStock() <= 0) {
        return false;
    }
    car.setReserved(true);
    car.setReservedBy(clients[clientIndex].getFullName());
    saveDataToFiles();
    return true;
}

bool DealershipManager::unreserveCar(const std::string& vin) {
    for (auto& car : cars) {
        if (car.getVin() == vin && car.isReserved()) {
            car.setReserved(false);
            saveDataToFiles();
            return true;
        }
    }
    return false;
}

bool DealershipManager::editCar(size_t index, const Car& newCar) {
    if (index >= cars.size()) {
        return false;
    }
    cars[index] = newCar;
    saveDataToFiles();
    return true;
}

bool DealershipManager::deleteCar(size_t index) {
    if (index >= cars.size()) {
        return false;
    }
    cars.erase(cars.begin() + index);
    saveDataToFiles();
    return true;
}

bool DealershipManager::deleteClient(size_t index) {
    if (index >= clients.size()) {
        return false;
    }
    clients.erase(clients.begin() + index);
    saveDataToFiles();
    return true;
}

bool DealershipManager::deleteSale(size_t index) {
    if (index >= sales.size()) {
        return false;
    }
    sales.erase(sales.begin() + index);
    saveDataToFiles();
    return true;
}

std::vector<Car> DealershipManager::searchCarsByBrand(const std::string& brand) const {
    std::vector<Car> results;
    for (const auto& car : cars) {
        if (car.getBrand() == brand) {
            results.push_back(car);
        }
    }
    return results;
}

std::vector<Car> DealershipManager::searchCarsByModel(const std::string& model) const {
    std::vector<Car> results;
    for (const auto& car : cars) {
        if (car.getModel() == model) {
            results.push_back(car);
        }
    }
    return results;
}

std::vector<Car> DealershipManager::searchCarsByPriceRange(double minPrice, double maxPrice) const {
    std::vector<Car> results;
    for (const auto& car : cars) {
        double price = car.getTotalPrice();
        if (price >= minPrice && price <= maxPrice) {
            results.push_back(car);
        }
    }
    return results;
}

std::vector<Car> DealershipManager::searchCarsByColor(const std::string& color) const {
    std::vector<Car> results;
    for (const auto& car : cars) {
        if (car.getColor() == color) {
            results.push_back(car);
        }
    }
    return results;
}

std::vector<Car> DealershipManager::searchCarsByHorsepower(int minHp, int maxHp) const {
    std::vector<Car> results;
    for (const auto& car : cars) {
        int hp = car.getHorsepower();
        if (hp >= minHp && hp <= maxHp) {
            results.push_back(car);
        }
    }
    return results;
}

std::vector<Car> DealershipManager::searchCarsByTransmission(const std::string& transmission) const {
    std::vector<Car> results;
    for (const auto& car : cars) {
        if (car.getTransmission() == transmission) {
            results.push_back(car);
        }
    }
    return results;
}

std::string DealershipManager::getCurrentDate() const {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
    return ss.str();
}