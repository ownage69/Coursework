#pragma once
#include <string>

class Client {
private:
    std::string fullName;
    std::string phone;
    double balance;

public:
    Client();
    Client(const std::string& fullName, const std::string& phone, double balance);
    
    std::string getFullName() const;
    std::string getPhone() const;
    double getBalance() const;
    
    void setFullName(const std::string& fullName);
    void setPhone(const std::string& phone);
    void setBalance(double balance);
    
    void display() const;
    std::string toString() const;
    static Client fromString(const std::string& data);
};