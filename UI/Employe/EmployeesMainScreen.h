#pragma once

#include <iostream>

#include "Screen.h"
#include "EmployeeManager.h"
#include "AddEmployeeScreen.h"
#include "FindEmployeeScreen.h"
#include "UpdateEmployeeScreen.h"
#include "DeleteEmployeeScreen.h"
#include "ShowEmployeeListScreen.h"
#include "ShowLoginRegisterScreen.h"

class EmployeesMainScreen : protected Screen {
	EmployeeManager& _manager;

    enum enChoise { Add = 1, Delete, Update, Find, ShowList, LoginRegister, Back } _choise{};
    void _PrintBody() {
        _PrintStartBlank(30); cout << '[' << Add << ']' << ".Add Employee" << endl;
        _PrintStartBlank(30); cout << '[' << Delete << ']' << ".Delete Employee" << endl;
        _PrintStartBlank(30); cout << '[' << Update << ']' << ".Update Employee" << endl;
        _PrintStartBlank(30); cout << '[' << Find << ']' << ".Find Employee" << endl;
        _PrintStartBlank(30); cout << '[' << ShowList << ']' << ".Show List Employees" << endl;
        _PrintStartBlank(30); cout << '[' << LoginRegister << ']' << ".Login Register" << endl;
		_PrintStartBlank(30); cout << '[' << Back << ']' << ".Main Screen" << endl;
        _PrintStartBlank(30); cout << "------------" << '\n';
    }
	void _PrintEmployeeMainScreen(const std::string& userName) {
		showGlobalScreen("Employees Main Screen (" + userName + ')');
		_PrintBody();
	}

	enChoise getChoise() {
		short choise{};
		_PrintStartBlank(30); cout << "Enter Choise: ";
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
		case LoginRegister: {
			ShowLoginRegisterScreen loginRegScreen;
			loginRegScreen.show(user);
			break;
		}
		case Back:
			return;
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

		do {
			system("cls");
			_PrintEmployeeMainScreen(user.getEmployee().getUserName());
			_choise = getChoise();

			system("cls");

			_DirectToScreen(_choise, user);

			if (_choise >= Back)
				break;

			system("pause");

		} while (true);
	}
};