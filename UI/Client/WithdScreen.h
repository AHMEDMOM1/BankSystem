#pragma once 
#include <iostream>
#include <iomanip>
#include <string>

#include "Client.h"
#include "ClientManager.h"
#include "ClientScreenBase.h"
#include "clsInputValidate.h"

class WithdrawScreen : protected ClientScreenBase {
	double _ReadWithdrawAmount(double currentAmount) {
		double newAmount{ };
		do {
			std::cout << "\n" << std::setw(30) << ' ';
			newAmount = clsInputValidate::ReadDblNumber("Enter Withdraw Amount: ");

			if (currentAmount < newAmount)
				std::cout << "\n" << std::setw(30) << ' ' << "The current amount is less than the required amount ";
			else if (newAmount <= 0)
				std::cout << "\n" << std::setw(30) << ' ' << "Invalid number. Enter a number greater than zero. ";
			else break;

		} while (true);

		return newAmount;
	}

	bool _WantsToWithdrawFromAnotherClient() {
		return _RequestRepetition("\n" + std::string(30, ' ') + "Do you want to Withdraw from another client? (Y/N): ");
	}
public:
	WithdrawScreen(ClientManager& manager) : ClientScreenBase(manager) {}
	void show(const CurrentUser& user) {
		showGlobalScreen("Withdraw Screen");

		do {

			Client client{ _GetClient() };
			if (client.isEmpty())
				return;

			_Print(client);

			double amount{_ReadWithdrawAmount(client.getBalance())};

			if (!_ConfirmAction())
				continue;

			client.setBalance(client.getBalance() - amount);
			if (!_manager.update(client)){
                std::cout << '\n' << std::setw(30) << ' ' << "--> Error: Amount Update failed!!\n";
                return;
            }
				
			std::cout << "\n" << std::setw(30) << ' ' << "--> The balance was successfully updated!!\n";
			_Print(client);
		
		} while (_WantsToWithdrawFromAnotherClient());

	}
};