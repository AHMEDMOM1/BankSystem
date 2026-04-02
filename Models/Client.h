#pragma once

#include "Person.h"


class Client : public Person{
private:
    std::string _AccountNumber{};
    short _PinCode{};
    double _Balance{};
    
public:
    Client() = default;
    Client(const std::string& name, 
           const std::string& surName,
           const std::string& phoneNumber,
           const std::string& email,
           const std::string& accountNumber,
           const short& pinCode,
           const double balance) 
    : Person(name, surName, phoneNumber, email)
    {
        _AccountNumber = accountNumber;
        _PinCode = pinCode;
        _Balance = balance;
    }
    std::string getAccountNumber() const{
        return _AccountNumber;
    }

    void setPinCode(const short& pinCode){
        _PinCode = pinCode;
    }
    short getPinCode() const{
        return _PinCode;
    }

    void setBalance(const double& balance){
        _Balance = balance;
    }
    double getBalance() const{
        return _Balance;
    }

    bool isEmpty(){
        return _AccountNumber.empty();
    }
   
};