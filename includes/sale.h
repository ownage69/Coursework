#pragma once
#include <string>
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
    Sale(Car car, Client client, std::string date, double originalPrice, double finalPrice, double discount1, double discount2);
    
    Car getCar() const;
    Client getClient() const;
    std::string getDate() const;
    double getOriginalPrice() const;
    double getFinalPrice() const;
    double getDiscountPercentage() const {
        return discount1 + discount2;
    }
    
    void setCar(Car car);
    void setClient(Client client);
    void setDate(std::string date);
    void setOriginalPrice(double originalPrice);
    void setFinalPrice(double finalPrice);
    void setDiscount1(double discount1);
    void setDiscount2(double discount2);
    
    void display() const;
    std::string toString() const;
    static Sale fromString(std::string data);
    
    static double calculateDiscount(const Client& client, const std::string& date, const std::vector<Sale>& previousSales);
    static bool isWinterMonth();
    static bool isFirstTimeBuyer(const Client& client, const std::vector<Sale>& previousSales);
    static bool isReturningClient(const Client& client, const std::vector<Sale>& previousSales);
};