#pragma once

#include <vector>

#include "ICurrenciesRepo.h"
#include "CurrencyRecord.h"

class CurrencyManager{
    ICurrenciesRepo& _repo;

public:
    CurrencyManager(ICurrenciesRepo& repo) : _repo(repo){}

    CurrencyRecord findByCurrencyCode(const std::string& currencyCode){
        return _repo.findByCurrencyCode(currencyCode);
    }

    CurrencyRecord findByCountryName(const std::string& countryName){
        return _repo.findByCountryName(countryName);
    }

    bool update(const CurrencyRecord& currentRecord){
        return _repo.updateRate(currentRecord);
    }

    std::vector<CurrencyRecord> loadAllCurrencies(){
        return _repo.getAll();
    }

    bool isCurrencyCodePresent(const std::string& currencyCode) {
        return !_repo.findByCurrencyCode(currencyCode).currencyCode.empty();
    }
    bool isCountryNamePresent(const std::string& countryName) {
        return !_repo.findByCurrencyCode(countryName).countryName.empty();
    }
};