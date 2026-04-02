#pragma once 
#include <iostream>
#include <vector>

#include "IEmployeeRepo.h"
#include "Employee.h"

class EmployeeManager {
    IEmployeeRepo& _repo;
public:
    EmployeeManager(IEmployeeRepo& repo) : _repo(repo) {}
    bool addNew(const Employee& employee) {
        if (!_repo.isExistAccount(employee.getUserName()))
            return _repo.add(employee);
        return false;
    }
    bool update(const Employee& employee) {
        if (_repo.isExistAccount(employee.getUserName()))
            return _repo.update(employee);
        return false;
    }
    bool remove(const Employee& employee) {
        if(_repo.isExistAccount(employee.getUserName()))
            return _repo.remove(employee.getUserName());
        return false;
    }
    bool isExistAccount(const std::string& account) {
        return _repo.isExistAccount(account);
    }
    Employee find(const std::string& account) {
        return _repo.find(account);
    }
    std::vector<Employee> loadAll() {
        return _repo.getAll();
    }

};