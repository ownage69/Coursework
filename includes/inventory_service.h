#pragma once

#include <vector>
#include "car.h"

class InventoryService {
public:
    static int getTotalCarsInStock(const std::vector<Car>& cars);
    static int getTotalUniqueModels(const std::vector<Car>& cars);
};

