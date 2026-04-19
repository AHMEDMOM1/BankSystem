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

	void _showHeader(const string& Title, const string& SubTitle = "") {

		short consoleWidth = _getConsoleWidth();
		short lineLength = 60;
		if (lineLength > consoleWidth) lineLength = consoleWidth; 

		short lineStartPos = (consoleWidth / 2) - (lineLength / 2); 

		cout << setw(lineStartPos) << setfill(' ') << "" << setw(lineLength) << setfill('=') << "" << setfill(' ') << endl;

		string titleLine(lineLength, ' ');
		short titleStart = (lineLength / 2) - (Title.length() / 2);

		if (titleStart >= 0 && Title.length() <= lineLength) {
			titleLine.replace(titleStart, Title.length(), Title);
		}

		if (!SubTitle.empty()) {
			short subStart = lineLength - SubTitle.length();
			if (subStart >= titleStart + Title.length()) { // Prevent overlap
				titleLine.replace(subStart, SubTitle.length(), SubTitle);
			}
		}

		cout << setw(lineStartPos) << setfill(' ') << "" << titleLine << endl;

		cout << setw(lineStartPos) << setfill(' ') << "" << setw(lineLength) << setfill('=') << "" << setfill(' ') << endl;
	}

public:
	void _PrintStartBlank(const short blank = 10) {
		cout << setw(blank) << ' ';
	}

	void showGlobalScreen(const string& title, const string& subTitle = "") {
		_showHeader(title, subTitle);
	}

	bool CheckAccessRights(const CurrentUser& user, Employee::enPermissions permission) {
		if (!user.checkAccessPermission(permission)) {
			cout << "\n\t\t\t\tAccess Denied! \n\t\t\t\tYou don't have permission to do this.\n\t\t\t\tContact your Admin.\n";
			return false;
		}
		return true;
	}
};
