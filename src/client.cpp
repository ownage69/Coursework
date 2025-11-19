#include "client.h"
#include <iostream>
#include <sstream>

Client::Client() : balance(0.0) {}

Client::Client(const std::string& fullName, const std::string& phone, double balance) 
    : fullName(fullName), phone(phone), balance(balance) {}

std::string Client::getFullName() const { return fullName; }
std::string Client::getPhone() const { return phone; }
double Client::getBalance() const { return balance; }

void Client::setFullName(std::string_view newFullName) { this->fullName = std::string(newFullName); }
void Client::setPhone(std::string_view newPhone) { this->phone = std::string(newPhone); }
void Client::setBalance(double newBalance) { this->balance = newBalance; }

void Client::display() const {
    std::cout << "Full Name: " << fullName << std::endl;
    std::cout << "Phone: " << phone << std::endl;
    std::cout << "Balance: $" << balance << std::endl;
}

std::string Client::toString() const {
    return fullName + "," + phone + "," + std::to_string(balance);
}

Client Client::fromString(const std::string& data) {
    std::stringstream ss(data);
    std::string fullName;
    std::string phone;
    std::string balanceStr;
    
    std::getline(ss, fullName, ',');
    std::getline(ss, phone, ',');
    std::getline(ss, balanceStr, ',');
    
    double balance = 0.0;
    try {
        if (!balanceStr.empty()) {
            balance = std::stod(balanceStr);
        }
    } catch (const std::invalid_argument&) {
        balance = 0.0;
    } catch (const std::out_of_range&) {
        balance = 0.0;
    }
    
    return Client(fullName, phone, balance);
}