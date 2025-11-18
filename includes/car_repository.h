#pragma once

#include <vector>
#include <string>
#include "car.h"

class CarRepository {
private:
    std::vector<Car> cars;
    std::string dataPath;

public:
    CarRepository(const std::string& dataPath = "");
    
    const std::vector<Car>& getAll() const;
    bool add(const Car& car);
    bool update(size_t index, const Car& car);
    bool remove(size_t index);
    Car* findByIndex(size_t index);
    const Car* findByIndex(size_t index) const;
    
    bool loadFromFile();
    bool saveToFile() const;
    
    std::vector<Car> searchByBrand(const std::string& brand) const;
    std::vector<Car> searchByModel(const std::string& model) const;
    std::vector<Car> searchByPriceRange(double minPrice, double maxPrice) const;
    std::vector<Car> searchByColor(const std::string& color) const;
    std::vector<Car> searchByHorsepower(int minHp, int maxHp) const;
    std::vector<Car> searchByTransmission(const std::string& transmission) const;
};

