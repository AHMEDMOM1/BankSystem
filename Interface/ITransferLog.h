#pragma once
class ITransferLog
{
public:
	virtual ~ITransferLog() = default;
	virtual bool recordTransferProcess(const CurrentUser& user, const Client& sender, const Client& rec, const double amount) = 0;
};

