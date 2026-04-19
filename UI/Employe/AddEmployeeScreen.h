#pragma once 
#include <iostream>

#include "EmployeeScreenBase.h"
#include "EmployeeManager.h"
#include "Employee.h"

class AddEmployeeScreen : protected EmployeeScreenBase {
	bool _WantsToAddAnotherEmployee() {
		return _RequestRepetition("\n" + string(30, ' ') + "Do you want to add another employee? (Y/N): ");
	}

	bool _TryReadNewAccount(string& account) {
		do {
			_PrintStartBlank(30);
			account = clsInputValidate::ReadString("Enter New UserName: ");
			if (!_employeeManager.isExistAccount(account)) {
				return true;
			}
			_PrintStartBlank(30); cout << "--> Error: UserName already exists!\n";

		} while (_WantsToTryAnotherAccount());
		return false;
	}

	bool _WantAllPermision() {
		_PrintStartBlank(30); cout << "Do you need give to employee All Permisions? (yes/no): ";
		return clsInputValidate::wantToApprove();
	}
	
	int _GetPermission() {
		if (_WantAllPermision())
			return -1;

		struct PermissionItem {
			string question{};
			Employee::enPermissions flag;
		};

		const vector<PermissionItem> permissions {
			{ "Give Show List? ",	  Employee::enPermissions::pListClients   },
			{ "Give Add? ",			  Employee::enPermissions::pAddNewClient  },
			{ "Give Delete? ",		  Employee::enPermissions::pDeleteClient  },
			{ "Give Update? ",		  Employee::enPermissions::pUpdateClients },
			{ "Give Find? ",		  Employee::enPermissions::pFindClient    },
			{ "Give Transaction? ",   Employee::enPermissions::pTransactions  },
			{ "Give Manager User? ",  Employee::enPermissions::pManageUsers	  }
		};

		int perm{};
		for (const auto& item : permissions) {
			_PrintStartBlank(30); cout << item.question;
			if (clsInputValidate::wantToApprove())
				perm |= static_cast<int>(item.flag);
		}

    return perm;
}

	Employee _CreateEmployee() {
		string account{};
		if (!_TryReadNewAccount(account)) {
			return Employee();
		}
		Employee employee("", "", "", "", account, "", -1);
		_FillInfo(employee);

		employee.setPermissions(_GetPermission());

		return employee;
	}

public:
	AddEmployeeScreen(EmployeeManager& manager) : EmployeeScreenBase(manager) {}
	void _Add() {
		do {
			Employee employee{ _CreateEmployee() };

			if (employee.isEmpty())
				return;

			if (_employeeManager.addNew(employee)) {
				cout << "\n" << setw(30) << ' ' << "--> Employee Added Successfully!\n";
				_Print(employee);
			}
			else {
				cout << "\n" << "--> Error Employee Adding Faild!!\n";
			}
				


		}while(_WantsToAddAnotherEmployee());

	}

	void show() {
		showGlobalScreen("Add Screen");
		_Add();
	}
};