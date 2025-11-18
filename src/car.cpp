#include "car.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include "safeinput.h"

const std::map<std::string, std::set<std::string>> Car::validBrandsAndModels = {
    {"BMW", {"3 Series", "5 Series", "X5", "M3", "i8"}},
    {"Audi", {"A4", "Q7", "RS6", "e-tron", "TT"}},
    {"Toyota", {"Camry", "Corolla", "RAV4", "Prius", "Highlander"}},
    {"Mercedes", {"C-Class", "E-Class", "S-Class", "GLE", "AMG GT"}},
    {"Ford", {"Mustang", "F-150", "Focus", "Explorer", "Bronco"}},
    {"Volkswagen", {"Golf", "Passat", "Tiguan", "Beetle", "ID.4"}},
    {"Honda", {"Civic", "Accord", "CR-V", "Pilot", "Odyssey"}},
    {"Tesla", {"Model 3", "Model Y", "Model S", "Cybertruck", "Model X"}},
    {"Chevrolet", {"Silverado", "Camaro", "Tahoe", "Equinox", "Corvette"}},
    {"Hyundai", {"Sonata", "Tucson", "Santa Fe", "Elantra", "Palisade"}}
};

Car::Car() : year(0), price(0.0), horsepower(0), reserved(false), stock(1), imagePath(":/images/default_car.png") {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << "VIN" << time << std::rand() % 10000;
    vin = ss.str();
}

Car::Car(std::string brand, std::string model, int year, double price, std::string color, int horsepower, std::string transmission, int stock, std::string vin) 
    : brand(brand), model(model), year(year), price(price), color(color), horsepower(horsepower), transmission(transmission), reserved(false), stock(stock), vin(vin), imagePath(":/images/default_car.png") {}

std::string Car::getBrand() const { return brand; }
std::string Car::getModel() const { return model; }
int Car::getYear() const { return year; }
double Car::getPrice() const { return price; }
std::string Car::getColor() const { return color; }
int Car::getHorsepower() const { return horsepower; }
std::string Car::getTransmission() const { return transmission; }
bool Car::isReserved() const { return reserved; }
std::string Car::getReservedBy() const { return reservedBy; }
int Car::getStock() const { return stock; }
std::string Car::getVin() const { return vin; }
std::string Car::getImagePath() const { return imagePath; }
const std::map<std::string, double>& Car::getOptions() const { return options; }

double Car::getTotalPrice() const {
    double total = price;
    for (const auto& option : options) {
        total += option.second;
    }
    return total;
}

void Car::setBrand(std::string brand) { this->brand = brand; }
void Car::setModel(std::string model) { this->model = model; }
void Car::setYear(int year) { this->year = year; }
void Car::setPrice(double price) { this->price = price; }
void Car::setColor(std::string color) { this->color = color; }
void Car::setHorsepower(int horsepower) { this->horsepower = horsepower; }
void Car::setTransmission(std::string transmission) { this->transmission = transmission; }
void Car::setReserved(bool reserved) { this->reserved = reserved; }
void Car::setReservedBy(std::string reservedBy) { this->reservedBy = reservedBy; }
void Car::setStock(int stock) { this->stock = stock; }
void Car::setVin(std::string vin) { this->vin = vin; }
void Car::setImagePath(std::string imagePath) { this->imagePath = imagePath; }

void Car::addOption(const std::string& option, double price) {
    options[option] = price;
}

void Car::removeOption(const std::string& option) {
    options.erase(option);
}

