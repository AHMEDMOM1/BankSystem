#pragma once 

#include "Employee.h"
#include "EmployeeManager.h"
#include "EmployeeScreenBase.h"

class DeleteEmployeeScreen : protected EmployeeScreenBase {

	bool _WantsToDeleteAnotherEmployee() {
		return _RequestRepetition("\n" + string(30, ' ') + "Do you want to delete another employee? (Y/N): ");
	}

public:
	DeleteEmployeeScreen(EmployeeManager& manager) : EmployeeScreenBase(manager) {}

	void show() {
		showGlobalScreen("Delete Screen");

		do {
			Employee employee{ _GetUser() };

			if (employee.isEmpty())return;

			_Print(employee);

			if (_ConfirmAction()) {
				_employeeManager.remove(employee);
				
				cout << "\n" << setw(30) << ' ' << "--> Employee Deleting Successfully!\n";
			}


		} while (_WantsToDeleteAnotherEmployee());

	}
};