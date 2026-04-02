#pragma once 
#include <vector>

#include "Employee.h"


class IEmployeeRepo{
public:
    virtual ~IEmployeeRepo() = default;
    virtual bool add(const Employee& Employee) = 0;
    virtual bool update(const Employee& Employee) = 0;  
    virtual bool remove(const std::string& account) = 0; 
    virtual bool isExistAccount(const std::string& account) = 0;
    virtual Employee find(const std::string& accountNumber) = 0; 
    virtual std::vector<Employee> getAll() = 0; 
};