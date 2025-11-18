#pragma once

#include <string>
#include <map>
#include <set>

class CarValidator {
public:
    static const std::map<std::string, std::set<std::string, std::less<>>, std::less<>>& getValidBrandsAndModels();
    static bool isValidBrand(const std::string& brand);
    static bool isValidModelForBrand(const std::string& brand, const std::string& model);
    static std::string getValidBrandInput();
    static std::string getValidModelInput(const std::string& brand);
    static std::string getValidColorInput();
    static std::string getValidTransmissionInput();
};

