#pragma once

#include <string>
#include "car.h"

class CarSerializer {
public:
    static std::string toString(const Car& car);
    static Car fromString(const std::string& data);
};

