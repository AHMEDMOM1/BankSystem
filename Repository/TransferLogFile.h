#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "Client.h"
#include "clsDate.h"
#include "Employee.h"
#include "clsString.h"
#include "CurrentUser.h"
#include "ITransferLog.h"
#include "TransferRecord.h"


class TransferLogFile : public ITransferLog
{
	std::string _fileName{};
	std::string _delim{};

	std::string _convertFromTransStructToLine(const CurrentUser& user, const Client& sender, const Client& rec, const double amount) {
		
		const Employee& emp{ user.getEmployee() };

		return { clsDate::GetSystemDateTimeString() + _delim + sender.getAccountNumber() + _delim + rec.getAccountNumber() + _delim + to_string(amount) + _delim + to_string(sender.getBalance()) + _delim + to_string(rec.getBalance()) + _delim + emp.getUserName() };
	
	}

	TransferRecord _convertFromLineToTransLogStruct(std::string& line) {
		std::vector<std::string>fields{ clsString::Split(line, _delim) };
		TransferRecord record{};

		if (fields.size() >= 1) record.date               = fields.at(0);
		if (fields.size() >= 2) record.senderAccount      = fields.at(1);
		if (fields.size() >= 3) record.recipientAccount   = fields.at(2);
		if (fields.size() >= 4) record.amount             = std::stod(fields.at(3));
		if (fields.size() >= 5) record.senderAmount       = std::stod(fields.at(4));
		if (fields.size() >= 6) record.recipientAmount    = std::stod(fields.at(5));
		if (fields.size() >= 7) record.currentUserAccount = fields.at(6);

		return record;
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

	std::vector<TransferRecord> loadAllRecords() override{
		ifstream iFile{ _fileName, std::ios::in };
		std::vector<TransferRecord> records{};

		if (iFile) {
			string line{};
			while (std::getline(iFile, line)) {
				TransferRecord record{ _convertFromLineToTransLogStruct(line) };

				if (!line.empty())
					records.push_back(record);
			}
			iFile.close();
		}

		return records;
	}

};

