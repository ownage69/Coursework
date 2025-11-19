#include "client.h"
#include <iostream>
#include <sstream>

Client::Client() : balance(0.0) {}

Client::Client(const std::string& fullName, const std::string& phone, double balance) 
    : fullName(fullName), phone(phone), balance(balance) {}

std::string Client::getFullName() const { return fullName; }
std::string Client::getPhone() const { return phone; }
double Client::getBalance() const { return balance; }

void Client::setFullName(const std::string& fullName) { this->fullName = fullName; }
void Client::setPhone(const std::string& phone) { this->phone = phone; }
void Client::setBalance(double balance) { this->balance = balance; }

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
    std::string fullName, phone, balanceStr;
    
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