#include "sale.h"
#include "car_serializer.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <string_view>
#include <QtGlobal>

Sale::Sale() : originalPrice(0.0), finalPrice(0.0), discount1(0.0), discount2(0.0) {}

Sale::Sale(const Car& car, const Client& client, const std::string& date, double originalPrice, double finalPrice, double discount1, double discount2) 
    : car(car), client(client), date(date), originalPrice(originalPrice), finalPrice(finalPrice), discount1(discount1), discount2(discount2) {}

Car Sale::getCar() const { return car; }
Client Sale::getClient() const { return client; }
std::string Sale::getDate() const { return date; }
double Sale::getOriginalPrice() const { return originalPrice; }
double Sale::getFinalPrice() const { return finalPrice; }

void Sale::setCar(const Car& newCar) { this->car = newCar; }
void Sale::setClient(const Client& newClient) { this->client = newClient; }
void Sale::setDate(std::string_view newDate) { this->date = std::string(newDate); }
void Sale::setOriginalPrice(double newOriginalPrice) { this->originalPrice = newOriginalPrice; }
void Sale::setFinalPrice(double newFinalPrice) { this->finalPrice = newFinalPrice; }
void Sale::setDiscount1(double newDiscount1) { this->discount1 = newDiscount1; }
void Sale::setDiscount2(double newDiscount2) { this->discount2 = newDiscount2; }

void Sale::display() const {
    std::cout << "Sale Date: " << date << std::endl;
    car.display();
    client.display();
    std::cout << "Original Price: $" << originalPrice << std::endl;
    std::cout << "Final Price: $" << finalPrice << std::endl;
    std::cout << "Discount: " << getDiscountPercentage() << "%" << std::endl;
}

std::string Sale::toString() const {
    std::stringstream ss;
    ss << CarSerializer::toString(car) << "|" << client.toString() << "|" << date << "|" << originalPrice << "|" << finalPrice << "|" << discount1 << "|" << discount2;
    return ss.str();
}

Sale Sale::fromString(const std::string& data) {
    std::stringstream ss(data);
    std::string part;
    std::vector<std::string> parts;
    while (std::getline(ss, part, '|')) {
        parts.push_back(part);
    }
    if (parts.size() == 6) {
        // Old format: car|client|date|price|discount1|discount2
        Car car = CarSerializer::fromString(parts[0]);
        Client client = Client::fromString(parts[1]);
        std::string date = parts[2];
        double price = std::stod(parts[3]);
        double discount1 = std::stod(parts[4]);
        double discount2 = std::stod(parts[5]);
        return Sale(car, client, date, price, price, discount1, discount2);  // Assume original = final
    } else if (parts.size() == 7) {
        // New format: car|client|date|originalPrice|finalPrice|discount1|discount2
        Car car = CarSerializer::fromString(parts[0]);
        Client client = Client::fromString(parts[1]);
        std::string date = parts[2];
        double originalPrice = std::stod(parts[3]);
        double finalPrice = std::stod(parts[4]);
        double discount1 = std::stod(parts[5]);
        double discount2 = std::stod(parts[6]);
        return Sale(car, client, date, originalPrice, finalPrice, discount1, discount2);
    } else {
        throw std::invalid_argument("Invalid sale data");
    }
}

double Sale::calculateDiscount(const Client& client, [[maybe_unused]] std::string_view date, const std::vector<Sale>& previousSales) {
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

bool Sale::isWinterMonth() {
    std::time_t t = std::time(nullptr);
    std::tm tmBuf{};
#if defined(_WIN32)
    localtime_s(&tmBuf, &t);
#else
    localtime_r(&t, &tmBuf);
#endif
    int month = tmBuf.tm_mon + 1;
    return month == 12 || month == 1 || month == 2;
}

bool Sale::isFirstTimeBuyer(const Client& client, const std::vector<Sale>& previousSales) {
    return std::none_of(previousSales.begin(), previousSales.end(),
                        [&client](const Sale& s) { return s.getClient().getFullName() == client.getFullName(); });
}

bool Sale::isReturningClient(const Client& client, const std::vector<Sale>& previousSales) {
    return std::any_of(previousSales.begin(), previousSales.end(),
                       [&client](const Sale& s) { return s.getClient().getFullName() == client.getFullName(); });
}