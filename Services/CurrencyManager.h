#pragma once

#include <vector>

#include "ICurrenciesRepo.h"
#include "CurrenciesRecord.h"

class CurrencyManager{
    ICurrenciesRepo& _repo;

public:
    CurrencyManager(ICurrenciesRepo& repo) : _repo(repo){}

    CurrenciesRecord findByCurrencyCode(const std::string& currencyCode){
        return _repo.findByCurrencyCode(currencyCode);
    }

    CurrenciesRecord findByCountryName(const std::string& countryName){
        return _repo.findByCountryName(countryName);
    }

    bool update(const CurrenciesRecord& currentRecord){
        return _repo.updateRate(currentRecord);
    }

    std::vector<CurrenciesRecord> loadAllCurrencies(){
        return _repo.getAll();
    }
};