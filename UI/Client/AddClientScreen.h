#pragma once
#include <iostream>
#include <iomanip>

#include "ClientScreenBase.h"

class AddClientScreen : protected ClientScreenBase {
	
	bool _WantsToAddAnotherClient(){
		return _RequestRepetition("\n" + string(30, ' ') + "Do you want to add another client? (Y/N): ");
	}

	bool _TryReadNewAccount(string& account) {
		do {
			cout << setw(30) << ' ';
			account = clsInputValidate::ReadString("Enter New Account: ");
			if (!_manager.existAccount(account)) {
				return true;
			}
			cout << setw(30) << ' ' << "--> Error: Account already exists!\n";

		} while (_WantsToTryAnotherAccount());
		return false;
	}

	Client _CreateClient() {
		string account{};
		if (!_TryReadNewAccount(account)) {
			return Client();
		}
		Client client("", "", "", "", account, 0, 0.0);
		_FillInfo(client);
		

		return client;
	}

public:
	AddClientScreen(ClientManager& manager) : ClientScreenBase(manager) {}
	void show(const CurrentUser& user) {
		showGlobalScreen("Add Screen");
		
		
		// created in screen.h for don't reapet print massage
		if (!CheckAccessRights(user, Employee::enPermissions::pAddNewClient)) {
			return; // Access denied! message already printed.
		}

		do {
			Client client{ _CreateClient() };
			if (client.isEmpty()) 
				return;

			_manager.addNew(client);

			cout << "\n" << setw(30) << ' ' << "--> Client Added Successfully!\n";
			_Print(client);

		} while (_WantsToAddAnotherClient());

	}
};
