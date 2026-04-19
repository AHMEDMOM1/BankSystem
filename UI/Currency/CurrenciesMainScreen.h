#pragma once

#include "Screen.h"
#include "CurrencyManager.h"
#include "FindCurrencyScreen.h"
#include "UpdateCurrencyScreen.h"
#include "ShowAllCurrenciesScreen.h"

class CurrenciesMainScreen : protected Screen {
	CurrencyManager& _manager;


	enum CurrencyOp { Find = 1, Update, ShowAll, Back }_choise{};
public:

	CurrenciesMainScreen(CurrencyManager& manager) : _manager(manager) {}
	void _printBody() {

		cout << setw(30) << ' ' << '[' << Find << ']' << ".Find" << endl;
		cout << setw(30) << ' ' << '[' << Update << ']' << ".Update" << endl;
		cout << setw(30) << ' ' << '[' << ShowAll << ']' << ".Show Currencies List" << endl;
		cout << setw(30) << ' ' << '[' << Back << ']' << ".Go Back" << endl;

	}
	void _PrintMainScreen() {
		showGlobalScreen("Currency Main Screen");
		_printBody();
	}

	void _DirectToScreen(CurrencyOp choise) {
		switch (choise) {
		case Find: {
			FindCurrencyScreen findScreen{_manager};
			findScreen.show();
			break;
		}
		case Update: {
			UpdateCurrencyScreen updateScreen{_manager};
			updateScreen.show();
			break;
		}
		case ShowAll: {
			ShowAllCurrenciesScreen currencyListScreen{_manager};
			currencyListScreen.show();
			break;
		}
		case Back: {
			return;
		}
		}
	}

	CurrencyOp getChoise() {
		short choise{};
		cout << setw(30) << ' ' << "------------" << '\n';
		cout << setw(30) << ' ' << "Enter Choise: ";
		cin >> choise;
		return static_cast<CurrencyOp>(choise);
	}
	

	void show() {
		do {
			system("cls");
			_PrintMainScreen();

			_choise = getChoise();
			if (_choise >= Back)break;

			system("cls");
			_DirectToScreen(_choise);

			system("pause");
		} while (true);

	}
};