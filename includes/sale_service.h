#pragma once

#include <vector>
#include <string>
#include "sale.h"
#include "client.h"

class SaleService {
public:
    static double calculateDiscountForSale(const Client& client, const Car& car, const std::vector<Sale>& previousSales);
    static bool isFirstTimeBuyer(const Client& client, const std::vector<Sale>& previousSales);
    static bool isReturningClient(const Client& client, const std::vector<Sale>& previousSales);
    static bool isWinterMonth();
    static std::string getCurrentDate();
};

