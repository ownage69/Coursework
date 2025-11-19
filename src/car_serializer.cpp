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

namespace {
    int parseInteger(const std::string& str, int defaultValue) {
        if (str.empty() || !std::all_of(str.begin(), str.end(), ::isdigit)) {
            return defaultValue;
        }
        try {
            return std::stoi(str);
        } catch (const std::invalid_argument&) {
            return defaultValue;
        } catch (const std::out_of_range&) {
            return defaultValue;
        }
    }
    
    double parseDouble(const std::string& str, double defaultValue) {
        if (str.empty()) {
            return defaultValue;
        }
        try {
            return std::stod(str);
        } catch (const std::invalid_argument&) {
            return defaultValue;
        } catch (const std::out_of_range&) {
            return defaultValue;
        }
    }
    
    void parseOptions(Car& car, const std::string& optionsStr) {
        if (optionsStr.empty()) {
            return;
        }
        std::stringstream optionsSs(optionsStr);
        std::string optionItem;
        std::vector<std::string> parts;
        while (std::getline(optionsSs, optionItem, ';')) {
            parts.push_back(optionItem);
        }
        // Parts come in pairs: option name, price
        for (size_t i = 0; i + 1 < parts.size(); i += 2) {
            std::string option = parts[i];
            double optionPrice = parseDouble(parts[i + 1], 0.0);
            if (!option.empty()) {
                car.addOption(option, optionPrice);
            }
        }
    }
}

Car CarSerializer::fromString(const std::string& data) {
    std::stringstream ss(data);
    std::string brand;
    std::string model;
    std::string yearStr;
    std::string priceStr;
    std::string color;
    std::string horsepowerStr;
    std::string transmission;
    std::string reservedStr;
    std::string reservedBy;
    std::string stockStr;
    std::string vin;
    std::string imagePath;
    std::string optionsStr;
    
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
    
    int year = parseInteger(yearStr, 0);
    double price = parseDouble(priceStr, 0.0);
    int horsepower = parseInteger(horsepowerStr, 0);
    int stock = parseInteger(stockStr, 1);
    bool reserved = reservedStr == "1";
    
    Car::CarSpec spec{brand, model, year, price, color, horsepower, transmission, stock, vin};
    Car car(spec);
    car.setReserved(reserved);
    car.setReservedBy(reservedBy);
    if (!imagePath.empty()) {
        car.setImagePath(imagePath);
    }
    
    parseOptions(car, optionsStr);
    
    return car;
}

