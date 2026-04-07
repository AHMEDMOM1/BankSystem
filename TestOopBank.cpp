
#include "TransferLogFile.h"
#include "EmployeeManager.h"
#include "FileEmployeeRepo.h"

#include "UserLoginFile.h"
#include "FileClientRepo.h"
#include "ClientManager.h"
#include "LoginScreen.h"
#include "MainScreen.h"



using namespace std;

int main() {
	FileEmployeeRepo empRepo{ "Employee.txt" };
	EmployeeManager empManager{ empRepo };
	
	FileClientRepo clntRepo{ "Client.txt" };
    TransferLogFile transLog{ "TransFerLog.txt" };
	ClientManager clntManager{ clntRepo, transLog };
    
   int i{ 3 };
    CurrentUser sessionUser;
    
    do {
        LoginScreen loginScreen(empManager);
        LoginScreen::LoginStatus result = loginScreen.login(sessionUser);
        if (result == LoginScreen::LoginStatus::Failed) {
            i--;
            cout << setw(30) << ' ' << "You Have " << i << " Trying!!" << endl;
        }
        else if (result == LoginScreen::LoginStatus::Canceled) return 0;
        else {
            UserLoginFile userLog{ "UserLog.txt" };
            userLog.add(sessionUser);

            MainScreen mainScreen(clntManager, empManager);
            mainScreen.show(sessionUser);
        }

    } while (i > 0);


    return 0;
}

