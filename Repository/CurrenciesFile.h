#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "clsString.h"
#include "ICurrenciesRepo.h"
#include "CurrenciesRecord.h"

class CurrenciesFile : public ICurrenciesRepo
{

	std::string _fileName{};
	std::string _delim{};

	CurrenciesRecord _ConvertLineToRecStuct(std::string& line) {
		std::vector<std::string>partitions{ clsString::Split(line, _delim) };
		CurrenciesRecord record{};

		if (partitions.size() >= 1) record.countryName = partitions.at(0);
		if (partitions.size() >= 2) record.currencyCode = partitions.at(1);
		if (partitions.size() >= 3) record.currencyName = partitions.at(2);
		if (partitions.size() >= 4) record.currencyExchangeDollar = std::stod(partitions.at(3));

		return record;
	}


public:
	CurrenciesFile(const std::string& fileName, const std::string& delim = "#//#") : _fileName(fileName), _delim(delim) {}

	CurrenciesRecord findByCurrencyCode(const std::string& currencyCode) override {
		std::vector<CurrenciesRecord> records{ getAll() };

		for (CurrenciesRecord& record : records) {
			if (record.currencyCode == currencyCode) return record;
		}

		return CurrenciesRecord();
	}
	CurrenciesRecord findByCountryName(const std::string& countryName) override {
		std::vector<CurrenciesRecord> records{ getAll() };

		for (CurrenciesRecord& record : records) {
			if (record.countryName == countryName) return record;
		}

		return CurrenciesRecord();
	}
	bool updateRate(const CurrenciesRecord& currentRecord)override {
		std::vector<CurrenciesRecord> records{ getAll() };

		for (CurrenciesRecord& record : records) {
			if (record.currencyCode == currentRecord.currencyCode) {
				record = currentRecord;
				return true;
			}
		}


		return false;
	}
	
	std::vector<CurrenciesRecord> getAll()override {
		std::ifstream iFile{_fileName, std::ios::in};
		std::vector<CurrenciesRecord> records{};

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

