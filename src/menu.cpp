#include "menu.h"
#include <iostream>
#include "safeinput.h"
#include "car_validator.h"

void Menu::displayMainMenu() {
    std::cout << "\n=== Car Dealership Management System ===" << std::endl;
    std::cout << "1. Add Car" << std::endl;
    std::cout << "2. Add Client" << std::endl;
    std::cout << "3. Make a Sale" << std::endl;
    std::cout << "4. Show All Cars, Clients, and Sales" << std::endl;
    std::cout << "5. Search Cars" << std::endl;
    std::cout << "6. Save Data to Files" << std::endl;
    std::cout << "7. Load Data from Files" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void Menu::handleAddCar() {
    std::cout << "\n--- Add New Car ---" << std::endl;
    
    std::string brand = CarValidator::getValidBrandInput();
    std::string model = CarValidator::getValidModelInput(brand);
    int year = safePositiveInputInt("Enter year: ");
    double price = safePositiveInputDouble("Enter price: ");
    std::string color = CarValidator::getValidColorInput();
    int horsepower = safePositiveInputInt("Enter horsepower: ");
    std::string transmission = CarValidator::getValidTransmissionInput();
    
    Car newCar;
    newCar.setBrand(brand);
    newCar.setModel(model);
    newCar.setYear(year);
    newCar.setPrice(price);
    newCar.setColor(color);
    newCar.setHorsepower(horsepower);
    newCar.setTransmission(transmission);
    newCar.setStock(1);
    
    if (manager.addCar(newCar)) {
        std::cout << "Car added successfully!" << std::endl;
    } else {
        std::cout << "Failed to add car!" << std::endl;
    }
}

void Menu::handleAddClient() {
    std::string fullName, phone;
    double balance;
    
    std::cout << "\n--- Add New Client ---" << std::endl;
    fullName = readLineTrimmed("Enter full name: ");
    phone = readLineTrimmed("Enter phone: ");
    balance = safePositiveInputDouble("Enter balance: ");
    
    Client newClient(fullName, phone, balance);
    
    if (manager.addClient(newClient)) {
        std::cout << "Client added successfully!" << std::endl;
    } else {
        std::cout << "Failed to add client!" << std::endl;
    }
}

void Menu::handleMakeSale() {
    const auto& cars = manager.getCars();
    const auto& clients = manager.getClients();
    
    if (cars.empty()) {
        std::cout << "No cars available for sale!" << std::endl;
        return;
    }
    if (clients.empty()) {
        std::cout << "No clients available!" << std::endl;
        return;
    }
    
    std::cout << "\n--- Available Cars ---" << std::endl;
    for (size_t i = 0; i < cars.size(); ++i) {
        std::cout << i + 1 << ". " << cars[i].getBrand() << " " << cars[i].getModel() 
                  << " ($" << cars[i].getPrice() << ")" << std::endl;
    }
    
    std::cout << "\n--- Available Clients ---" << std::endl;
    for (size_t i = 0; i < clients.size(); ++i) {
        std::cout << i + 1 << ". " << clients[i].getFullName() 
                  << " ($" << clients[i].getBalance() << ")" << std::endl;
    }
    
    int carIndex = getValidChoice(1, cars.size()) - 1;
    int clientIndex = getValidChoice(1, clients.size()) - 1;
    
    if (manager.makeSale(carIndex, clientIndex)) {
        std::cout << "Sale completed successfully!" << std::endl;
    } else {
        std::cout << "Sale failed! Insufficient balance or invalid selection." << std::endl;
    }
}

void Menu::handleShowAll() {
    const auto& cars = manager.getCars();
    const auto& clients = manager.getClients();
    const auto& sales = manager.getSales();
    
    std::cout << "\n=== ALL CARS ===" << std::endl;
    if (cars.empty()) {
        std::cout << "No cars available." << std::endl;
    } else {
        for (size_t i = 0; i < cars.size(); ++i) {
            std::cout << "\nCar " << i + 1 << ":" << std::endl;
            cars[i].display();
        }
    }
    
    std::cout << "\n=== ALL CLIENTS ===" << std::endl;
    if (clients.empty()) {
        std::cout << "No clients available." << std::endl;
    } else {
        for (size_t i = 0; i < clients.size(); ++i) {
            std::cout << "\nClient " << i + 1 << ":" << std::endl;
            clients[i].display();
        }
    }
    
    std::cout << "\n=== ALL SALES ===" << std::endl;
    if (sales.empty()) {
        std::cout << "No sales available." << std::endl;
    } else {
        for (size_t i = 0; i < sales.size(); ++i) {
            std::cout << "\nSale " << i + 1 << ":" << std::endl;
            sales[i].display();
            std::cout << "------------------------" << std::endl;
        }
    }
}

void Menu::handleSearchCars() {
    std::cout << "\n--- Search Cars ---" << std::endl;
    std::cout << "1. Search by Brand" << std::endl;
    std::cout << "2. Search by Model" << std::endl;
    std::cout << "3. Search by Price Range" << std::endl;
    std::cout << "4. Search by Color" << std::endl;
    std::cout << "5. Search by Horsepower Range" << std::endl;
    std::cout << "6. Search by Transmission" << std::endl;
    
    int searchChoice = getValidChoice(1, 6);
    std::vector<Car> results;
    
    switch (searchChoice) {
        case 1: {
            std::string brand = CarValidator::getValidBrandInput();
            results = manager.searchCarsByBrand(brand);
            break;
        }
        case 2: {
            std::string model = readLineTrimmed("Enter model: ");
            results = manager.searchCarsByModel(model);
            break;
        }
        case 3: {
            double minPrice = safePositiveInputDouble("Enter minimum price: ");
            double maxPrice = safePositiveInputDouble("Enter maximum price: ");
            results = manager.searchCarsByPriceRange(minPrice, maxPrice);
            break;
        }
        case 4: {
            std::string color = CarValidator::getValidColorInput();
            results = manager.searchCarsByColor(color);
            break;
        }
        case 5: {
            int minHp = safePositiveInputInt("Enter minimum horsepower: ");
            int maxHp = safePositiveInputInt("Enter maximum horsepower: ");
            results = manager.searchCarsByHorsepower(minHp, maxHp);
            break;
        }
        case 6: {
            std::string transmission = CarValidator::getValidTransmissionInput();
            results = manager.searchCarsByTransmission(transmission);
            break;
        }
    }
    
    std::cout << "\n--- Search Results ---" << std::endl;
    if (results.empty()) {
        std::cout << "No cars found matching the criteria." << std::endl;
    } else {
        for (size_t i = 0; i < results.size(); ++i) {
            std::cout << "\nCar " << i + 1 << ":" << std::endl;
            results[i].display();
        }
    }
}

void Menu::handleSaveData() {
    if (manager.saveData()) {
        std::cout << "Data saved successfully!" << std::endl;
    } else {
        std::cout << "Failed to save data!" << std::endl;
    }
}

void Menu::handleLoadData() {
    if (manager.loadData()) {
        std::cout << "Data loaded successfully!" << std::endl;
    } else {
        std::cout << "Failed to load data!" << std::endl;
    }
}

int Menu::getValidChoice(int min, int max) {
    while (true) {
        int choice = safeInputInt("Enter choice (" + std::to_string(min) + "-" + std::to_string(max) + "): ");
        if (choice >= min && choice <= max) {
            return choice;
        }
        std::cout << "Invalid choice. Please try again." << std::endl;
    }
}