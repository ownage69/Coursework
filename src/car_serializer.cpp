#include "car_serializer.h"
#include <sstream>
#include <algorithm>

std::string CarSerializer::toString(const Car& car) {
    std::string result = car.getBrand() + "," + car.getModel() + "," + 
                        std::to_string(car.getYear()) + "," + 
                        std::to_string(car.getPrice()) + "," + 
                        car.getColor() + "," + 
                        std::to_string(car.getHorsepower()) + "," + 
                        car.getTransmission() + "," + 
                        (car.isReserved() ? "1" : "0") + "," + 
                        car.getReservedBy() + "," + 
                        std::to_string(car.getStock()) + "," + 
                        car.getVin() + "," + 
                        car.getImagePath() + ",";
    
    const auto& options = car.getOptions();
    for (auto it = options.begin(); it != options.end(); ++it) {
        if (it != options.begin()) result += ";";
        result += it->first + ";" + std::to_string(it->second);
    }
    
    return result;
}

Car CarSerializer::fromString(const std::string& data) {
    std::stringstream ss(data);
    std::string brand, model, yearStr, priceStr, color, horsepowerStr, transmission, reservedStr, reservedBy, stockStr, vin, imagePath, optionsStr;
    
    std::getline(ss, brand, ',');
    std::getline(ss, model, ',');
    std::getline(ss, yearStr, ',');
    std::getline(ss, priceStr, ',');
    std::getline(ss, color, ',');
    std::getline(ss, horsepowerStr, ',');
    std::getline(ss, transmission, ',');
    std::getline(ss, reservedStr, ',');
    std::getline(ss, reservedBy, ',');
    std::getline(ss, stockStr, ',');
    std::getline(ss, vin, ',');
    std::getline(ss, imagePath, ',');
    std::getline(ss, optionsStr, ',');
    
    int year = 0;
    try {
        if (!yearStr.empty() && std::all_of(yearStr.begin(), yearStr.end(), ::isdigit)) {
            year = std::stoi(yearStr);
        }
    } catch (const std::invalid_argument&) {
        year = 0;
    } catch (const std::out_of_range&) {
        year = 0;
    }
    
    double price = 0.0;
    try {
        if (!priceStr.empty()) {
            price = std::stod(priceStr);
        }
    } catch (const std::invalid_argument&) {
        price = 0.0;
    } catch (const std::out_of_range&) {
        price = 0.0;
    }
    
    int horsepower = 0;
    try {
        if (!horsepowerStr.empty() && std::all_of(horsepowerStr.begin(), horsepowerStr.end(), ::isdigit)) {
            horsepower = std::stoi(horsepowerStr);
        }
    } catch (const std::invalid_argument&) {
        horsepower = 0;
    } catch (const std::out_of_range&) {
        horsepower = 0;
    }
    
    bool reserved = reservedStr == "1";
    
    int stock = 1;
    try {
        if (!stockStr.empty() && std::all_of(stockStr.begin(), stockStr.end(), ::isdigit)) {
            stock = std::stoi(stockStr);
        }
    } catch (const std::invalid_argument&) {
        stock = 1;
    } catch (const std::out_of_range&) {
        stock = 1;
    }
    
    Car car(brand, model, year, price, color, horsepower, transmission, stock, vin);
    car.setReserved(reserved);
    car.setReservedBy(reservedBy);
    if (!imagePath.empty()) {
        car.setImagePath(imagePath);
    }
    
    if (!optionsStr.empty()) {
        std::stringstream optionsSs(optionsStr);
        std::string optionItem;
        std::vector<std::string> parts;
        while (std::getline(optionsSs, optionItem, ';')) {
            parts.push_back(optionItem);
        }
        // Parts come in pairs: option name, price
        for (size_t i = 0; i + 1 < parts.size(); i += 2) {
            std::string option = parts[i];
            double optionPrice = 0.0;
            try {
                if (!parts[i + 1].empty()) {
                    optionPrice = std::stod(parts[i + 1]);
                }
            } catch (const std::invalid_argument&) {
                optionPrice = 0.0;
            } catch (const std::out_of_range&) {
                optionPrice = 0.0;
            }
            if (!option.empty()) {
                car.addOption(option, optionPrice);
            }
        }
    }
    
    return car;
}

