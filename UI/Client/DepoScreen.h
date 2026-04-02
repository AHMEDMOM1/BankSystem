#pragma once
#include <iostream>


#include "Client.h"
#include "ClientManager.h"
#include "ClientScreenBase.h"
#include "clsInputValidate.h"


using namespace std;

class DepoScreen : protected ClientScreenBase
{
	bool _WantsToDepoToAnotherClient() {
		return _RequestRepetition("\n" + string(30, ' ') + "Do you want to Deposite to another client? (Y/N): ");
	}
public:
	DepoScreen(ClientManager& manager) : ClientScreenBase(manager) {}
	void show(const CurrentUser& user) {
		showGlobalScreen("Deposite Screen");
		
		do {
			Client client{ _GetClient() };

			if (client.isEmpty())
				return;

			_Print(client);
			if (!_ConfirmAction())
				continue;

			cout << "\n" << setw(30) << ' ';
			double balance{ clsInputValidate::ReadDblNumber("How much do you want to add: ") };
			client.setBalance(client.getBalance() + balance);


			if(!_manager.update(client))
				cout << '\n' << setw(30) << ' ' << "--> Error: Balance Update failed!!\n";

			cout << "\n" << setw(30) << ' ' << "--> The balance was successfully updated!!\n";
			_Print(client);

		} while (_WantsToDepoToAnotherClient());

	}
};

