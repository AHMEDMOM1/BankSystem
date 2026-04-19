#pragma once

#include <iostream>
#include <iomanip>

#include "Screen.h"
#include "DepoScreen.h"
#include "WithdScreen.h"
#include "ClientManager.h"
#include "TransferScreen.h"
#include "clsInputValidate.h"
#include "TransferLogScreen.h"
#include "TotalBalanceScreen.h"

using namespace std;

class TransictionScreen : protected Screen
{
	ClientManager& _manager;
	enum _enChoise { Depo = 1, Withd, TotalBalance, Transfer, TransFerShow, Back };
	_enChoise _GetChosie() {
			_PrintStartBlank(30);
		short choise{
			static_cast<short>(clsInputValidate::ReadIntNumber("Chosie: "))
		};
		return static_cast<_enChoise>(choise);
	}
	void _DirectToScreen(const _enChoise& choise, const CurrentUser& user) {
		switch (choise) {
		case Depo: {
			DepoScreen depo(_manager);
			depo.show();
			break;
		}
		case Withd: {
			WithdrawScreen withd(_manager);
			withd.show();
			break;
		}
		case TotalBalance: {
			TotalBalanceScreen total(_manager);
			total.show();
			break;
		}
		case Transfer: {
			TransferScreen trans(_manager);
			trans.show(user);
			break;
		}
		case TransFerShow: {
			TransferLogScreen transShow(_manager);
			transShow.show();
			break;
		}
		default:
			return;
		}
	}

	void _PrintBody() {
		_PrintStartBlank(30); cout << '[' << Depo << ']' << ". Deposite" << endl;
		_PrintStartBlank(30); cout << '[' << Withd << ']' << ". Withdraw" << endl;
		_PrintStartBlank(30); cout << '[' << TotalBalance << ']' << ". Show Total Balance" << endl;
		_PrintStartBlank(30); cout << '[' << Transfer << ']' << ". Transfer" << endl;
		_PrintStartBlank(30); cout << '[' << TransFerShow << ']' << ". Transfer Log Screen" << endl;
		_PrintStartBlank(30); cout << "[6]. Main Screen" << endl;
		_PrintStartBlank(30); cout << "------------------" << '\n';
	}
public:
	
	TransictionScreen(ClientManager& manager) : _manager(manager) {}
	void show(const CurrentUser& user) {
		_enChoise choise{};

		showGlobalScreen("Transcition Screen");
		if (!CheckAccessRights(user, Employee::enPermissions::pTransactions)) {
			system("pause");
			return;
		}

		do {

			system("cls");
			showGlobalScreen("Transcition Screen");

			_PrintBody();
			choise = _GetChosie();
			system("cls");

			_DirectToScreen(choise, user);

			if (choise >= Back)break;

			system("pause");

		} while (true);
	}

};

