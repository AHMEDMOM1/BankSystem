#pragma once 

#include <vector>

#include "IClientRepo.h"
#include "Client.h"

class ClientManager {
    IClientRepo& _repo;

public:
    ClientManager(IClientRepo& repo) : _repo(repo) {}
    bool addNew(const Client& client) {
        if(_repo.existAccount(client.getAccountNumber())) 
            return false;
        
        return _repo.add(client);
    }
    bool update(const Client& client) {
        if (!_repo.existAccount(client.getAccountNumber()))
            return false;
        return _repo.update(client);
    }
    bool remove(const std::string& account) {
        if (!_repo.existAccount(account))
            return false;
        return _repo.remove(account);
    }
    Client find(const std::string& account) {
        return _repo.find(account);
    }

    bool existAccount(const std::string& account) {
        return _repo.existAccount(account);
    }
    
    std::vector<Client> loadAll() {
        return _repo.getAll();
    }

    double getTotalBalance() {
        vector<Client>clients{ loadAll() };
        double totalBalance{};

        if (!clients.empty()) {
            for (Client client : clients) {
                totalBalance += client.getBalance();
            }
        }

        return totalBalance;
    }

    bool transfre(Client& fromClient, Client& toClient, const double& amount) {

        fromClient.setBalance(fromClient.getBalance() - amount);
        toClient.setBalance(toClient.getBalance() + amount);

        return update(fromClient) && update(toClient);
    }

};