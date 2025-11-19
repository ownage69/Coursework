#pragma once
#include <vector>
#include <string>
#include "car.h"
#include "client.h"
#include "sale.h"
#include "car_repository.h"
#include "client_repository.h"
#include "sale_repository.h"
#include "sale_service.h"
#include "inventory_service.h"
#include <QCoreApplication>
#include <string_view>

class DealershipManager {
private:
    static constexpr const char* DEFAULT_DATA_PATH = "D:/Labs/3sem/labsBSUIR3rdTerm/coursework/";
    CarRepository carRepository{DEFAULT_DATA_PATH};
    ClientRepository clientRepository{DEFAULT_DATA_PATH};
    SaleRepository saleRepository{DEFAULT_DATA_PATH};
    bool dataLoaded{false};

public:
    DealershipManager();
    
    const std::vector<Car>& getCars() const;
    const std::vector<Client>& getClients() const;
    const std::vector<Sale>& getSales() const;
    
    bool addCar(const Car& car);
    bool addClient(const Client& client);
    bool addSale(const Sale& sale);
    
    bool makeSale(size_t carIndex, size_t clientIndex, double originalPrice, double finalPrice, double discount);
    bool makeSaleWithCar(const Car& carWithOptions, size_t carIndex, size_t clientIndex, double originalPrice, double finalPrice, double discount);
    
    bool loadData();
    bool saveData() const;
    
    bool loadDataFromFiles();
    bool saveDataToFiles();
    
    int getTotalCarsInStock() const;
    int getTotalUniqueModels() const;
    
    bool clearData();
    
    bool reserveCar(size_t carIndex, size_t clientIndex);
    bool unreserveCar(std::string_view vin);
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
    
    double calculateDiscountForSale(const Client& client, const Car& car) const;
};