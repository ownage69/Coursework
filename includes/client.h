#pragma once
#include <string>
#include <string_view>

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
    
    void setFullName(std::string_view newFullName);
    void setPhone(std::string_view newPhone);
    void setBalance(double newBalance);
    
    void display() const;
    std::string toString() const;
    static Client fromString(const std::string& data);
};