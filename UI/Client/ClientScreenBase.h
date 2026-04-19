// UI/Client/ClientScreenBase.h
#pragma once
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <sstream>

#include "Screen.h"
#include "Client.h"
#include "ClientManager.h"
#include "clsInputValidate.h"

using namespace std;

class ClientScreenBase : protected Screen {
    protected:

    ClientManager& _manager;
    ClientScreenBase(ClientManager& manager) : _manager(manager) {}

    // ─── Console Color Helpers ────────────────────────
    HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    void _SetColor(int c) { SetConsoleTextAttribute(_hConsole, c); }
    void _ResetColor()    { SetConsoleTextAttribute(_hConsole, 7); }
    enum enCardColor {
        _CYAN = 3, _YELLOW = 6, _GREY = 8,
        _LIGHT_GREEN = 10, _LIGHT_CYAN = 11, _BRIGHT_WHITE = 15
    };

    static const short CARD_W = 62; // total card width

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

    // ─── Shared: Print Client Card ───────────────────
    void _Print(const Client& client) {
        const string& acc = client.getAccountNumber();
        short accLen = static_cast<short>(acc.length());
        short pad    = (CARD_W - accLen - 4) / 2;
        cout << endl;

        // ── Header with account number ──
        _CardLine('=');
        _SetColor(_CYAN);       cout << setw(30) << ' ' << "| ";
        _SetColor(_GREY);       cout << setw(pad) << setfill('-') << '-';
        _SetColor(_LIGHT_GREEN);cout << ' ' << acc << ' ';
        _SetColor(_GREY);       cout << setw(CARD_W - pad - accLen - 6) << setfill('-') << '-';
        _SetColor(_CYAN);       cout << "|" << setfill(' ') << endl;
        _ResetColor();
        _CardLine('-');

        // ── Data rows ──
        _CardRow("Name:",     client.getName() + " " + client.getSurName());
        _CardRow("Email:",    client.getEmail());
        _CardRow("Phone:",    client.getPhoneNumber());
        _CardRow("Pin Code:", to_string(client.getPinCode()));

        ostringstream bal;
        bal << fixed << setprecision(2) << client.getBalance();
        _CardRow("Balance:",  bal.str());

        _CardLine('=');
        cout << endl;
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
    bool _TryExistAccount(string& account, const string& massage) {
        do {
            cout << setw(30) << ' ';
            account = clsInputValidate::ReadString(massage);
            if (_manager.existAccount(account))
                return true;
            cout << setw(30) << ' ' << "--> Error: Account Not Found!\n";
        } while (_WantsToTryAnotherAccount());
        return false;
    }

    // ─── Shared: Get Existing Client ─────────────────
    Client _GetClient(const string& massage = "Enter Existing Account: ") {
        string account{};
        if (_TryExistAccount(account, massage))
            return _manager.find(account);
        return Client();
    }
    // ─── Shared: Confirm Action ──────────────────────
    bool _ConfirmAction(const string& message = "Are You Sure (Yes/No): ") {
        cout << setw(30) << ' ';
        string request{ clsInputValidate::ReadString(message) };
        transform(request.begin(), request.end(), request.begin(), ::tolower);
        return request == "yes" || request == "y";
    }

};
