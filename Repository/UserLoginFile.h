#pragma once
#include <string>
#include <fstream>
#include <iostream>

#include "clsDate.h"
#include "Employee.h"
#include "CurrentUser.h"

class UserLoginFile
{
	std::string _fileName{};
	std::string _delim{};



    std::string _ConvertCurrentUserToLine(const CurrentUser& user) {
        clsDate date{};
        Employee emp{ user.getEmployee() };

        return { date.GetSystemDateTimeString() + _delim + 
                 emp.getUserName()  + _delim + emp.getPassword() + _delim + to_string(emp.getPermissions()) };
    }
public:
	UserLoginFile(const std::string& fileName, const std::string& delim = "#//#") : _fileName(fileName), _delim(delim) {}

    bool add(const CurrentUser& user) {
        std::ofstream oFile{ _fileName, std::ios::app };
        if (oFile) {
            oFile << _ConvertCurrentUserToLine(user) << '\n';
            oFile.close();
            return true;
        }
        return false;
    }
};

