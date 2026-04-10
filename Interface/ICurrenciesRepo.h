#pragma once

#include <vector>

#include "CurrenciesRecord.h"

class ICurrenciesRepo
{

public:
	virtual ~ICurrenciesRepo() = default;
	virtual CurrenciesRecord findByCurrencyCode(const std::string& currencyCode) = 0;
	virtual CurrenciesRecord findByCountryName(const std::string& countryName) = 0;
	virtual bool updateRate(const CurrenciesRecord& currentRecord) = 0;
	virtual std::vector<CurrenciesRecord> getAll() = 0;
};

