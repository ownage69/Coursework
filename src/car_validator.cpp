#include "car_validator.h"
#include "safeinput.h"
#include <iostream>

static const std::map<std::string, std::set<std::string, std::less<>>, std::less<>> validBrandsAndModels = {
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

const std::map<std::string, std::set<std::string>>& CarValidator::getValidBrandsAndModels() {
    return validBrandsAndModels;
}

bool CarValidator::isValidBrand(const std::string& brand) {
    return validBrandsAndModels.find(brand) != validBrandsAndModels.end();
}

bool CarValidator::isValidModelForBrand(const std::string& brand, const std::string& model) {
    if (auto it = validBrandsAndModels.find(brand); it != validBrandsAndModels.end()) {
        return it->second.find(model) != it->second.end();
    }
    return false;
}

std::string CarValidator::getValidBrandInput() {
    std::cout << "Available brands: ";
    for (const auto& [brandName, models] : validBrandsAndModels) {
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

std::string CarValidator::getValidModelInput(const std::string& brand) {
    std::cout << "Available models for " << brand << ": ";
    if (auto it = validBrandsAndModels.find(brand); it != validBrandsAndModels.end()) {
        for (const auto& model : it->second) {
            std::cout << model << " ";
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

std::string CarValidator::getValidColorInput() {
    std::set<std::string, std::less<>> validColors = {"Black", "White", "Silver", "Gray", "Blue", "Red", "Green", "Yellow", "Orange", "Brown", "Purple"};
    
    std::cout << "Available colors: ";
    for (const auto& color : validColors) {
        std::cout << color << " ";
    }
    std::cout << std::endl;
    
    while (true) {
        if (std::string color = readLineTrimmed("Enter color: "); validColors.find(color) != validColors.end()) {
            return color;
        }
        std::cout << "Invalid color. Please choose from the available colors." << std::endl;
    }
}

std::string CarValidator::getValidTransmissionInput() {
    while (true) {
        std::cout << "Available transmissions: Automatic, Manual" << std::endl;
        if (std::string transmission = readLineTrimmed("Enter transmission (Automatic/Manual): ");
            transmission == "Automatic" || transmission == "Manual") {
            return transmission;
        }
        std::cout << "Invalid transmission. Please enter 'Automatic' or 'Manual'." << std::endl;
    }
}

