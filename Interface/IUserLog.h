#pragma once

#include <iostream>
#include <vector>

#include "LoginRecord.h"
#include "CurrentUser.h"

class IUserLogin {
public:
	virtual ~IUserLogin() = default;
	virtual bool add(const CurrentUser& user) = 0;
	virtual std::vector<LoginRecord> getAll() = 0;
};