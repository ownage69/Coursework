#include "sale_service.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "car.h"

double SaleService::calculateDiscountForSale(const Client& client, const Car& /*car*/, const std::vector<Sale>& previousSales) {
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
    return std::none_of(previousSales.begin(), previousSales.end(),
        [&client](const Sale& sale) {
            return sale.getClient().getFullName() == client.getFullName();
        });
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
    time_t t = time(nullptr);
    tm now{};
#ifdef _WIN32
    localtime_s(&now, &t);
#else
    localtime_r(&t, &now);
#endif
    int month = now.tm_mon + 1;
    return month == 12 || month == 1 || month == 2;
}

std::string SaleService::getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    tm timeinfo{};
#ifdef _WIN32
    localtime_s(&timeinfo, &in_time_t);
#else
    localtime_r(&in_time_t, &timeinfo);
#endif
    ss << std::put_time(&timeinfo, "%Y-%m-%d");
    return ss.str();
}

