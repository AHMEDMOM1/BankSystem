#pragma once

#include <iostream>
#include <vector>

#include "Screen.h"
#include "ClientManager.h"
#include "TransferRecord.h"
#include "TransferLogFile.h"


class TransferLogScreen : protected Screen
{
	ClientManager& _manager;
	void _printRecords(std::vector<TransferRecord> records) {

	}
	public:
	void show() {
		showGlobalScreen("Transfer Log Screen");

		std::vector<TransferRecord> records{ _manager.loadAlllRecords() };

		_printRecords(records);
	}
};

