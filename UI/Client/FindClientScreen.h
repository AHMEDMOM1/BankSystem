#pragma once

#include "ClientScreenBase.h"

class FindClientScreen  : protected ClientScreenBase {
	
	bool _WantsToFindAnotherClient() {
		return _RequestRepetition("\n" + string(30, ' ') + "Do you want to find another client? (Y/N): ");
	}public:
	FindClientScreen(ClientManager& manager) : ClientScreenBase(manager) {}

	void _Find(){
		do{
			Client client{_GetClient()};
			
			if(client.isEmpty())
				return;
			_Print(client);

		}while(_WantsToFindAnotherClient());

	}
public:
	void show(const CurrentUser& user){
		showGlobalScreen("Find Screen");

		if (!CheckAccessRights(user, Employee::enPermissions::pFindClient)) return;

		_Find();
		
	}
};
