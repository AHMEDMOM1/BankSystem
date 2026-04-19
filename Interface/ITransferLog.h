#pragma once

#include <vector>

#include "Client.h"
#include "CurrentUser.h"
#include "TransferRecord.h"
class ITransferLog
{
public:
	virtual ~ITransferLog() = default;
	virtual bool recordTransferProcess(const CurrentUser& user, const Client& sender, const Client& rec, const double amount) = 0;
	virtual std::vector<TransferRecord> loadAllRecords() = 0;
};

