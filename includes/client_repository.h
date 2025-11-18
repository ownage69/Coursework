#pragma once

#include <vector>
#include <string>
#include "client.h"

class ClientRepository {
private:
    std::vector<Client> clients;
    std::string dataPath;

public:
    ClientRepository(const std::string& dataPath = "");
    
    const std::vector<Client>& getAll() const;
    bool add(const Client& client);
    bool update(size_t index, const Client& client);
    bool remove(size_t index);
    Client* findByIndex(size_t index);
    const Client* findByIndex(size_t index) const;
    
    bool loadFromFile();
    bool saveToFile() const;
};