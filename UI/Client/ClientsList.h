#pragma once
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Screen.h"
#include "clsUtil.h"
#include "ClientManager.h"

using namespace std;

class ClientsList : protected Screen
{
	ClientManager& _manager;

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
		// Background colors (add 16 * bg_color)
		WHITE_ON_DARK_BLUE  = 15 | (1 << 4),  // Bright White text on Dark Blue bg
		BLACK_ON_CYAN       = 0  | (3 << 4),   // Black text on Cyan bg
		BLACK_ON_WHITE      = 0  | (7 << 4),   // Black text on White bg
		YELLOW_ON_DARK_BLUE = 14 | (1 << 4),   // Yellow text on Dark Blue bg
	};

	// ─── Table Layout Constants ──────────────────────────────────
	static const short COL_ACCOUNT  = 16;
	static const short COL_NAME     = 24;
	static const short COL_PHONE    = 14;
	static const short COL_EMAIL    = 24;
	static const short COL_PINCODE  = 10;
	static const short COL_BALANCE  = 19;
	static const short TABLE_WIDTH  = COL_ACCOUNT + COL_NAME + COL_PHONE + COL_EMAIL + COL_PINCODE + COL_BALANCE + 13; // +13 for separators

	// ─── Table Drawing Methods ───────────────────────────────────
	void _PrintHorizontalLine(char ch = '-') {
		_SetColor(CYAN);
		cout << setw(TABLE_WIDTH) << setfill(ch) << ch << setfill(' ') << endl;
		_ResetColor();
	}

	void _PrintTableHeader() {
		// Top border
		_PrintHorizontalLine('=');

		// Column headers
		_SetColor(YELLOW);
		cout << left
			 << "| " << setw(COL_ACCOUNT) << "Account Number"
			 << "| " << setw(COL_NAME)    << "Client Name"
			 << "| " << setw(COL_PHONE)   << "Phone"
			 << "| " << setw(COL_EMAIL)   << "Email"
			 << "| " << setw(COL_PINCODE) << "Pin Code"
			 << "| " << setw(COL_BALANCE) << "Balance"
			 << '|' << endl;
		_ResetColor();

		// Header bottom border
		_PrintHorizontalLine('=');
	}

	void _PrintClientRow(const Client& client) {

		cout << left;
		
		_SetColor(YELLOW); cout << "| "; _ResetColor();
		cout << setw(COL_ACCOUNT) << client.getAccountNumber();

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		cout << setw(COL_NAME)    << (client.getName() + " " + client.getSurName());

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		cout << setw(COL_PHONE)   << client.getPhoneNumber();

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		cout << setw(COL_EMAIL)   << client.getEmail();

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		cout << setw(COL_PINCODE) << client.getPinCode();

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		cout << setw(COL_BALANCE) << fixed << setprecision(2) << client.getBalance();

		_SetColor(YELLOW); cout << '|' << endl;
		_ResetColor();
	}

	void _PrintPageHeader(short clientCount) {
		showGlobalScreen("Client List (" + to_string(clientCount) + ") Client(s)");
		cout << endl;
	}

	void _PrintFooter(const double& totalBalance, const string& strTotalBalance) {
		_PrintHorizontalLine('=');

		// Total Balance line
		_SetColor(LIGHT_GREEN);
		cout << "\n\t Total Balances = ";
		_SetColor(BRIGHT_WHITE);
		cout << fixed << setprecision(2) << totalBalance << endl;

		// Text representation
		_SetColor(LIGHT_CYAN);
		cout << "\t ( " << strTotalBalance << " )" << endl;
		_ResetColor();

		// End of List
		_SetColor(GREY);
		cout << right << setw(TABLE_WIDTH) << "End of List" << endl;
		_ResetColor();
	}

	void _PrintEmptyMessage() {
		_SetColor(LIGHT_RED);
		cout << "\n" << setw(50) << ' ' << ">> No Clients Found! <<" << endl;
		_ResetColor();
	}

	// ─── Main Logic ──────────────────────────────────────────────
	void _ShowList() {
		vector<Client> clients{ _manager.loadAll() };
		double totalBalance{_manager.getTotalBalance()};
		string strTotalBalance{ clsUtil::getStringOfTotal(totalBalance) };

		_PrintPageHeader(static_cast<short>(clients.size()));

		if (clients.empty()) {
			_PrintEmptyMessage();
			return;
		}

		_PrintTableHeader();

		for (short i = 0; i < static_cast<short>(clients.size()); i++) {
			_PrintClientRow(clients.at(i));
		}

		_PrintFooter(totalBalance, strTotalBalance);
	}

public:
	ClientsList(ClientManager& manager) : _manager(manager) {}

	void show(const CurrentUser& user) {

		if (!CheckAccessRights(user, Employee::enPermissions::pListClients)) return;

		_ShowList();
	}
};
