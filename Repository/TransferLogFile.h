#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "Client.h"
#include "clsDate.h"
#include "Employee.h"
#include "CurrentUser.h"
#include "ITransferLog.h"
#include "TransferRecord.h"

class TransferLogFile : public ITransferLog
{
	std::string _fileName{};
	std::string _delim{};

	std::string _convertFromTransStructToLine(const CurrentUser& user, const Client& sender, const Client& rec, const double amount) {
		
		clsDate date{};
		const Employee& emp{ user.getEmployee() };

		return { date.GetSystemDateTimeString() + _delim + sender.getAccountNumber() + _delim + rec.getAccountNumber() + _delim + to_string(amount) + _delim + to_string(sender.getBalance()) + _delim + to_string(rec.getBalance()) + _delim + emp.getUserName() };
	
	}

public:
	TransferLogFile(const std::string fileName, const std::string delim = "#//#") : _fileName(fileName), _delim(delim) {}

	bool recordTransferProcess(const CurrentUser& user, const Client& sender, const Client& rec, const double amount) override{
		ofstream oFile{ _fileName, std::ios::app };

		if (oFile) {
			oFile << _convertFromTransStructToLine(user, sender, rec, amount) << '\n';
			oFile.close();
			return true;
		}
		return false;
	}

};

