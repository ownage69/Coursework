#include "car_repository.h"
#include "car_serializer.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

CarRepository::CarRepository(const std::string& dataPath) : dataPath(dataPath) {
    if (!dataPath.empty()) {
        loadFromFile();
    }
}

const std::vector<Car>& CarRepository::getAll() const {
    return cars;
}

bool CarRepository::add(const Car& car) {
    cars.push_back(car);
    return saveToFile();
}

bool CarRepository::update(size_t index, const Car& car) {
    if (index >= cars.size()) {
        return false;
    }
    cars[index] = car;
    return saveToFile();
}

bool CarRepository::remove(size_t index) {
    if (index >= cars.size()) {
        return false;
    }
    cars.erase(cars.begin() + index);
    return saveToFile();
}

Car* CarRepository::findByIndex(size_t index) {
    if (index >= cars.size()) {
        return nullptr;
    }
    return &cars[index];
}

const Car* CarRepository::findByIndex(size_t index) const {
    if (index >= cars.size()) {
        return nullptr;
    }
    return &cars[index];
}

bool CarRepository::loadFromFile() {
    if (dataPath.empty()) {
        return false;
    }
    
    cars.clear();
    if (QFile carFile(QString::fromStdString(dataPath + "cars.txt")); carFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&carFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.isEmpty()) {
                try {
                    cars.push_back(CarSerializer::fromString(line.toStdString()));
                } catch (const std::invalid_argument& e) {
                    qCritical() << "Error parsing car (invalid argument): " << e.what();
                } catch (const std::exception& e) {
                    qCritical() << "Error parsing car: " << e.what();
                }
            }
        }
        carFile.close();
        return true;
    }
    return false;
}

bool CarRepository::saveToFile() const {
    if (dataPath.empty()) {
        return false;
    }
    
    if (QFile carFile(QString::fromStdString(dataPath + "cars.txt")); carFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&carFile);
        for (const auto& car : cars) {
            out << QString::fromStdString(CarSerializer::toString(car)) << "\n";
        }
        carFile.close();
        return true;
    }
    return false;
}

std::vector<Car> CarRepository::searchByBrand(const std::string& brand) const {
    std::vector<Car> results;
    for (const auto& car : cars) {
        if (car.getBrand() == brand) {
            results.push_back(car);
        }
    }
    return results;
}

std::vector<Car> CarRepository::searchByModel(const std::string& model) const {
    std::vector<Car> results;
    for (const auto& car : cars) {
        if (car.getModel() == model) {
            results.push_back(car);
        }
    }
    return results;
}

std::vector<Car> CarRepository::searchByPriceRange(double minPrice, double maxPrice) const {
    std::vector<Car> results;
    for (const auto& car : cars) {
        double price = car.getTotalPrice();
        if (price >= minPrice && price <= maxPrice) {
            results.push_back(car);
        }
    }
    return results;
}

std::vector<Car> CarRepository::searchByColor(const std::string& color) const {
    std::vector<Car> results;
    for (const auto& car : cars) {
        if (car.getColor() == color) {
            results.push_back(car);
        }
    }
    return results;
}

std::vector<Car> CarRepository::searchByHorsepower(int minHp, int maxHp) const {
    std::vector<Car> results;
    for (const auto& car : cars) {
        int hp = car.getHorsepower();
        if (hp >= minHp && hp <= maxHp) {
            results.push_back(car);
        }
    }
    return results;
}

std::vector<Car> CarRepository::searchByTransmission(const std::string& transmission) const {
    std::vector<Car> results;
    for (const auto& car : cars) {
        if (car.getTransmission() == transmission) {
            results.push_back(car);
        }
    }
    return results;
}

