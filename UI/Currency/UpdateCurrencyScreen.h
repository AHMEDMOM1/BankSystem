#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>

#include "clsInputValidate.h" 
#include "CurrencyManager.h"
#include "CurrencyRecord.h"
#include "Screen.h"

class UpdateCurrencyScreen : protected Screen{
    CurrencyManager& _manager;

    // ─── Console Color Helpers ───────────────────────────────────
    HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    void _SetColor(int color) {
        SetConsoleTextAttribute(_hConsole, color);
    }
    void _ResetColor() {
        SetConsoleTextAttribute(_hConsole, 7);
    }

    enum enColor {
        CYAN = 3, YELLOW = 6, WHITE = 7, GREY = 8,
        LIGHT_GREEN = 10, LIGHT_CYAN = 11, LIGHT_RED = 12, BRIGHT_WHITE = 15,
    };

    static const short CARD_WIDTH = 50;

    void _PrintStartBlank(const short blank = 30) {
        cout << setw(blank) << ' ';
    }

    void _PrintCardLine(char ch = '-') {
        _SetColor(CYAN);
        _PrintStartBlank(35); cout << setw(CARD_WIDTH) << setfill(ch) << ch << setfill(' ') << endl;
        _ResetColor();
    }

    void _PrintCardRow(const string& label, const string& value) {
        _SetColor(CYAN);
        _PrintStartBlank(35);
        cout << "| ";
        _SetColor(YELLOW);  cout << left << setw(18) << label;
        _SetColor(BRIGHT_WHITE); cout << setw(CARD_WIDTH - 22) << value;
        _SetColor(CYAN);   cout << " |" << endl;
        _ResetColor();
    }

    void _printCurrency(const CurrencyRecord& currency) {
        cout << endl;

        // ── Top border ──
        _PrintCardLine('=');

        // ── Centered currency code header ──
        short codeLen = static_cast<short>(currency.currencyCode.length());
        short padding = (CARD_WIDTH - codeLen - 4) / 2;

        _SetColor(CYAN);
        _PrintStartBlank(35);
        cout << "| ";
        _SetColor(GREY); cout << setw(padding) << setfill('-') << '-';
        _SetColor(LIGHT_GREEN); cout << ' ' << currency.currencyCode << ' ';
        _SetColor(GREY); cout << setw(CARD_WIDTH - padding - codeLen - 6) << setfill('-') << '-';
        _SetColor(CYAN); cout << " |" << setfill(' ') << endl;
        _ResetColor();

        // ── Separator ──
        _PrintCardLine('-');

        // ── Data rows ──
        _PrintCardRow("Country:", currency.countryName);
        _PrintCardRow("Currency:", currency.currencyName);
        _PrintCardRow("Code:", currency.currencyCode);

        // ── Exchange rate ──
        ostringstream rateStr;
        rateStr << fixed << setprecision(4) << currency.currencyExchangeDollar;
        _PrintCardRow("Rate / 1 USD:", rateStr.str());

        // ── Bottom border ──
        _PrintCardLine('=');
        cout << endl;
    }

    // ─── Confirm Action ──────────────────────────────────────────
    bool _askSure() {
        _PrintStartBlank(30);
        cout << "Are You Sure You Want To Update This Currency? (Yes/No): ";
        return clsInputValidate::wantToApprove();
    }

    // ─── Main Logic ──────────────────────────────────────────────
    void _update() {
        _PrintStartBlank(30);
        std::string currencyCode{ clsInputValidate::ReadString("Enter an existing currency code: ") };

        CurrencyRecord currency{ _manager.findByCurrencyCode(currencyCode) };
        if (currency.isEmpty()) {
            _PrintStartBlank(30);
            _SetColor(LIGHT_RED);
            cout << "--> Currency Not Found!!" << endl;
            _ResetColor();
            return;
        }

        // Show current currency info
        _printCurrency(currency);

        // Ask for confirmation
        if (!_askSure()) {
            _PrintStartBlank(30);
            _SetColor(GREY);
            cout << "--> Update Cancelled." << endl;
            _ResetColor();
            return;
        }

        // Read new rate
        _PrintStartBlank(30);
        double newRate{ clsInputValidate::ReadDblNumber("Enter New Rate: ") };
        currency.currencyExchangeDollar = newRate;

        // Perform update
        if (!_manager.update(currency)) {
            _PrintStartBlank(30);
            cout << "--> Error: Updating falid!!\n";
            return;
        }

        _PrintStartBlank(30);
        _SetColor(LIGHT_GREEN);
        cout << "--> Currency Rate Updated Successfully!" << endl;
        _ResetColor();

        // Print updated currency card
        _printCurrency(currency);
    }

public:
    UpdateCurrencyScreen(CurrencyManager& manager) : _manager(manager) {}

    void show(){
        showGlobalScreen("Update Currency Screen");
        _update();
    }
};