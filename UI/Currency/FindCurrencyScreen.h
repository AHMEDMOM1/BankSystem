#pragma once

#include "Screen.h"

class FindCurrencyScreen : protected Screen{


public:
    void show(){
        showGlobalScreen("Find Currency Screen");
    }
};