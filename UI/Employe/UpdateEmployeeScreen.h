#pragma once 

#include "Employee.h"
#include "EmployeeManager.h"
#include "EmployeeScreenBase.h"

class UpdateEmployeeScreen : protected EmployeeScreenBase {

	bool _WantsToUpdateAnotherEmployee() {
		return _RequestRepetition("\n" + string(30, ' ') + "Do you want to Update another employee? (Y/N): ");
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

		const vector<PermissionItem> permissions{
			{ "Give Show List? ",  Employee::enPermissions::pListClients   },
			{ "Give Add? ",        Employee::enPermissions::pAddNewClient  },
			{ "Give Delete? ",     Employee::enPermissions::pDeleteClient  },
			{ "Give Update? ",     Employee::enPermissions::pUpdateClients },
			{ "Give Find? ",       Employee::enPermissions::pFindClient    },
		};

		int perm{};
		for (const auto& item : permissions) {
			_PrintStartBlank(30); cout << item.question;
			if (clsInputValidate::wantToApprove())
				perm |= static_cast<int>(item.flag);
		}

		return perm;
	}

public:
	UpdateEmployeeScreen(EmployeeManager& manager) : EmployeeScreenBase(manager) {}

	void show() {
		showGlobalScreen("Update Screen");

		do {
			Employee employee{ _GetUser() };

			if (employee.isEmpty())return;

			_Print(employee);

			if (_ConfirmAction()) {

				_FillInfo(employee);
				employee.setPermissions(_GetPermission());

				if(_employeeManager.update(employee))
					cout << "\n" << setw(30) << ' ' << "--> Employee Updating Successfully!\n";
				else 
					cout << "\n" << "--> Error Employee Updating Faild!!\n";
			}


		} while (_WantsToUpdateAnotherEmployee());

	}
};