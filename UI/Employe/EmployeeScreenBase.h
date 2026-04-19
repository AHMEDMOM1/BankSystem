#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

#include "Employee.h"
#include "Screen.h"
#include "EmployeeManager.h"
#include "clsInputValidate.h"

class EmployeeScreenBase : protected Screen
{
protected:
	EmployeeManager& _employeeManager;
	
    // ─── Console Color Helpers ────────────────────────
    HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    void _SetColor(int c) { SetConsoleTextAttribute(_hConsole, c); }
    void _ResetColor()    { SetConsoleTextAttribute(_hConsole, 7); }
    enum enCardColor {
        _CYAN = 3, _YELLOW = 6, _GREY = 8,
        _LIGHT_GREEN = 10, _LIGHT_CYAN = 11, _BRIGHT_WHITE = 15
    };

    static const short CARD_W = 62;

    void _CardLine(char ch = '-') {
        _SetColor(_CYAN);
        cout << setw(30) << ' ' << setw(CARD_W) << setfill(ch) << ch << setfill(' ') << endl;
        _ResetColor();
    }

    void _CardRow(const string& label, const string& value) {
        _SetColor(_CYAN);        cout << setw(30) << ' ' << "| ";
        _SetColor(_YELLOW);      cout << left << setw(14) << label;
        _SetColor(_BRIGHT_WHITE);cout << setw(CARD_W - 18) << value;
        _SetColor(_CYAN);        cout << "|" << endl;
        _ResetColor();
    }

    // ─── Shared: Print Employee Card ───────────────────
    void _Print(const Employee& employee) {
        const string& uname = employee.getUserName();
        short uLen = static_cast<short>(uname.length());
        short pad  = (CARD_W - uLen - 4) / 2;
        cout << endl;

        // ── Header with username ──
        _CardLine('=');
        _SetColor(_CYAN);       cout << setw(30) << ' ' << "| ";
        _SetColor(_GREY);       cout << setw(pad) << setfill('-') << '-';
        _SetColor(_LIGHT_GREEN);cout << ' ' << uname << ' ';
        _SetColor(_GREY);       cout << setw(CARD_W - pad - uLen - 6) << setfill('-') << '-';
        _SetColor(_CYAN);       cout << "|" << setfill(' ') << endl;
        _ResetColor();
        _CardLine('-');

        // ── Data rows ──
        _CardRow("Name:",     employee.getName() + " " + employee.getSurName());
        _CardRow("Email:",    employee.getEmail());
        _CardRow("Phone:",    employee.getPhoneNumber());
        _CardRow("Password:", employee.getPassword());
        _CardRow("Permissions:", to_string(employee.getPermissions()));

        _CardLine('=');
        cout << endl;
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
