#pragma once

#include <vector>

#include "CurrencyRecord.h"

class ICurrenciesRepo
{

public:
	virtual ~ICurrenciesRepo() = default;
	virtual CurrencyRecord findByCurrencyCode(const std::string& currencyCode) = 0;
	virtual CurrencyRecord findByCountryName(const std::string& countryName) = 0;
	virtual bool updateRate(const CurrencyRecord& currentRecord) = 0;
	virtual std::vector<CurrencyRecord> getAll() = 0;
};

