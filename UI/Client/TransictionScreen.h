#pragma once

#include <iostream>
#include <iomanip>

#include "Screen.h"
#include "DepoScreen.h"
#include "WithdScreen.h"
#include "ClientManager.h"
#include "clsInputValidate.h"
#include "TotalBalanceScreen.h"

using namespace std;

class TransictionScreen : protected Screen
{
	ClientManager& _manager;
	enum _enChoise { Depo = 1, Withd, TotalBalance } _choise{};
	_enChoise _GetChosie() {
			cout << setw(30) << ' ';
		short choise{
			static_cast<short>(clsInputValidate::ReadIntNumber("Chosie: "))
		};
		return static_cast<_enChoise>(choise);
	}
	void _DirectToScreen(const _enChoise& choise, const CurrentUser& user) {
		switch (choise) {
		case Depo: {
			DepoScreen depo(_manager);
			depo.show(user);
			break;
		}
		case Withd: {
			WithdrawScreen withd(_manager);
			withd.show(user);
			break;
		}
		case TotalBalance: {
			TotalBalanceScreen total(_manager);
			total.show(user);
			break;
		}
		default:
			return;
		}
	}

	void _PrintBody() {
		cout << setw(30) << ' ' << '[' << Depo << ']' << ". Deposite" << endl;
		cout << setw(30) << ' ' << '[' << Withd << ']' << ". Withdraw" << endl;
		cout << setw(30) << ' ' << '[' << TotalBalance << ']' << ". Show Total Balance" << endl;
		cout << setw(30) << ' ' << "[4]. Main Screen" << endl;
		cout << setw(30) << ' ' << "------------------" << '\n';
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

			_PrintBody();
			choise = _GetChosie();
			system("cls");

			_DirectToScreen(choise, user);
			
			if (choise <= 3) {
				system("pause");
			}

		} while (choise <= 3);
	}

};

