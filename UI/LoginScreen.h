#pragma once

#include "Employee.h"
#include "MainScreen.h"
#include "MainScreen.h"
#include "AppContext.h"
#include "CurrentUser.h"
#include "ClientManager.h"
#include "EmployeeManager.h"
#include "ClientMainScreen.h"
#include "clsInputValidate.h"
#include "EmployeeScreenBase.h"

class StartScreen : protected EmployeeScreenBase{

// EmployeeManager& _empManager;
// if we initialization _empManager to parametery var not prob why?



public:
    enum class LoginStatus { Success, Failed, Canceled };

private:
   
    bool _IsUserDataCorrect(const std::string& userName,const std::string& passWord){
        Employee employee{_employeeManager.find(userName)};

        if(employee.isEmpty()){
            cout << setw(30) << ' ' << "--> Error: UserName not found!\n";
            return false;
        }
        else if(employee.getPassword() != passWord){
            cout << setw(30) << ' ' << "--> Error: Password Incorrect!!\n";
            return false;
        }

        return true;
    }

bool checkIfUserZero(const std::string& user) {
    return user == "0";
}

string _InputUserName() {
    cout << setw(30) << ' ';
    return clsInputValidate::ReadString("Enter UserName: ");
}

string _InputPassWord() {
    cout << setw(30) << ' ';
    return clsInputValidate::ReadString("Enter PassWord: ");
}

public:
    StartScreen(AppContext& context) : EmployeeScreenBase(context.empManager){}

    LoginStatus login(CurrentUser& user){
        showGlobalScreen("Login Screen", "(exit = 0)");
        
        string userName = _InputUserName();

        if (checkIfUserZero(userName)) return LoginStatus::Canceled;

        string passWord = _InputPassWord();
       
        if(_IsUserDataCorrect(userName, passWord)){
            Employee loggedInEmp = _employeeManager.find(userName);
            user.login(loggedInEmp);
            return LoginStatus::Success;
        }
        
        return LoginStatus::Failed;
    }

    bool login(AppContext& context) {

        CurrentUser sessionUser;
        int i{ 3 };

        do {
            StartScreen::LoginStatus result = login(sessionUser);

            if (result == StartScreen::LoginStatus::Failed) {
                i--;
                cout << setw(30) << ' ' << "You Have " << i << " Trying!!" << endl;
            }
            else if (result == StartScreen::LoginStatus::Canceled) return 0;
            else {
               
                context.logManager.add(sessionUser);

                MainScreen mainScreen(context);
                mainScreen.show(sessionUser);
            }
        } while (i > 0);
    }
};
