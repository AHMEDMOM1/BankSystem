#pragma once

#include <iostream>

#include "Screen.h"
#include "EmployeeManager.h"
#include "AddEmployeeScreen.h"
#include "FindEmployeeScreen.h"
#include "UpdateEmployeeScreen.h"
#include "DeleteEmployeeScreen.h"
#include "ShowEmployeeListScreen.h"

class EmployeesMainScreen : protected Screen {
	EmployeeManager& _manager;

    enum enChoise { Add = 1, Delete, Update, Find, ShowList } _choise{};
    void _PrintBody() {
        cout << setw(30) << ' ' << '[' << Add << ']' << ". Add Employee" << endl;
        cout << setw(30) << ' ' << '[' << Delete << ']' << ". Delete Employee" << endl;
        cout << setw(30) << ' ' << '[' << Update << ']' << ". Update Employee" << endl;
        cout << setw(30) << ' ' << '[' << Find << ']' << ". Find Employee" << endl;
        cout << setw(30) << ' ' << '[' << ShowList << ']' << ". Show List Employees" << endl;
		cout << setw(30) << ' ' << "[6]. Login Screen" << endl;
        cout << setw(30) << ' ' << "------------" << '\n';
    }
	void _PrintEmployeeMainScreen(const std::string& userName) {
		showGlobalScreen("Employees Main Screen (" + userName + ')');
		_PrintBody();
	}

	enChoise getChoise() {
		short choise{};
		cout << setw(30) << ' ' << "Enter Choise: ";
		cin >> choise;
		return static_cast<enChoise>(choise);
	}

	void _DirectToScreen(const enChoise& choise, const CurrentUser& user) {
		switch (choise) {
		case Add: {
			AddEmployeeScreen addScreen(_manager);
			addScreen.show();
			break;
		}
		case Delete: {
			DeleteEmployeeScreen deleteScreen(_manager);
			deleteScreen.show();
			break;
		}
		case Update: {
			UpdateEmployeeScreen updateScreen(_manager);
			updateScreen.show();
			break;
		}
		case Find: {
			FindEmployeeScreen findScreen(_manager);
			findScreen.show();
			break;
		}
		case ShowList: {
			ShowEmployeeListScreen empList(_manager);
			empList.show();
			break;
		}
		default:
			return;
		}
	}

public:
	EmployeesMainScreen(EmployeeManager& manager) : _manager(manager) {}
	void show(const CurrentUser& user) {

		if (!CheckAccessRights(user, Employee::enPermissions::pManageUsers)) {
			system("pause");
			return;
		}
		_PrintEmployeeMainScreen(user.getEmployee().getUserName());

		do {
			system("cls");
			_PrintEmployeeMainScreen(user.getEmployee().getUserName());
			_choise = getChoise();

			system("cls");

			_DirectToScreen(_choise, user);

			if (_choise > ShowList)
				break;

			system("pause");

		} while (true);
	}
};