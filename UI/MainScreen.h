#pragma once

#include <iostream>

#include "Screen.h"
#include "AppContext.h"
#include "ClientMainScreen.h"
#include "EmployeesMainScreen.h"


// 1. print main screen
// 2. create logic screen

using namespace std;
class MainScreen : protected Screen {
	AppContext& _context;

  enum enChoise { Employee = 1, Client, Logout } _choise{};
  void _PrintBody() {
    cout << setw(30) << ' ' << '[' << Employee << ']' << ".Employee Manage" << endl;
    cout << setw(30) << ' ' << '[' << Client << ']' << ".Client Manage" << endl;
    cout << setw(30) << ' ' << '[' << Logout << ']' << ".Logout" << endl;
	cout << setw(30) << ' ' << "------------" << '\n';
  }
  void _PrintMainScreen(const std::string& userName) { 
	showGlobalScreen("Main Screen (" + userName + ')');
	_PrintBody();
  }

  enChoise getChoise(){
	short choise{};
	cout << setw(30) << ' ' << "Enter Choise: ";
	cin >> choise;
	return static_cast<enChoise>(choise);
  }

  void _DirectToScreen(const enChoise& choise, CurrentUser& user){
	switch (choise) {
		case Employee: {
			EmployeesMainScreen empMainScreen(_context.empManager);
			empMainScreen.show(user);
			break;
		}
		case Client: {
			ClientMainScreen clntMainScreen(_context);
			clntMainScreen.show(user);
			break;
		}
		case Logout:
			user.logout();
			return;
		default:
			break;
	}
  }

public:
  MainScreen(AppContext& context): _context(context) {};

  void show(CurrentUser& user) {
	do{
		
		system("cls");
		_PrintMainScreen(user.getEmployee().getUserName());
		_choise = getChoise();

		system("cls");
		_DirectToScreen(_choise, user);


	}while(_choise != Logout);
  }
};

