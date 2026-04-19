#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>

#include "Screen.h"
#include "CurrencyRecord.h"
#include "CurrencyManager.h"
#include "clsInputValidate.h"

class FindCurrencyScreen : protected Screen{
    CurrencyManager& _manager;

    enum OperationOpt { CurrencyCode = 1, CountryName } _choise{};
    void _printBody() {
        _PrintStartBlank(30); 
        std::cout << CurrencyCode << ". Search By Currency Code" << endl;

        _PrintStartBlank(30); 
        std::cout << CountryName  << ". Search By Country Name" << endl;
    }
    OperationOpt _choiseOpt() {
        short choise{};
        _PrintStartBlank(30); 
        std::cout << "------------" << endl;
        
        _PrintStartBlank(30); 
        std::cout << "Chosie: ";
        choise = static_cast<short>(clsInputValidate::ReadIntNumber(""));

        return static_cast<OperationOpt>(choise);
    }

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
        LIGHT_GREEN = 10, LIGHT_CYAN = 11, BRIGHT_WHITE = 15,
    };

    static const short CARD_WIDTH = 50;

    void _PrintCardLine(char ch = '-') {
        _SetColor(CYAN);
        _PrintStartBlank(35); std::cout << setw(CARD_WIDTH) << setfill(ch) << ch << setfill(' ') << endl;
        _ResetColor();
    }

    void _PrintCardRow(const string& label, const string& value) {
        _SetColor(CYAN);   
        _PrintStartBlank(35); 
        
        std::cout << "| ";
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
        short padding = (CARD_WIDTH - codeLen - 4) / 2; // -4 for "| " and " |"

        _SetColor(CYAN); 
        _PrintStartBlank(35); 
        
        std::cout << "| ";
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

        // ── Exchange rate with special formatting ──
        ostringstream rateStr;
        rateStr << fixed << setprecision(4) << currency.currencyExchangeDollar;
        _PrintCardRow("Rate / 1 USD:", rateStr.str());

        // ── Bottom border ──
        _PrintCardLine('=');
        cout << endl;
    }

    void _Find() {
        _printBody();

        _choise = _choiseOpt();

        switch (_choise) {
        case CurrencyCode: {
           
            _PrintStartBlank(30);
            std::string currencyCode{ clsInputValidate::ReadString("Enter Currency Code: ") };
            CurrencyRecord currency{ _manager.findByCurrencyCode(currencyCode) };

            if (currency.isEmpty()) {
                _PrintStartBlank(30);

                std::cout << "This Currency Not Found!!";
                return;
            }
            _printCurrency(currency);
            break;
        }           
        case CountryName:

            _PrintStartBlank(30);
            std::string countryName{ clsInputValidate::ReadString("Enter Country Name: ") };
            CurrencyRecord currency{ _manager.findByCountryName(countryName) };

            if (currency.isEmpty()) {
                _PrintStartBlank(30); 
                
                std::cout << "This Currency Not Found!!";
                return;
            }
            _printCurrency(currency);
            break;
        }
    }
public:
    FindCurrencyScreen(CurrencyManager& manager) : _manager(manager) {}
    void show(){
        showGlobalScreen("Find Currency Screen");
        _Find();
    }
};