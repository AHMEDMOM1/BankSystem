#pragma once

#include <iostream>

#include "Screen.h"
#include "AppContext.h"
#include "ClientsList.h"
#include "ClientManager.h"
#include "CurrencyManager.h"
#include "AddClientScreen.h"
#include "FindClientScreen.h"
#include "TransictionScreen.h"
#include "DeleteClientScreen.h"
#include "UpdateClientScreen.h"
#include "CurrenciesMainScreen.h"




using namespace std;
class ClientMainScreen : protected Screen {
	AppContext& _context;

	enum enChoise { Add = 1, Delete, Update, Find, ShowList, Currency, Trans, Back } _choise{};
	void _PrintBody() {
		cout << setw(30) << ' ' << '[' << Add << ']' << ".Add" << endl;
		cout << setw(30) << ' ' << '[' << Delete << ']' << ".Delete" << endl;
		cout << setw(30) << ' ' << '[' << Update << ']' << ".Update" << endl;
		cout << setw(30) << ' ' << '[' << Find << ']' << ".Find" << endl;
		cout << setw(30) << ' ' << '[' << ShowList << ']' << ".Show List" << endl;
		cout << setw(30) << ' ' << '[' << Currency << ']' << ".Currencies" << endl;
		cout << setw(30) << ' ' << '[' << Trans << ']' << ".Transiction" << endl;
		cout << setw(30) << ' ' << '[' << Back << ']' << ".Login Screen" << endl;
		cout << setw(30) << ' ' << "------------" << '\n';
	}
	void _PrintMainScreen(const std::string& userName) {
		showGlobalScreen("Client Main Screen (" + userName + ')');
		_PrintBody();
	}

	enChoise getChoise() {
		short choise{};
		cout << setw(30) << ' ' << "Enter Choise: ";
		cin >> choise;
		return static_cast<enChoise>(choise);
	}

	void _DirectToScreen(const enChoise& choise, const CurrentUser& user) {
		switch (choise) {
		case Add: {
			AddClientScreen addScreen(_context.clntManager);
			addScreen.show(user);
			break;
		}
		case Delete: {
			DeleteClientScreen deleteScreen(_context.clntManager);
			deleteScreen.show(user);
			break;
		}
		case Update: {
			UpdateClientScreen updateScreen(_context.clntManager);
			updateScreen.show(user);
			break;
		}
		case Find: {
			FindClientScreen findScreen(_context.clntManager);
			findScreen.show(user);
			break;
		}
		case ShowList: {
			ClientsList clienstList(_context.clntManager);
			clienstList.show(user);
			break;
		}
		case Currency: {
			CurrenciesMainScreen currMainScreen{_context.curManager};
			currMainScreen.show();
			break;
		}
		case Trans: {
			TransictionScreen transScreen(_context.clntManager);
			transScreen.show(user);
			break;
		}
		case Back: {
			return;
		}
		default:
			return;
		}
	}

public:
	ClientMainScreen(AppContext& context): _context(context) {};

	void show(const CurrentUser& user) {
		do {
			system("cls");
			_PrintMainScreen(user.getEmployee().getUserName());
			_choise = getChoise();

			system("cls");
			_DirectToScreen(_choise, user);

			if (_choise >= Back)break;
			else if(_choise < Currency)
				system("pause");

		} while (true);
	}
};
