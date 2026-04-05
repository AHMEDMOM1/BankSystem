#pragma once
#include "Person.h"

class Employee : public Person{
private:
    std::string _Username{};
    std::string _Password{};
    int _Permissions{0};

public:
    enum enPermissions {
        eAll = -1,
        pListClients   = 1,
        pAddNewClient  = 2,
        pDeleteClient  = 4,
        pUpdateClients = 8,
        pFindClient    = 16,
        pTransactions  = 32,
        pManageUsers   = 64
    };

    Employee() = default;

    Employee(const std::string& name, const std::string& surName, const std::string& phoneNumber, const std::string& email, const std::string& username, const std::string& password, int permissions = 0)
    : Person(name, surName, phoneNumber, email)
    {
        _Username = username;
        _Password = password;
        _Permissions = permissions;
    }

    void setUsername(const std::string& username) {
        _Username = username;
    }

    std::string getUserName() const{
        return _Username;
    }

    void setPassword(const std::string& password){
        _Password = password;
    }

    std::string getPassword() const{
        return _Password;
    }

    void setPermissions(int permissions){
        _Permissions = permissions;
    }

    int getPermissions() const{
        return _Permissions;
    }

    bool checkAccessPermission(enPermissions permission) const {
        if (_Permissions == enPermissions::eAll)
            return true;

        if ((permission & _Permissions) == permission)
            return true;

        return false;
    }

    bool isEmpty() {
        return _Username.empty();
    }
};