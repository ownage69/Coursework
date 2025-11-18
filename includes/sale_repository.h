#pragma once

#include <vector>
#include <string>
#include "sale.h"

class SaleRepository {
private:
    std::vector<Sale> sales;
    std::string dataPath;

public:
    explicit SaleRepository(const std::string& dataPath = "");
    
    const std::vector<Sale>& getAll() const;
    bool add(const Sale& sale);
    bool remove(size_t index);
    
    bool loadFromFile();
    bool saveToFile() const;
};

