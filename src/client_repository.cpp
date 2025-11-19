#include "client_repository.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

ClientRepository::ClientRepository(const std::string& dataPath) : dataPath(dataPath) {
    if (!dataPath.empty()) {
        loadFromFile();
    }
}

const std::vector<Client>& ClientRepository::getAll() const {
    return clients;
}

bool ClientRepository::add(const Client& client) {
    clients.push_back(client);
    return saveToFile();
}

bool ClientRepository::update(size_t index, const Client& client) {
    if (index >= clients.size()) {
        return false;
    }
    clients[index] = client;
    return saveToFile();
}

bool ClientRepository::remove(size_t index) {
    if (index >= clients.size()) {
        return false;
    }
    clients.erase(clients.begin() + index);
    return saveToFile();
}

Client* ClientRepository::findByIndex(size_t index) {
    if (index >= clients.size()) {
        return nullptr;
    }
    return &clients[index];
}

const Client* ClientRepository::findByIndex(size_t index) const {
    if (index >= clients.size()) {
        return nullptr;
    }
    return &clients[index];
}

bool ClientRepository::loadFromFile() {
    if (dataPath.empty()) {
        return false;
    }
    
    clients.clear();
    if (QFile clientFile(QString::fromStdString(dataPath + "clients.txt")); clientFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&clientFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.isEmpty()) {
                try {
                    clients.push_back(Client::fromString(line.toStdString()));
                } catch (const std::invalid_argument& e) {
                    qCritical() << "Error parsing client (invalid argument): " << e.what();
                } catch (const std::out_of_range& e) {
                    qCritical() << "Error parsing client (out of range): " << e.what();
                }
            }
        }
        clientFile.close();
        return true;
    }
    return false;
}

bool ClientRepository::saveToFile() const {
    if (dataPath.empty()) {
        return false;
    }
    
    if (QFile clientFile(QString::fromStdString(dataPath + "clients.txt")); clientFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&clientFile);
        for (const auto& client : clients) {
            out << QString::fromStdString(client.toString()) << "\n";
        }
        clientFile.close();
        return true;
    }
    return false;
}

