#pragma once

#include <vector>
#include <string>
#include <string_view>
#include "car.h"

class CarRepository {
private:
    std::vector<Car> cars;
    std::string dataPath;

public:
    explicit CarRepository(const std::string& dataPath = "");
    
    const std::vector<Car>& getAll() const;
    bool add(const Car& car);
    bool update(size_t index, const Car& car);
    bool remove(size_t index);
    Car* findByIndex(size_t index);
    const Car* findByIndex(size_t index) const;
    
    bool loadFromFile();
    bool saveToFile() const;
    
    std::vector<Car> searchByBrand(std::string_view brand) const;
    std::vector<Car> searchByModel(std::string_view model) const;
    std::vector<Car> searchByPriceRange(double minPrice, double maxPrice) const;
    std::vector<Car> searchByColor(std::string_view color) const;
    std::vector<Car> searchByHorsepower(int minHp, int maxHp) const;
    std::vector<Car> searchByTransmission(std::string_view transmission) const;
};

