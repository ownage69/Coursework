#pragma once
#include <string>
#include <string_view>
#include <vector>
#include "car.h"
#include "client.h"

class Sale {
private:
    Car car;
    Client client;
    std::string date;
    double originalPrice;
    double finalPrice;
    double discount1;
    double discount2;

public:
    Sale();
    Sale(const Car& car, const Client& client, const std::string& date, double originalPrice, double finalPrice, double discount1, double discount2);
    
    Car getCar() const;
    Client getClient() const;
    std::string getDate() const;
    double getOriginalPrice() const;
    double getFinalPrice() const;
    double getDiscountPercentage() const {
        return discount1 + discount2;
    }
    
    void setCar(const Car& newCar);
    void setClient(const Client& newClient);
    void setDate(std::string_view newDate);
    void setOriginalPrice(double newOriginalPrice);
    void setFinalPrice(double newFinalPrice);
    void setDiscount1(double newDiscount1);
    void setDiscount2(double newDiscount2);
    
    void display() const;
    std::string toString() const;
    static Sale fromString(const std::string& data);
    
    static double calculateDiscount(const Client& client, std::string_view date, const std::vector<Sale>& previousSales);
    static bool isWinterMonth();
    static bool isFirstTimeBuyer(const Client& client, const std::vector<Sale>& previousSales);
    static bool isReturningClient(const Client& client, const std::vector<Sale>& previousSales);
};