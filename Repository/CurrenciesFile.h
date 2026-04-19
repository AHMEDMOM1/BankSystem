#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "clsString.h"
#include "ICurrenciesRepo.h"
#include "CurrencyRecord.h"

class CurrenciesFile : public ICurrenciesRepo
{

	std::string _fileName{};
	std::string _delim{};

	CurrencyRecord _ConvertLineToRecStuct(std::string& line) {
		std::vector<std::string>partitions{ clsString::Split(line, _delim) };
		CurrencyRecord record{};

		if (partitions.size() >= 1) record.countryName = partitions.at(0);
		if (partitions.size() >= 2) record.currencyCode = partitions.at(1);
		if (partitions.size() >= 3) record.currencyName = partitions.at(2);
		if (partitions.size() >= 4) record.currencyExchangeDollar = std::stod(partitions.at(3));

		return record;
	}

	std::string _ConvertRecordToLine(const CurrencyRecord& record) {
		return { record.countryName + _delim + 
				 record.currencyCode + _delim + 
				 record.currencyName + _delim +
				 to_string(record.currencyExchangeDollar)};
	}

	bool _SaveAll(std::vector<CurrencyRecord> records) {
		std::ofstream oFile{ _fileName, std::ios::out };

		if (oFile) {
			for (CurrencyRecord& record : records) {
				oFile << _ConvertRecordToLine(record) << '\n';
			}
			return true;
		}

		return false;
	}


public:
	CurrenciesFile(const std::string& fileName, const std::string& delim = "#//#") : _fileName(fileName), _delim(delim) {}

	CurrencyRecord findByCurrencyCode(const std::string& currencyCode) override {
		std::vector<CurrencyRecord> records{ getAll() };

		for (CurrencyRecord& record : records) {
			if (record.currencyCode == currencyCode) return record;
		}

		return CurrencyRecord();
	}
	CurrencyRecord findByCountryName(const std::string& countryName) override {
		std::vector<CurrencyRecord> records{ getAll() };

		for (CurrencyRecord& record : records) {
			if (record.countryName == countryName) return record;
		}

		return CurrencyRecord();
	}
	bool updateRate(const CurrencyRecord& currentRecord)override {
		std::vector<CurrencyRecord> records{ getAll() };

		for (CurrencyRecord& record : records) {
			if (record.currencyCode == currentRecord.currencyCode) {
				record = currentRecord;
				return _SaveAll(records);
			}
		}


		return false;
	}
	
	std::vector<CurrencyRecord> getAll()override {
		std::ifstream iFile{_fileName, std::ios::in};
		std::vector<CurrencyRecord> records{};

		if (iFile) {
			std::string line{};
			while (std::getline(iFile, line)) {
				if (line.empty())continue;
				records.push_back(_ConvertLineToRecStuct(line));
			}
			iFile.close();
		}
		 
		return records;
	}

};

