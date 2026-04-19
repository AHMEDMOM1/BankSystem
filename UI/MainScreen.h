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
    _PrintStartBlank(30); cout << '[' << Employee << ']' << ".Employee Manage" << endl;
    _PrintStartBlank(30); cout << '[' << Client << ']' << ".Client Manage" << endl;
    _PrintStartBlank(30); cout << '[' << Logout << ']' << ".Logout" << endl;
	_PrintStartBlank(30); cout << "------------" << '\n';
  }
  void _PrintMainScreen(const std::string& userName) { 
	showGlobalScreen("Main Screen (" + userName + ')');
	_PrintBody();
  }

  enChoise getChoise(){
	short choise{};
	_PrintStartBlank(30); cout << "Enter Choise: ";
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

