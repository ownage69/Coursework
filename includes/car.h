#pragma once
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <string_view>

class Car {
private:
    std::string brand;
    std::string model;
    int year;
    double price;
    std::string color;
    int horsepower;
    std::string transmission;
    bool reserved{false};
    std::string reservedBy;
    int stock;
    std::string vin;
    std::string imagePath{":/images/default_car.png"};
    std::map<std::string, double, std::less<>> options;

public:
    Car();

    struct CarSpec {
        std::string brand;
        std::string model;
        int year;
        double price;
        std::string color;
        int horsepower;
        std::string transmission;
        int stock;
        std::string vin;
    };
    explicit Car(const CarSpec& spec);
    
    std::string getBrand() const;
    std::string getModel() const;
    int getYear() const;
    double getPrice() const;
    std::string getColor() const;
    int getHorsepower() const;
    std::string getTransmission() const;
    bool isReserved() const;
    std::string getReservedBy() const;
    int getStock() const;
    std::string getVin() const;
    std::string getImagePath() const;
    const std::map<std::string, double, std::less<>>& getOptions() const;
    double getTotalPrice() const;
    
    void setBrand(std::string_view newBrand);
    void setModel(std::string_view newModel);
    void setYear(int year);
    void setPrice(double price);
    void setColor(std::string_view newColor);
    void setHorsepower(int horsepower);
    void setTransmission(std::string_view newTransmission);
    void setReserved(bool reserved);
    void setReservedBy(std::string_view newReservedBy);
    void setStock(int stock);
    void setVin(std::string_view newVin);
    void setImagePath(std::string_view newImagePath);
    void addOption(const std::string& option, double price);
    void removeOption(const std::string& option);
    
    void display() const;
    std::string toString() const;
    static Car fromString(const std::string& data);
    
    static std::map<std::string, double, std::less<>> getAvailableOptions();
};