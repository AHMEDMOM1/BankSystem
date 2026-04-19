
#include "TransferLogFile.h"
#include "EmployeeManager.h"
#include "FileEmployeeRepo.h"

#include "AppContext.h"
#include "LoginScreen.h"
#include "LoggerManager.h"
#include "UserLoginFile.h"
#include "ClientManager.h"
#include "CurrenciesFile.h"
#include "FileClientRepo.h"
#include "CurrencyManager.h"


using namespace std;

int main() {
	// Preparing work files

    FileEmployeeRepo empRepo{ "Employee.txt" };
	EmployeeManager empManager{ empRepo };
	
	FileClientRepo clntRepo{ "Client.txt" };
    TransferLogFile transLog{ "TransFerLog.txt" };
	ClientManager clntManager{ clntRepo, transLog };

    CurrenciesFile curFile{"Currencies.txt"};
    CurrencyManager curManager{ curFile };

    UserLoginFile userLog{ "UserLog.txt" };
    LoggerManager logManager{ userLog };

    AppContext context{ clntManager, empManager, curManager, logManager };

    // <-----------------


    StartScreen start(context);
    start.login(context);

    return 0;
}

