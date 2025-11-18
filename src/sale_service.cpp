#include "sale_service.h"
#include <QtGlobal>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "car.h"

double SaleService::calculateDiscountForSale(const Client& client, const Car& car, const std::vector<Sale>& previousSales) {
    Q_UNUSED(car);
    double discount = 0.0;
    if (isFirstTimeBuyer(client, previousSales)) {
        discount += 10.0;
    }
    if (isReturningClient(client, previousSales)) {
        discount += 5.0;
    }
    if (isWinterMonth()) {
        discount += 7.0;
    }
    return discount;
}

bool SaleService::isFirstTimeBuyer(const Client& client, const std::vector<Sale>& previousSales) {
    for (const auto& sale : previousSales) {
        if (sale.getClient().getFullName() == client.getFullName()) {
            return false;
        }
    }
    return true;
}

bool SaleService::isReturningClient(const Client& client, const std::vector<Sale>& previousSales) {
    int purchaseCount = 0;
    for (const auto& sale : previousSales) {
        if (sale.getClient().getFullName() == client.getFullName()) {
            purchaseCount++;
        }
    }
    return purchaseCount >= 2;
}

bool SaleService::isWinterMonth() {
    time_t t = time(0);
    tm* now = localtime(&t);
    int month = now->tm_mon + 1;
    return month == 12 || month == 1 || month == 2;
}

std::string SaleService::getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
    return ss.str();
}

