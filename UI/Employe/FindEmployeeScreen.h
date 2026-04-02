#pragma once 

#include "Employee.h"
#include "EmployeeManager.h"
#include "EmployeeScreenBase.h"

class FindEmployeeScreen : protected EmployeeScreenBase {

	bool _WantsToFindAnotherEmployee() {
		return _RequestRepetition("\n" + string(30, ' ') + "Do you want to Find another employee? (Y/N): ");
	}


	bool _WantAllPermision() {
		cout << setw(30) << ' ' << "Do you need give to employee All Permisions? (yes/no): ";
		return clsInputValidate::wantToApprove();
	}


public:
	FindEmployeeScreen(EmployeeManager& manager) : EmployeeScreenBase(manager) {}

	void show() {
		showGlobalScreen("Find Screen");

		do {
			Employee employee{ _GetUser() };

			if (employee.isEmpty())return;

			_Print(employee);

		} while (_WantsToFindAnotherEmployee());

	}
};