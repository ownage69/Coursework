#include "car.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include "safeinput.h"
#include "car_serializer.h"

namespace {
int parseIntSafe(const std::string& text, int fallback = 0) {
    try {
        if (!text.empty() && std::all_of(text.begin(), text.end(), ::isdigit)) {
            return std::stoi(text);
        }
    } catch (const std::invalid_argument&) {
    } catch (const std::out_of_range&) {
    }
    return fallback;
}

double parseDoubleSafe(const std::string& text, double fallback = 0.0) {
    try {
        if (!text.empty()) {
            return std::stod(text);
        }
    } catch (const std::invalid_argument&) {
    } catch (const std::out_of_range&) {
    }
    return fallback;
}
} // namespace

const std::map<std::string, std::set<std::string, std::less<>>, std::less<>> Car::validBrandsAndModels = {
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

Car::Car() : year(0), price(0.0), horsepower(0), stock(1) {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    std::random_device rd;
    unsigned int randPart = rd() % 10000;
    ss << "VIN" << time << randPart;
    vin = ss.str();
}

Car::Car(const std::string& brand, const std::string& model, int year, double price, const std::string& color, int horsepower, const std::string& transmission, int stock, const std::string& vin) 
    : brand(brand), model(model), year(year), price(price), color(color), horsepower(horsepower), transmission(transmission), stock(stock), vin(vin) {}

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
const std::map<std::string, double, std::less<>>& Car::getOptions() const { return options; }

double Car::getTotalPrice() const {
    double total = price;
    for (const auto& [optName, optPrice] : options) {
        total += optPrice;
    }
    return total;
}

void Car::setBrand(std::string_view newBrand) { this->brand = std::string(newBrand); }
void Car::setModel(std::string_view newModel) { this->model = std::string(newModel); }
void Car::setYear(int newYear) { this->year = newYear; }
void Car::setPrice(double newPrice) { this->price = newPrice; }
void Car::setColor(std::string_view newColor) { this->color = std::string(newColor); }
void Car::setHorsepower(int newHorsepower) { this->horsepower = newHorsepower; }
void Car::setTransmission(std::string_view newTransmission) { this->transmission = std::string(newTransmission); }
void Car::setReserved(bool isReserved) { this->reserved = isReserved; }
void Car::setReservedBy(std::string_view newReservedBy) { this->reservedBy = std::string(newReservedBy); }
void Car::setStock(int newStock) { this->stock = newStock; }
void Car::setVin(std::string_view newVin) { this->vin = std::string(newVin); }
void Car::setImagePath(std::string_view newImagePath) { this->imagePath = std::string(newImagePath); }

void Car::addOption(const std::string& option, double optionPrice) {
    options[option] = optionPrice;
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
    for (const auto& [name, optPrice] : options) {
        std::cout << "  " << name << ": $" << optPrice << std::endl;
    }
    std::cout << "Total Price: $" << getTotalPrice() << std::endl;
}

std::string Car::toString() const {
    return CarSerializer::toString(*this);
}

Car Car::fromString(const std::string& data) {
    return CarSerializer::fromString(data);
}

bool Car::isValidBrand(const std::string& brand) {
    return validBrandsAndModels.find(brand) != validBrandsAndModels.end();
}

bool Car::isValidModelForBrand(const std::string& brand, const std::string& model) {
    if (auto it = validBrandsAndModels.find(brand); it != validBrandsAndModels.end()) {
        return it->second.find(model) != it->second.end();
    }
    return false;
}

std::string Car::getValidBrandInput() {
    std::cout << "Available brands: ";
    for (const auto& [brandName, _] : validBrandsAndModels) {
        std::cout << brandName << " ";
    }
    std::cout << std::endl;
    
    while (true) {
        if (std::string brand = readLineTrimmed("Enter brand: "); isValidBrand(brand)) {
            return brand;
        }
        std::cout << "Invalid brand. Please choose from the available brands." << std::endl;
    }
}

std::string Car::getValidModelInput(const std::string& brand) {
    std::cout << "Available models for " << brand << ": ";
    if (auto it = validBrandsAndModels.find(brand); it != validBrandsAndModels.end()) {
        for (const auto& modelName : it->second) {
            std::cout << modelName << " ";
        }
    }
    std::cout << std::endl;
    
    while (true) {
        if (std::string model = readLineTrimmed("Enter model: "); isValidModelForBrand(brand, model)) {
            return model;
        }
        std::cout << "Invalid model for " << brand << ". Please choose from the available models." << std::endl;
    }
}

std::string Car::getValidColorInput() {
    std::set<std::string, std::less<>> validColors = {"Black", "White", "Silver", "Gray", "Blue", "Red", "Green", "Yellow", "Orange", "Brown", "Purple"};
    
    std::cout << "Available colors: ";
    for (const auto& colorName : validColors) {
        std::cout << colorName << " ";
    }
    std::cout << std::endl;
    
    while (true) {
        if (std::string color = readLineTrimmed("Enter color: "); validColors.find(color) != validColors.end()) {
            return color;
        }
        std::cout << "Invalid color. Please choose from the available colors." << std::endl;
    }
}

std::string Car::getValidTransmissionInput() {
    while (true) {
        std::cout << "Available transmissions: Automatic, Manual" << std::endl;
        if (std::string transmission = readLineTrimmed("Enter transmission (Automatic/Manual): "); transmission == "Automatic" || transmission == "Manual") {
            return transmission;
        }
        std::cout << "Invalid transmission. Please enter 'Automatic' or 'Manual'." << std::endl;
    }
}

std::map<std::string, double, std::less<>> Car::getAvailableOptions() {
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