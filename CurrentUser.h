#pragma once
#include <iostream>
#include "Employee.h"

class CurrentUser {
private:
    Employee _employee{};

public:
    // We tell the compiler that this function is noexcept and trivial.
    CurrentUser() = default;

    void login(const Employee& emp) {
        _employee = emp;
    }

    void logout() {
        _employee = Employee();
    }

    const Employee& getEmployee() const {
        return _employee;
    }

    bool checkAccessPermission(Employee::enPermissions permission) const {
        return _employee.checkAccessPermission(permission);
    }
};