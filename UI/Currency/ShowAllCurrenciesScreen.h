#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Screen.h"
#include "CurrencyManager.h"

using namespace std;

class ShowAllCurrenciesScreen : protected Screen
{
	CurrencyManager& _manager;

	// ─── Console Color Helpers ───────────────────────────────────
	HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	void _SetColor(int color) {
		SetConsoleTextAttribute(_hConsole, color);
	}

	void _ResetColor() {
		SetConsoleTextAttribute(_hConsole, 7); // Default: White on Black
	}

	// Color Constants
	enum enColor {
		DARK_BLUE    = 1,
		GREEN        = 2,
		CYAN         = 3,
		RED          = 4,
		PURPLE       = 5,
		YELLOW       = 6,
		WHITE        = 7,
		GREY         = 8,
		LIGHT_BLUE   = 9,
		LIGHT_GREEN  = 10,
		LIGHT_CYAN   = 11,
		LIGHT_RED    = 12,
		LIGHT_PURPLE = 13,
		LIGHT_YELLOW = 14,
		BRIGHT_WHITE = 15,
	};

	// ─── Table Layout Constants ──────────────────────────────────
	static const short COL_COUNTRY  = 28;
	static const short COL_CURRENCY = 28;
	static const short COL_CODE     = 12;
	static const short COL_RATE     = 18;
	static const short TABLE_WIDTH  = COL_COUNTRY + COL_CURRENCY + COL_CODE + COL_RATE + 9; // +9 for separators "| " x5

	// ─── Table Drawing Methods ───────────────────────────────────
	void _PrintHorizontalLine(char ch = '-') {
		_SetColor(CYAN);

		_PrintStartBlank();
		cout << setw(TABLE_WIDTH) << setfill(ch) << ch << setfill(' ') << endl;
		_ResetColor();
	}

	void _PrintTableHeader() {
		_PrintHorizontalLine('=');

		// Column headers
		_SetColor(YELLOW);
		_PrintStartBlank();
		cout << left
			 << "| " << setw(COL_COUNTRY)  << "Country"
			 << "| " << setw(COL_CURRENCY) << "Currency Name"
			 << "| " << setw(COL_CODE)     << "Code"
			 << "| " << setw(COL_RATE)     << "Rate / 1 USD"
			 << "|" << endl;
		_ResetColor();

		_PrintHorizontalLine('=');
	}

	void _PrintCurrencyRow(const CurrencyRecord& currency) {
		_PrintStartBlank();

		cout << left;

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		_SetColor(LIGHT_CYAN);
		cout << setw(COL_COUNTRY) << currency.countryName;

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		cout << setw(COL_CURRENCY) << currency.currencyName;

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		_SetColor(LIGHT_GREEN);
		cout << setw(COL_CODE) << currency.currencyCode;

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		_SetColor(BRIGHT_WHITE);
		cout << setw(COL_RATE) << fixed << setprecision(4) << currency.currencyExchangeDollar;

		_SetColor(YELLOW); cout << "|" << endl;
		_ResetColor();
	}

	void _PrintPageHeader(short currencyCount) {
		showGlobalScreen("Currencies List (" + to_string(currencyCount) + ") Currency(s)");
		cout << endl;
	}

	void _PrintFooter() {
		_PrintHorizontalLine('=');
		_SetColor(GREY);
		cout << right << setw(TABLE_WIDTH) << "End of List" << endl;
		_ResetColor();
	}

	void _PrintEmptyMessage() {
		_SetColor(LIGHT_RED);
		cout << "\n" << setw(50) << ' ' << ">> No Currencies Found! <<" << endl;
		_ResetColor();
	}

	// ─── Main Logic ──────────────────────────────────────────────
	void _ShowList() {
		vector<CurrencyRecord> currencies{ _manager.loadAllCurrencies() };

		_PrintPageHeader(static_cast<short>(currencies.size()));

		if (currencies.empty()) {
			_PrintEmptyMessage();
			return;
		}

		_PrintTableHeader();

		for (short i = 0; i < static_cast<short>(currencies.size()); i++) {
			_PrintCurrencyRow(currencies.at(i));
		}

		_PrintFooter();
	}

public:
	ShowAllCurrenciesScreen(CurrencyManager& manager) : _manager(manager) {}

	void show() {
		_ShowList();
	}
};