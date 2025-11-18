#pragma once
#include "dealership_manager.h"

class Menu {
private:
    DealershipManager manager;

public:
    void displayMainMenu();
    void handleAddCar();
    void handleAddClient();
    void handleMakeSale();
    void handleShowAll();
    void handleSearchCars();
    void handleSaveData();
    void handleLoadData();
    
    int getValidChoice(int min, int max);
};