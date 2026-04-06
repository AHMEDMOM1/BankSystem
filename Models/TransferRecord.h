#pragma once
#include <iostream>

struct TransRecord {
	std::string date{};
	std::string senderAccount{};
	std::string recipientAccount{};
	double amount{};
	double senderAmount{};
	double recipientAmount{};
	std::string currentUserAccount{};

};