void Car::display() const {
    std::cout << "Brand: " << brand << std::endl;
    std::cout << "Model: " << model << std::endl;
    std::cout << "Year: " << year << std::endl;
    std::cout << "Price: $" << price << std::endl;
    std::cout << "Color: " << color << std::endl;
    std::cout << "Horsepower: " << horsepower << " HP" << std::endl;
    std::cout << "Transmission: " << transmission << std::endl;
    std::cout << "Stock: " << stock << std::endl;
    std::cout << "VIN: " << vin << std::endl;
    std::cout << "Reserved: " << (reserved ? "Yes" : "No") << std::endl;
    if (reserved) {
        std::cout << "Reserved by: " << reservedBy << std::endl;
    }
    std::cout << "Options:" << std::endl;
    for (const auto& option : options) {
        std::cout << "  " << option.first << ": $" << option.second << std::endl;
    }
    std::cout << "Total Price: $" << getTotalPrice() << std::endl;
}

std::string Car::toString() const {
    std::string result = brand + "," + model + "," + std::to_string(year) + "," + std::to_string(price) + "," + color + "," + std::to_string(horsepower) + "," + transmission + "," + (reserved ? "1" : "0") + "," + reservedBy + "," + std::to_string(stock) + "," + vin + "," + imagePath + ",";
    
    for (auto it = options.begin(); it != options.end(); ++it) {
        if (it != options.begin()) result += ";";
        result += it->first + ";" + std::to_string(it->second);
    }
    
    return result;
}

Car Car::fromString(std::string data) {
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

bool Car::isValidBrand(const std::string& brand) {
    return validBrandsAndModels.find(brand) != validBrandsAndModels.end();
}

bool Car::isValidModelForBrand(const std::string& brand, const std::string& model) {
    auto it = validBrandsAndModels.find(brand);
    if (it != validBrandsAndModels.end()) {
        return it->second.find(model) != it->second.end();
    }
    return false;
}

std::string Car::getValidBrandInput() {
    std::cout << "Available brands: ";
    for (const auto& pair : validBrandsAndModels) {
        std::cout << pair.first << " ";
    }
    std::cout << std::endl;
    
    while (true) {
        std::string brand = readLineTrimmed("Enter brand: ");
        if (isValidBrand(brand)) {
            return brand;
        }
        std::cout << "Invalid brand. Please choose from the available brands." << std::endl;
    }
}

std::string Car::getValidModelInput(const std::string& brand) {
    std::cout << "Available models for " << brand << ": ";
    auto it = validBrandsAndModels.find(brand);
    if (it != validBrandsAndModels.end()) {
        for (const auto& model : it->second) {
            std::cout << model << " ";
        }
    }
    std::cout << std::endl;
    
    while (true) {
        std::string model = readLineTrimmed("Enter model: ");
        if (isValidModelForBrand(brand, model)) {
            return model;
        }
        std::cout << "Invalid model for " << brand << ". Please choose from the available models." << std::endl;
    }
}

std::string Car::getValidColorInput() {
    std::set<std::string> validColors = {"Black", "White", "Silver", "Gray", "Blue", "Red", "Green", "Yellow", "Orange", "Brown", "Purple"};
    
    std::cout << "Available colors: ";
    for (const auto& color : validColors) {
        std::cout << color << " ";
    }
    std::cout << std::endl;
    
    while (true) {
        std::string color = readLineTrimmed("Enter color: ");
        if (validColors.find(color) != validColors.end()) {
            return color;
        }
        std::cout << "Invalid color. Please choose from the available colors." << std::endl;
    }
}

std::string Car::getValidTransmissionInput() {
    while (true) {
        std::cout << "Available transmissions: Automatic, Manual" << std::endl;
        std::string transmission = readLineTrimmed("Enter transmission (Automatic/Manual): ");
        if (transmission == "Automatic" || transmission == "Manual") {
            return transmission;
        }
        std::cout << "Invalid transmission. Please enter 'Automatic' or 'Manual'." << std::endl;
    }
}

const std::map<std::string, double> Car::getAvailableOptions() {
    return {
        {"Leather Seats", 1000.0},
        {"Navigation System", 500.0},
        {"Sunroof", 800.0},
        {"Premium Audio", 600.0},
        {"Heated Seats", 400.0},
        {"Backup Camera", 300.0},
        {"Alloy Wheels", 700.0},
        {"Towing Package", 900.0}
    };
}