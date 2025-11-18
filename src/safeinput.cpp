#include "safeinput.h"
#include <iostream>
#include <string>
#include <regex>
#include <cctype>
#include <limits>

using std::string;
using std::cout;
using std::cin;
using std::getline;

inline void trimInPlace(string& s) {
    while (!s.empty() && isspace(static_cast<unsigned char>(s.front())))
        s.erase(s.begin());
    while (!s.empty() && isspace(static_cast<unsigned char>(s.back())))
        s.pop_back();
}

string readLineTrimmed(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    trimInPlace(input);
    return input;
}

int safeInputInt(const string& prompt) {
    std::regex pat(R"(^[+-]?\d+$)");
    while (true) {
        string input = readLineTrimmed(prompt);
        if (!input.empty() && std::regex_match(input, pat)) {
            try {
                return std::stoi(input);
            }
            catch (const std::invalid_argument&) {
                cout << "Invalid input. Please enter a valid integer.\n";
            }
            catch (const std::out_of_range&) {
                cout << "Number out of range for int. Please try again.\n";
            }
        }
        else {
            cout << "Invalid input. Please enter an integer.\n";
        }
    }
}

int safePositiveInputInt(const string& prompt) {
    while (true) {
        int number = safeInputInt(prompt);
        if (number > 0)
            return number;
        cout << "Number must be positive.\n";
    }
}

double safeInputDouble(const string& prompt) {
    std::regex pat(R"(^[+-]?\d*\.?\d+$)");
    while (true) {
        string input = readLineTrimmed(prompt);
        if (!input.empty() && std::regex_match(input, pat)) {
            try {
                return std::stod(input);
            }
            catch (const std::invalid_argument&) {
                cout << "Invalid input. Please enter a valid number.\n";
            }
            catch (const std::out_of_range&) {
                cout << "Number out of range for double. Please try again.\n";
            }
        }
        else {
            cout << "Invalid input. Please enter a number.\n";
        }
    }
}

double safePositiveInputDouble(const string& prompt) {
    while (true) {
        double number = safeInputDouble(prompt);
        if (number > 0)
            return number;
        cout << "Number must be positive.\n";
    }
}
