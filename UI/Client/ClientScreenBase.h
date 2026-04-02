// UI/Client/ClientScreenBase.h
#pragma once
#include <iomanip>
#include <iostream>
#include <algorithm>

#include "Screen.h"
#include "Client.h"
#include "ClientManager.h"
#include "clsInputValidate.h"

using namespace std;

class ClientScreenBase : protected Screen {
    protected:

    ClientManager& _manager;
    ClientScreenBase(ClientManager& manager) : _manager(manager) {}

    // ─── Shared: Print Client Card ───────────────────
    void _Print(const Client& client) {
        short accountLength{ static_cast<short>(client.getAccountNumber().length()) };
        cout << setw(30) << ' ' << setw(30 - (accountLength / 2)) << setfill('-') << '-' << client.getAccountNumber() << setw(30 - (accountLength / 2)) << setfill('-') << '-' << setfill(' ') << endl;
        cout << setw(30) << ' ' << setw(5) << left << "Name:" << setw(7) << left << client.getName() << setw(32) << ' ' << "Last Name: " << client.getSurName() << endl;
        cout << setw(30) << ' ' << setw(6) << left << "Email:" << setw(30) << left << client.getEmail() << setw(9) << ' ' << "Pin Code " << client.getPinCode() << endl;
        cout << setw(30) << ' ' << setw(6) << left << "Phone:" << setw(11) << left << client.getPhoneNumber() << setw(28) << ' ' << "Balance: " << client.getBalance() << endl;
        cout << setw(30) << ' ' << setw(60) << setfill('-') << '-' << setfill(' ') << endl;
    }

    // ─── Shared: Yes/No Question ─────────────────────
    bool _RequestRepetition(const string& message) {
        cout << setw(30) << ' ';
        string rep{ clsInputValidate::ReadString(message) };
        transform(rep.begin(), rep.end(), rep.begin(), ::tolower);
        return rep == "yes" || rep == "y";
    }

    // ─── Shared: Try Another Account? ────────────────
    bool _WantsToTryAnotherAccount() {
        return _RequestRepetition("\n" + string(30, ' ') + "Try another account? (Y/N): ");
    }

    // ─── Shared: Fill Client Info ────────────────────
    void _FillInfo(Client& client) {
        cout << setw(30) << ' '; client.setName(clsInputValidate::ReadString("Enter Name: "));
        cout << setw(30) << ' '; client.setSurName(clsInputValidate::ReadString("Enter lastName: "));
        cout << setw(30) << ' '; client.setPhoneNumber(clsInputValidate::ReadString("Enter Phone: "));
        cout << setw(30) << ' '; client.setEmail(clsInputValidate::ReadString("Enter Email: "));
        cout << setw(30) << ' '; client.setPinCode(static_cast<short>(clsInputValidate::ReadIntNumber("Enter Pin Code: ")));
        cout << setw(30) << ' '; client.setBalance(clsInputValidate::ReadDblNumber("Enter Balance: "));
    }

    // ─── Shared: Try Find Existing Account ───────────
    bool _TryExistAccount(string& account) {
        do {
            cout << setw(30) << ' ';
            account = clsInputValidate::ReadString("Enter Existing Account: ");
            if (_manager.existAccount(account))
                return true;
            cout << setw(30) << ' ' << "--> Error: Account Not Found!\n";
        } while (_WantsToTryAnotherAccount());
        return false;
    }

    // ─── Shared: Get Existing Client ─────────────────
    Client _GetClient() {
        string account{};
        if (_TryExistAccount(account))
            return _manager.find(account);
        return Client();
    }
    // ─── Shared: Confirm Action ──────────────────────
    bool _ConfirmAction(const string& message = "Are You Sure (Yes/No): ") {
        cout << setw(30) << ' ';
        string request{ clsInputValidate::ReadString(message) };
        transform(request.begin(), request.end(), request.begin(), ::tolower);
        return request == "yes";
    }

};
