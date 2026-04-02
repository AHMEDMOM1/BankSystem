#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h> 
#undef byte
#include <iostream>
#include <iomanip>
#include "../CurrentUser.h"

using namespace std;

class Screen
{
private:

	short _getConsoleWidth() const {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		short columns = 80; 
	
		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
			columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		}
		return columns;
	}

	void _showHeader(const string& Title ) {

		short consoleWidth = _getConsoleWidth();
		short dev = (Title.length() / 2);
		short lineLength = 60;
		if (lineLength > consoleWidth) lineLength = consoleWidth; 

		short lineStartPos = (consoleWidth / 2) - (lineLength / 2); 
		short titleStartPos = (consoleWidth / 2) - dev;             

		cout << setw(lineStartPos) << setfill(' ') << "" << setw(lineLength) << setfill('=') << "" << setfill(' ') << endl;

		cout << setw(titleStartPos) << "" << Title << endl;

		cout << setw(lineStartPos) << setfill(' ') << "" << setw(lineLength) << setfill('=') << "" << setfill(' ') << endl;
	}

public:
	void showGlobalScreen(const string& title) {
		_showHeader(title);
	}

	bool CheckAccessRights(const CurrentUser& user, Employee::enPermissions permission) {
		if (!user.checkAccessPermission(permission)) {
			cout << "\n\t\t\t\tAccess Denied! \n\t\t\t\tYou don't have permission to do this.\n\t\t\t\tContact your Admin.\n";
			return false;
		}
		return true;
	}
};
