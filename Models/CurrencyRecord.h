#pragma once

#include <iostream>

struct CurrencyRecord
{
	std::string countryName{};
	std::string currencyName{};
	std::string currencyCode{};
	double currencyExchangeDollar{};

	bool isEmpty() {
		return countryName.empty() || currencyCode.empty();
	}
};

