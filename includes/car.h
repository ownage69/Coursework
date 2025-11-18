#pragma once
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>

class Car {
private:
    std::string brand;
    std::string model;
    int year;
    double price;
    std::string color;
    int horsepower;
    std::string transmission;
    bool reserved;
    std::string reservedBy;
    int stock;
    std::string vin;
    std::string imagePath;
    std::map<std::string, double> options;

    static const std::map<std::string, std::set<std::string>> validBrandsAndModels;

public:
    Car();
    Car(std::string brand, std::string model, int year, double price, std::string color, int horsepower, std::string transmission, int stock, std::string vin);
    
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
    const std::map<std::string, double>& getOptions() const;
    double getTotalPrice() const;
    
    void setBrand(std::string brand);
    void setModel(std::string model);
    void setYear(int year);
    void setPrice(double price);
    void setColor(std::string color);
    void setHorsepower(int horsepower);
    void setTransmission(std::string transmission);
    void setReserved(bool reserved);
    void setReservedBy(std::string reservedBy);
    void setStock(int stock);
    void setVin(std::string vin);
    void setImagePath(std::string imagePath);
    void addOption(const std::string& option, double price);
    void removeOption(const std::string& option);
    
    void display() const;
    std::string toString() const;
    static Car fromString(std::string data);
    
    static bool isValidBrand(const std::string& brand);
    static bool isValidModelForBrand(const std::string& brand, const std::string& model);
    static std::string getValidBrandInput();
    static std::string getValidModelInput(const std::string& brand);
    static std::string getValidColorInput();
    static std::string getValidTransmissionInput();
    static const std::map<std::string, double> getAvailableOptions();
};