#pragma once 
#include <iostream>
#include <vector>

#include "Employee.h"
#include "ITransferLog.h"
#include "UserLoginFile.h"
#include "IEmployeeRepo.h"


class EmployeeManager {
    IEmployeeRepo& _repo;

public:
    EmployeeManager(IEmployeeRepo& repo) : _repo(repo) {}
    bool addNew(const Employee& employee) {
        return _repo.add(employee);
    }
    bool update(const Employee& employee) {
        return _repo.update(employee);
    }
    bool remove(const Employee& employee) {
        return _repo.remove(employee.getUserName());
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