#pragma once
#include <vector>
#include <string>
#include "car.h"
#include "client.h"
#include "sale.h"
#include <QCoreApplication>

class DealershipManager {
private:
    std::vector<Car> cars;
    std::vector<Client> clients;
    std::vector<Sale> sales;
    bool dataLoaded;
    
    std::string getCurrentDate() const;

public:
    DealershipManager();
    
    const std::vector<Car>& getCars() const;
    const std::vector<Client>& getClients() const;
    const std::vector<Sale>& getSales() const;
    
    bool addCar(Car car);
    bool addClient(Client client);
    bool addSale(Sale sale);
    
    bool makeSale(size_t carIndex, size_t clientIndex, double originalPrice, double finalPrice, double discount);
    bool makeSaleWithCar(const Car& carWithOptions, size_t carIndex, size_t clientIndex, double originalPrice, double finalPrice, double discount);
    
    double calculateDiscountForSale(const Client& client, const Car& car) const;
    
    bool loadData();
    bool saveData();
    
    bool loadDataFromFiles();
    bool saveDataToFiles();
    
    int getTotalCarsInStock() const;
    int getTotalUniqueModels() const;
    
    bool clearData();
    
    bool reserveCar(size_t carIndex, size_t clientIndex);
    bool unreserveCar(const std::string& vin);
    bool editCar(size_t index, const Car& newCar);
    bool deleteCar(size_t index);
    bool deleteClient(size_t index);
    bool deleteSale(size_t index);
    
    std::vector<Car> searchCarsByBrand(const std::string& brand) const;
    std::vector<Car> searchCarsByModel(const std::string& model) const;
    std::vector<Car> searchCarsByPriceRange(double minPrice, double maxPrice) const;
    std::vector<Car> searchCarsByColor(const std::string& color) const;
    std::vector<Car> searchCarsByHorsepower(int minHp, int maxHp) const;
    std::vector<Car> searchCarsByTransmission(const std::string& transmission) const;
};