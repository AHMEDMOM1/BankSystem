#pragma once
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Screen.h"
#include "UserLoginFile.h"

using namespace std;

class ShowLoginRegisterScreen : protected Screen
{
	// ─── Console Color Helpers ───────────────────────────────────
	HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	void _SetColor(int color) {
		SetConsoleTextAttribute(_hConsole, color);
	}

	void _ResetColor() {
		SetConsoleTextAttribute(_hConsole, 7);
	}

	// Color Constants
	enum enColor {
		CYAN         = 3,
		YELLOW       = 6,
		WHITE        = 7,
		GREY         = 8,
		LIGHT_GREEN  = 10,
		LIGHT_CYAN   = 11,
		LIGHT_RED    = 12,
		BRIGHT_WHITE = 15,
	};

	// ─── Table Layout Constants ──────────────────────────────────
	static const short COL_DATE     = 26;
	static const short COL_USERNAME = 15;
	static const short COL_PASSWORD = 15;
	static const short COL_PERMS    = 15;
	static const short TABLE_WIDTH  = COL_DATE + COL_USERNAME + COL_PASSWORD + COL_PERMS + 9; // +9 for separators

	// ─── Table Drawing Methods ───────────────────────────────────
	void _PrintHorizontalLine(char ch = '-') {
		_SetColor(CYAN);
		cout << setw(20) << ' ';
		cout << setw(TABLE_WIDTH) << setfill(ch) << ch << setfill(' ') << endl;
		_ResetColor();
	}

	void _PrintTableHeader() {
		
		_PrintHorizontalLine('=');

		_SetColor(YELLOW);
		cout << setw(20) << ' ';
		cout << left
			 << "| " << setw(COL_DATE)     << "Date / Time"
			 << "| " << setw(COL_USERNAME) << "Username"
			 << "| " << setw(COL_PASSWORD) << "Password"
			 << "| " << setw(COL_PERMS)    << "Permissions"
			 << '|' << endl;
		_ResetColor();

		_PrintHorizontalLine('=');
	}

	void _PrintRow(const LoginRecord& record) {
		cout << left;
		cout << setw(20) << ' ';

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		_SetColor(LIGHT_CYAN);
		cout << setw(COL_DATE) << record.dateTime;

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		_SetColor(BRIGHT_WHITE);
		cout << setw(COL_USERNAME) << record.userName;

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		_SetColor(GREY);
		cout << setw(COL_PASSWORD) << string(record.password.length(), '*');

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		_SetColor(LIGHT_GREEN);
		cout << setw(COL_PERMS) << record.permissions;

		_SetColor(YELLOW); cout << '|' << endl;
		_ResetColor();
	}

	void _PrintFooter(short count) {
		_PrintHorizontalLine('=');

		_SetColor(LIGHT_GREEN);
		cout << endl << setw(20) << ' ' << "Total Records = ";
		_SetColor(BRIGHT_WHITE);
		cout << count << endl;
		_ResetColor();

		_SetColor(GREY);
		cout << right << setw(30 + TABLE_WIDTH) << "End of List" << endl;
		_ResetColor();
	}

	void _PrintEmptyMessage() {
		_SetColor(LIGHT_RED);
		cout << "\n" << setw(50) << ' ' << ">> No Login Records Found! <<" << endl;
		_ResetColor();
	}

public:

	void show() {

		showGlobalScreen("Login Register");

		UserLoginFile loginFile{ "UserLog.txt" };
		vector<LoginRecord> vRecords = loginFile.getAll();

		cout << endl;

		if (vRecords.empty()) {
			_PrintEmptyMessage();
			return;
		}

		_PrintTableHeader();

		for (const LoginRecord& record : vRecords) {
			_PrintRow(record);
		}

		_PrintFooter(static_cast<short>(vRecords.size()));
	}
};
