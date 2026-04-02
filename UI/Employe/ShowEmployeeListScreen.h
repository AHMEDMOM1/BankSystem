#pragma once
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Screen.h"
#include "clsUtil.h"
#include "Employee.h"
#include "EmployeeManager.h"

using namespace std;

class ShowEmployeeListScreen : protected Screen
{
	EmployeeManager& _manager;

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
		DARK_BLUE = 1,
		GREEN = 2,
		CYAN = 3,
		RED = 4,
		PURPLE = 5,
		YELLOW = 6,
		WHITE = 7,
		GREY = 8,
		LIGHT_BLUE = 9,
		LIGHT_GREEN = 10,
		LIGHT_CYAN = 11,
		LIGHT_RED = 12,
		LIGHT_PURPLE = 13,
		LIGHT_YELLOW = 14,
		BRIGHT_WHITE = 15,
		// Background colors (add 16 * bg_color)
		WHITE_ON_DARK_BLUE = 15 | (1 << 4),  // Bright White text on Dark Blue bg
		BLACK_ON_CYAN = 0 | (3 << 4),   // Black text on Cyan bg
		BLACK_ON_WHITE = 0 | (7 << 4),   // Black text on White bg
		YELLOW_ON_DARK_BLUE = 14 | (1 << 4),   // Yellow text on Dark Blue bg
	};

	// ─── Table Layout Constants ──────────────────────────────────
	static const short COL_USERNAME = 16;
	static const short COL_NAME = 24;
	static const short COL_PHONE = 14;
	static const short COL_EMAIL = 28;
	static const short COL_PASSWORD = 12;
	static const short COL_PERMISSIONS = 12;
	static const short TABLE_WIDTH = COL_USERNAME + COL_NAME + COL_PHONE + COL_EMAIL + COL_PASSWORD + COL_PERMISSIONS + 13; // +13 for separators

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
			<< "| " << setw(COL_USERNAME) << "Username"
			<< "| " << setw(COL_NAME) << "Employee Name"
			<< "| " << setw(COL_PHONE) << "Phone"
			<< "| " << setw(COL_EMAIL) << "Email"
			<< "| " << setw(COL_PASSWORD) << "Password"
			<< "| " << setw(COL_PERMISSIONS) << "Permissions"
			<< '|' << endl;
		_ResetColor();

		// Header bottom border
		_PrintHorizontalLine('=');
	}

	void _PrintEmployeeRow(const Employee& employee) {

		cout << left;

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		cout << setw(COL_USERNAME) << employee.getUserName();

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		cout << setw(COL_NAME) << (employee.getName() + " " + employee.getSurName());

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		cout << setw(COL_PHONE) << employee.getPhoneNumber();

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		cout << setw(COL_EMAIL) << employee.getEmail();

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		// printing masked password for better visual security representation
		cout << setw(COL_PASSWORD) << string(employee.getPassword().length(), '*');

		_SetColor(YELLOW); cout << "| "; _ResetColor();
		cout << setw(COL_PERMISSIONS) << employee.getPermissions();

		_SetColor(YELLOW); cout << '|' << endl;
		_ResetColor();
	}

	void _PrintPageHeader(short employeeCount) {
		showGlobalScreen("Employee List (" + to_string(employeeCount) + ") Employee(s)");
		cout << endl;
	}


	void _PrintFooter() {
		_PrintHorizontalLine('=');

		// End of List
		_SetColor(GREY);
		cout << right << setw(TABLE_WIDTH) << "End of List" << endl;
		_ResetColor();
	}

	void _PrintEmptyMessage() {
		_SetColor(LIGHT_RED);
		cout << "\n" << setw(50) << ' ' << ">> No Employees Found! <<" << endl;
		_ResetColor();
	}

	// ─── Main Logic ──────────────────────────────────────────────
	void _ShowList() {
		vector<Employee> employees{ _manager.loadAll() };

		_PrintPageHeader(static_cast<short>(employees.size()));

		if (employees.empty()) {
			_PrintEmptyMessage();
			return;
		}

		_PrintTableHeader();

		for (short i = 0; i < static_cast<short>(employees.size()); i++) {
			_PrintEmployeeRow(employees.at(i));
		}
		
		_PrintFooter();
	}

public:
	ShowEmployeeListScreen(EmployeeManager& manager) : _manager(manager) {}

	void show() {

		_ShowList();
	}
};
