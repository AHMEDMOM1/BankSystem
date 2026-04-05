#pragma once

#include <iostream>

#include "Screen.h"
#include "ClientsList.h"
#include "ClientManager.h"
#include "AddClientScreen.h"
#include "FindClientScreen.h"
#include "TransictionScreen.h"
#include "DeleteClientScreen.h"
#include "UpdateClientScreen.h"


// 1. print main screen
// 2. create logic screen

using namespace std;
class ClientMainScreen : protected Screen {
	ClientManager& _clntManager;
	enum enChoise { Add = 1, Delete, Update, Find, ShowList, Trans } _choise{};
	void _PrintBody() {
		cout << setw(30) << ' ' << '[' << Add << ']' << ". Add" << endl;
		cout << setw(30) << ' ' << '[' << Delete << ']' << ". Delete" << endl;
		cout << setw(30) << ' ' << '[' << Update << ']' << ". Update" << endl;
		cout << setw(30) << ' ' << '[' << Find << ']' << ". Find" << endl;
		cout << setw(30) << ' ' << '[' << ShowList << ']' << ". Show List" << endl;
		cout << setw(30) << ' ' << '[' << Trans << ']' << ". Transiction" << endl;
		cout << setw(30) << ' ' << "[7]. Login Screen" << endl;
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
			AddClientScreen addScreen(_clntManager);
			addScreen.show(user);
			break;
		}
		case Delete: {
			DeleteClientScreen deleteScreen(_clntManager);
			deleteScreen.show(user);
			break;
		}
		case Update: {
			UpdateClientScreen updateScreen(_clntManager);
			updateScreen.show(user);
			break;
		}
		case Find: {
			FindClientScreen findScreen(_clntManager);
			findScreen.show(user);
			break;
		}
		case ShowList: {
			ClientsList clienstList(_clntManager);
			clienstList.show(user);
			break;
		}
		case Trans: {
			TransictionScreen transScreen(_clntManager);
			transScreen.show(user);
			break;
		}
		default:
			return;
		}
	}

public:
	ClientMainScreen(ClientManager& clntManager) : _clntManager(clntManager) {};

	void show(const CurrentUser& user) {
		do {
			system("cls");
			_PrintMainScreen(user.getEmployee().getUserName());
			_choise = getChoise();

			system("cls");
			_DirectToScreen(_choise, user);

			system("pause");

		} while (true);
	}
};
