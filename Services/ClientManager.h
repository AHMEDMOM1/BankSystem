#pragma once 

#include <vector>

#include "ITransferLog.h"
#include "IClientRepo.h"
#include "Client.h"

class ClientManager {
    IClientRepo& _repo;
    ITransferLog& _log;

public:
    ClientManager(IClientRepo& repo, ITransferLog& log) : _repo(repo), _log(log) {}

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

    bool transfre(const CurrentUser& user, Client& sender, Client& rec, const double amount) {

        sender.setBalance(sender.getBalance() - amount);
        rec.setBalance(rec.getBalance() + amount);

        if(update(sender) && update(rec))
            return _log.recordTransferProcess(user, sender, rec, amount);
    }

};