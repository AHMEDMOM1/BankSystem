#pragma once

#include "ClientScreenBase.h"

class UpdateClientScreen : protected ClientScreenBase {

public:
	UpdateClientScreen(ClientManager& manager) : ClientScreenBase(manager) {}
	void show(const CurrentUser& user){
		showGlobalScreen("Update Screen");
		
		if (!CheckAccessRights(user, Employee::enPermissions::pUpdateClients)) return;
		do{
			Client client{_GetClient()};
			if(client.isEmpty())
				return;
			_Print(client);
			if (_ConfirmAction()) {
				_FillInfo(client);
				if (_manager.update(client)) {
					cout << "\n"; _PrintStartBlank(30); cout << "--> Client Updated Successfully!\n";
				}
				else {
					cout << "\n"; _PrintStartBlank(30); cout << "--> Error: Updating Client Failed!\n";
				}
			}
		}while(_RequestRepetition("\n" + string(30, ' ') + "Do you want to update another client? (Y/N): "));
	
		return;
	}
};
