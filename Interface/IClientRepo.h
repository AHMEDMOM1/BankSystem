#pragma once 
#include <vector>

#include "Client.h"


class IClientRepo{
public:
    virtual ~IClientRepo() = default;
    virtual bool add(const Client& client) = 0;
    virtual bool update(const Client& clients) = 0;  
    virtual bool remove(const std::string& account) = 0; 
    virtual Client find(const std::string& accountNumber) = 0; 
    virtual bool existAccount(const std::string& account) = 0;
    virtual std::vector<Client> getAll() = 0; 
};