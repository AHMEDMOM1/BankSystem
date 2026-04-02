#pragma once

#include <iostream>

#include "Employee.h"
#include "Screen.h"
#include "EmployeeManager.h"
#include "clsInputValidate.h"

class EmployeeScreenBase : protected Screen
{
protected:
	EmployeeManager& _employeeManager;
	
    // ??? Shared: Print Employee Card 
    void _Print(const Employee& Employee) {
        short accountLength{ static_cast<short>(Employee.getUserName().length()) };
        cout << setw(30) << ' ' << setw(30 - (accountLength / 2)) << setfill('-') << '-' << Employee.getUserName() << setw(30 - (accountLength / 2)) << setfill('-') << '-' << setfill(' ') << endl;
        cout << setw(30) << ' ' << setw(5) << left << "Name:" << setw(7) << left << Employee.getName() << setw(32) << ' ' << "Last Name: " << Employee.getSurName() << endl;
        cout << setw(30) << ' ' << setw(6) << left << "Email:" << setw(30) << left << Employee.getEmail() << setw(9) << ' ' << "Password " << Employee.getPassword() << endl;
        cout << setw(30) << ' ' << setw(6) << left << "Phone:" << setw(11) << left << Employee.getPhoneNumber() << setw(28) << ' ' << "Permisions: " << Employee.getPermissions() << endl;
        cout << setw(30) << ' ' << setw(60) << setfill('-') << '-' << setfill(' ') << endl;
    }

    // ??? Shared: Yes/No Question 
    bool _RequestRepetition(const string& message) {
        cout << setw(30) << ' ';
        string rep{ clsInputValidate::ReadString(message) };
        transform(rep.begin(), rep.end(), rep.begin(), ::tolower);
        return rep == "yes" || rep == "y";
    }

    // ??? Shared: Try Another Account? 
    bool _WantsToTryAnotherAccount() {
        return _RequestRepetition("\n" + string(30, ' ') + "Try another account? (Y/N): ");
    }

    // ??? Shared: Fill Employee Info 
    void _FillInfo(Employee& Employee) {
        cout << setw(30) << ' '; Employee.setName(clsInputValidate::ReadString("Name: "));
        cout << setw(30) << ' '; Employee.setSurName(clsInputValidate::ReadString("lastName: "));
        cout << setw(30) << ' '; Employee.setPhoneNumber(clsInputValidate::ReadString("Phone: "));
        cout << setw(30) << ' '; Employee.setEmail(clsInputValidate::ReadString("Email: "));
        cout << setw(30) << ' '; Employee.setPassword(clsInputValidate::ReadString(("Password: ")));
    }

    // ??? Shared: Try Find Existing Account 
    bool _TryExistAccount(string& account) {
        do {
            cout << setw(30) << ' ';
            account = clsInputValidate::ReadString("Enter Existing Account: ");

           if (_employeeManager.isExistAccount(account))
                return true;

            cout << setw(30) << ' ' << "--> Error: Account Not Found!\n";

        } while (_WantsToTryAnotherAccount());
        return false;
    }

    // ??? Shared: Get Existing Employee 
    Employee _GetUser() {
        string account{};
        if (_TryExistAccount(account))
            return _employeeManager.find(account);
        return Employee();
    }
    // ??? Shared: Confirm Action 
    bool _ConfirmAction(const string& message = "Are You Sure (Yes/No): ") {
        cout << setw(30) << ' ';
        string request{ clsInputValidate::ReadString(message) };
        transform(request.begin(), request.end(), request.begin(), ::tolower);
        return request == "yes" || request == "y";
    }
public:
    EmployeeScreenBase(EmployeeManager& Employee) : _employeeManager(Employee) {}
};
