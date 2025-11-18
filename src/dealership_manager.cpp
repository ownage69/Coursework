#include "dealership_manager.h"
#include <QDebug>
#include <QCoreApplication>

DealershipManager::DealershipManager() {
    loadDataFromFiles();
    dataLoaded = true;
}

const std::vector<Car>& DealershipManager::getCars() const {
    return carRepository.getAll();
}

const std::vector<Client>& DealershipManager::getClients() const {
    return clientRepository.getAll();
}

const std::vector<Sale>& DealershipManager::getSales() const {
    return saleRepository.getAll();
}

bool DealershipManager::addCar(Car car) {
    return carRepository.add(car);
}

bool DealershipManager::addClient(Client client) {
    return clientRepository.add(client);
}

bool DealershipManager::addSale(Sale sale) {
    return saleRepository.add(sale);
}

bool DealershipManager::makeSale(size_t carIndex, size_t clientIndex, double originalPrice, double finalPrice, double discount) {
    auto& cars = carRepository.getAll();
    auto& clients = clientRepository.getAll();
    
    if (carIndex >= cars.size() || clientIndex >= clients.size()) {
        return false;
    }

    Car car = cars[carIndex];
    Client client = clients[clientIndex];

    if (car.getStock() <= 0 || client.getBalance() < finalPrice) {
        return false;
    }
    
    if (car.isReserved() && car.getReservedBy() != client.getFullName()) {
        return false;
    }

    client.setBalance(client.getBalance() - finalPrice);
    car.setStock(car.getStock() - 1);

    // Use the car as-is (options are already in the car object)
    Sale sale(car, client, SaleService::getCurrentDate(), originalPrice, finalPrice, discount, 0.0);
    saleRepository.add(sale);

    if (car.getStock() == 0) {
        carRepository.remove(carIndex);
    } else {
        carRepository.update(carIndex, car);
    }
    
    clientRepository.update(clientIndex, client);
    return true;
}

bool DealershipManager::makeSaleWithCar(const Car& carWithOptions, size_t carIndex, size_t clientIndex, double originalPrice, double finalPrice, double discount) {
    auto& cars = carRepository.getAll();
    auto& clients = clientRepository.getAll();
    
    if (carIndex >= cars.size() || clientIndex >= clients.size()) {
        return false;
    }

    Car car = cars[carIndex];
    Client client = clients[clientIndex];

    if (car.getStock() <= 0 || client.getBalance() < finalPrice) {
        return false;
    }
    
    if (car.isReserved() && car.getReservedBy() != client.getFullName()) {
        return false;
    }

    client.setBalance(client.getBalance() - finalPrice);
    car.setStock(car.getStock() - 1);

    // Use the car with selected options for the sale
    Sale sale(carWithOptions, client, SaleService::getCurrentDate(), originalPrice, finalPrice, discount, 0.0);
    saleRepository.add(sale);

    if (car.getStock() == 0) {
        carRepository.remove(carIndex);
    } else {
        carRepository.update(carIndex, car);
    }
    
    clientRepository.update(clientIndex, client);
    return true;
}

double DealershipManager::calculateDiscountForSale(const Client& client, const Car& car) const {
    return SaleService::calculateDiscountForSale(client, car, saleRepository.getAll());
}

bool DealershipManager::loadData() {
    dataLoaded = true;
    return loadDataFromFiles();
}

bool DealershipManager::saveData() const {
    return carRepository.saveToFile() && 
           clientRepository.saveToFile() && 
           saleRepository.saveToFile();
}

bool DealershipManager::loadDataFromFiles() {
    return carRepository.loadFromFile() && 
           clientRepository.loadFromFile() && 
           saleRepository.loadFromFile();
}

int DealershipManager::getTotalCarsInStock() const {
    return InventoryService::getTotalCarsInStock(carRepository.getAll());
}

int DealershipManager::getTotalUniqueModels() const {
    return InventoryService::getTotalUniqueModels(carRepository.getAll());
}

bool DealershipManager::clearData() {
    dataLoaded = false;
    // Note: This would require clearing repositories, but for now we'll just mark as not loaded
    return true;
}

bool DealershipManager::reserveCar(size_t carIndex, size_t clientIndex) {
    auto& cars = carRepository.getAll();
    auto& clients = clientRepository.getAll();
    
    if (carIndex >= cars.size() || clientIndex >= clients.size()) {
        return false;
    }
    Car car = cars[carIndex];
    if (car.isReserved() || car.getStock() <= 0) {
        return false;
    }
    car.setReserved(true);
    car.setReservedBy(clients[clientIndex].getFullName());
    return carRepository.update(carIndex, car);
}

bool DealershipManager::unreserveCar(const std::string& vin) {
    auto& cars = carRepository.getAll();
    for (size_t i = 0; i < cars.size(); ++i) {
        if (cars[i].getVin() == vin && cars[i].isReserved()) {
            Car car = cars[i];
            car.setReserved(false);
            return carRepository.update(i, car);
        }
    }
    return false;
}

bool DealershipManager::editCar(size_t index, const Car& newCar) {
    return carRepository.update(index, newCar);
}

bool DealershipManager::deleteCar(size_t index) {
    return carRepository.remove(index);
}

bool DealershipManager::deleteClient(size_t index) {
    return clientRepository.remove(index);
}

bool DealershipManager::deleteSale(size_t index) {
    return saleRepository.remove(index);
}

std::vector<Car> DealershipManager::searchCarsByBrand(const std::string& brand) const {
    return carRepository.searchByBrand(brand);
}

std::vector<Car> DealershipManager::searchCarsByModel(const std::string& model) const {
    return carRepository.searchByModel(model);
}

std::vector<Car> DealershipManager::searchCarsByPriceRange(double minPrice, double maxPrice) const {
    return carRepository.searchByPriceRange(minPrice, maxPrice);
}

std::vector<Car> DealershipManager::searchCarsByColor(const std::string& color) const {
    return carRepository.searchByColor(color);
}

std::vector<Car> DealershipManager::searchCarsByHorsepower(int minHp, int maxHp) const {
    return carRepository.searchByHorsepower(minHp, maxHp);
}

std::vector<Car> DealershipManager::searchCarsByTransmission(const std::string& transmission) const {
    return carRepository.searchByTransmission(transmission);
}
