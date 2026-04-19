#pragma once

#include "ClientManager.h"
#include "LoggerManager.h"
#include "EmployeeManager.h"
#include "CurrencyManager.h"


struct AppContext{
    ClientManager& clntManager;
    EmployeeManager& empManager;
    CurrencyManager& curManager;
    LoggerManager& logManager;

};