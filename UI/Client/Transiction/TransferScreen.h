#pragma once
#include <iostream>

#include "Client.h"
#include "ClientManager.h"
#include "clsInputValidate.h"
#include "ClientScreenBase.h"

class TransferScreen : protected ClientScreenBase
{
	enum enTransferState { SameAccount, CanceledTrans, Successed, FailedTrans };

	double _getValidAmount(const Client& fromClient) {
		double validAmount{};
		double SendersAmount{ fromClient.getBalance() };
		do {
			cout << setw(30) << ' ' << "Enter a valid amount that is less than " << SendersAmount << ": ";
			validAmount = clsInputValidate::ReadDblNumber();
		} while (validAmount > SendersAmount || validAmount <= 0);

		return validAmount;
	}

	enTransferState _TransFer(const CurrentUser& user, Client& fromClient, Client& toClient, double& amount) {

		fromClient = _GetClient("Enter the account number you want to send from: ");
		if (fromClient.isEmpty())
			return CanceledTrans;

		_Print(fromClient);

		toClient = _GetClient("Enter the account number you want to send to: ");
		if (toClient.isEmpty())
			return CanceledTrans;

		_Print(toClient);

		if (fromClient.getAccountNumber() == toClient.getAccountNumber())
			return SameAccount;


		amount = _getValidAmount(fromClient);
		
		if (!_ConfirmAction())
			return CanceledTrans;

		if (!_manager.transfre(user, fromClient, toClient, amount))
			return FailedTrans;

		return Successed;
	}

	void _PrintStateMassage(enTransferState enTransSt) {
		switch (enTransSt) {
		case SameAccount: {
			cout << setw(30) << ' ' << "--> Error: The recipient's mistake is the same as the sender's!!\n";
			break;
		}
		case CanceledTrans: {
			cout << setw(30) << ' ' << "--> Clarification!! The operation has been cancelled\n";
			break;
		}
		case Successed: {
			cout << setw(30) << ' ' << "--> The transfer was successful.!!\n";
			break;
		}
		case FailedTrans: {
			cout << setw(30) << ' ' << "--> The Trasfering is Failed!!";
			break;
		}
		}
	}

public:
	TransferScreen(ClientManager& manager) : ClientScreenBase(manager) {}
	void show(const CurrentUser& user) {
		showGlobalScreen("Transfer Screeen");

		Client sender{};
		Client recipient{};
		double amount{};

		enTransferState enTransSt = _TransFer(user, sender, recipient, amount);

		system("cls");
		showGlobalScreen("Transfer Screen");

		_PrintStateMassage(enTransSt);
		if (enTransSt == Successed) {
			_Print(sender);
			_Print(recipient);
		}
	}
};

