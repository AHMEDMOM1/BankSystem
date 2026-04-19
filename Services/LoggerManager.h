#pragma once
#include <iostream>
#include <vector>

#include "IUserLog.h"
#include "LoginRecord.h"
#include "CurrentUser.h"

class LoggerManager
{
	IUserLogin& _userLog;
public:
	LoggerManager(IUserLogin& userLog) : _userLog(userLog) {}

	bool add(const CurrentUser& user) {
		return _userLog.add(user);
	}

	std::vector<LoginRecord> loadAll() {
		return _userLog.getAll();
	}
};
