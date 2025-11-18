#include "inventory_service.h"
#include <set>

int InventoryService::getTotalCarsInStock(const std::vector<Car>& cars) {
    int total = 0;
    for (const auto& car : cars) {
        total += car.getStock();
    }
    return total;
}

int InventoryService::getTotalUniqueModels(const std::vector<Car>& cars) {
    std::set<std::string> models;
    for (const auto& car : cars) {
        models.insert(car.getBrand() + " " + car.getModel());
    }
    return models.size();
}

