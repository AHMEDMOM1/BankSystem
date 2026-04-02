#pragma once
#include "ClientScreenBase.h"

class DeleteClientScreen : protected ClientScreenBase {
	
	bool _WantsToDeleteAnotherClient() {
		return _RequestRepetition("\n" + string(30, ' ') + "Do you want to Delete another client? (Y/N): ");
	}

	void _Delete() {
		do {
			Client client{ _GetClient() };
			if (client.isEmpty())
				return;
			_Print(client);

			if (_ConfirmAction()) {
				_manager.remove(client.getAccountNumber());
				cout << "\n" << setw(30) << ' ' << "--> Client Deleted Successfully!\n";
			}
			else {
				cout << setw(30) << ' ' << "--> Deletion Cancelled.\n";
			}

			
		} while (_WantsToDeleteAnotherClient());
	}
public:
	DeleteClientScreen(ClientManager& manager) : ClientScreenBase(manager) {}

	void show(const CurrentUser& user) {
		showGlobalScreen("Delete Screen");

		if (!CheckAccessRights(user, Employee::enPermissions::pDeleteClient)) return;

		_Delete();
	}
};
