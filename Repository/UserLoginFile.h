#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "clsDate.h"
#include "clsString.h"
#include "Employee.h"
#include "CurrentUser.h"
#include "LoginRecord.h"

class UserLoginFile
{
	std::string _fileName{};
	std::string _delim{};

    std::string _ConvertCurrentUserToLine(const CurrentUser& user) {
        const Employee& emp = user.getEmployee();

        return { clsDate::GetSystemDateTimeString() + _delim +
                 emp.getUserName()  + _delim + emp.getPassword() + _delim + std::to_string(emp.getPermissions()) };
    }

    LoginRecord _ConvertLineToRecord(const std::string& line) {
        std::vector<std::string> fields = clsString::Split(line, _delim);
        LoginRecord record;

        if (fields.size() >= 1) record.dateTime     = fields[0];
        if (fields.size() >= 2) record.userName     = fields[1];
        if (fields.size() >= 3) record.password     = fields[2];
        if (fields.size() >= 4) record.permissions  = std::stoi(fields[3]);

        return record;
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

    std::vector<LoginRecord> getAll() {
        std::vector<LoginRecord> vRecords{};
        std::fstream myFile{};
        myFile.open(_fileName, std::ios::in);
        if (myFile) {
            std::string line;
            while (std::getline(myFile, line)) {
                if (!line.empty())
                    vRecords.push_back(_ConvertLineToRecord(line));
            }
            myFile.close();
        }
        return vRecords;
    }
};
