#pragma once

#include "Screen.h"

class ShowAllCurrenciesScreen  : protected Screen{
    void show(){
        showGlobalScreen("Currencies List");
    }
};