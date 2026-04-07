#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>

#include "Screen.h"
#include "ClientManager.h"
#include "TransferRecord.h"

class TransferLogScreen : protected Screen
{
	ClientManager& _manager;

	// ─── Console Color Helpers ───────────────────────────────────
	HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	void _SetColor(int color) {
		SetConsoleTextAttribute(_hConsole, color);
	}
	void _ResetColor() {
		SetConsoleTextAttribute(_hConsole, 7);
	}

	// Color Constants
	enum enColor {
		CYAN          = 3,
		DARK_YELLOW   = 6,
		WHITE         = 7,
		GREY          = 8,
		LIGHT_BLUE    = 9,
		LIGHT_GREEN   = 10,
		LIGHT_CYAN    = 11,
		LIGHT_RED     = 12,
		LIGHT_MAGENTA = 13,
		YELLOW        = 14,
		BRIGHT_WHITE  = 15,
	};

	// ─── Table Layout Constants ──────────────────────────────────
	static const short COL_NO        = 4;
	static const short COL_DATE      = 20;
	static const short COL_SENDER    = 8;
	static const short COL_RECIPIENT = 8;
	static const short COL_AMOUNT    = 8;
	static const short COL_S_BAL     = 9;
	static const short COL_R_BAL     = 9;
	static const short COL_USER      = 9;
	static const short LEFT_PAD      = 15;
	static const short TABLE_WIDTH   = COL_NO + COL_DATE + COL_SENDER + COL_RECIPIENT
	                                    + COL_AMOUNT + COL_S_BAL + COL_R_BAL + COL_USER + 18;

	// ─── Formatting Helpers ──────────────────────────────────────
	std::string _formatMoney(double value) {
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(0) << value;
		return oss.str();
	}

	// ─── Table Drawing Methods ───────────────────────────────────
	void _PrintHorizontalLine(char fillChar = '-', int color = CYAN) {
		_SetColor(color);
		std::cout << std::setw(LEFT_PAD) << ' ';
		for (int i = 0; i < TABLE_WIDTH; i++) std::cout << fillChar;
		std::cout << std::endl;
		_ResetColor();
	}

	void _PrintTableHeader() {
		std::cout << std::endl;
		_PrintHorizontalLine('=', DARK_YELLOW);

		std::cout << std::setw(LEFT_PAD) << ' ';
		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(YELLOW);       std::cout << std::left << std::setw(COL_NO)        << "#";
		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(YELLOW);       std::cout << std::left << std::setw(COL_DATE)      << "Date / Time";
		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(YELLOW);       std::cout << std::left << std::setw(COL_SENDER)    << "Sender";
		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(YELLOW);       std::cout << std::left << std::setw(COL_RECIPIENT) << "Recipient";
		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(YELLOW);       std::cout << std::left << std::setw(COL_AMOUNT)    << "Amount";
		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(YELLOW);       std::cout << std::left << std::setw(COL_S_BAL)     << "S.Balance";
		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(YELLOW);       std::cout << std::left << std::setw(COL_R_BAL)     << "R.Balance";
		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(YELLOW);       std::cout << std::left << std::setw(COL_USER)      << "User";
		_SetColor(DARK_YELLOW);  std::cout << "|" << std::endl;
		_ResetColor();

		_PrintHorizontalLine('=', DARK_YELLOW);
	}

	void _PrintRow(const TransferRecord& record, short rowNumber) {
		std::cout << std::left;
		std::cout << std::setw(LEFT_PAD) << ' ';

		// Row alternating subtle effect via # color
		int numColor = (rowNumber % 2 == 0) ? GREY : BRIGHT_WHITE;

		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(numColor);     std::cout << std::setw(COL_NO)        << rowNumber;

		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(LIGHT_CYAN);   std::cout << std::setw(COL_DATE)      << record.date;

		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(LIGHT_GREEN);  std::cout << std::setw(COL_SENDER)    << record.senderAccount;

		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(LIGHT_MAGENTA);std::cout << std::setw(COL_RECIPIENT) << record.recipientAccount;

		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(LIGHT_RED);    std::cout << std::setw(COL_AMOUNT)    << _formatMoney(record.amount);

		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(LIGHT_BLUE);   std::cout << std::setw(COL_S_BAL)    << _formatMoney(record.senderAmount);

		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(LIGHT_BLUE);   std::cout << std::setw(COL_R_BAL)    << _formatMoney(record.recipientAmount);

		_SetColor(DARK_YELLOW);  std::cout << "| ";
		_SetColor(BRIGHT_WHITE); std::cout << std::setw(COL_USER)      << record.currentUserAccount;

		_SetColor(DARK_YELLOW);  std::cout << "|" << std::endl;
		_ResetColor();
	}

	void _PrintFooter(short count) {
		_PrintHorizontalLine('=', DARK_YELLOW);

		_SetColor(LIGHT_GREEN);
		std::cout << std::endl << std::setw(LEFT_PAD) << ' ' << " Total Transfers: ";
		_SetColor(YELLOW);
		std::cout << count << std::endl;
		_ResetColor();

		_SetColor(GREY);
		std::cout << std::right << std::setw(LEFT_PAD + TABLE_WIDTH) << "End of Transfer Log" << std::endl;
		_ResetColor();
	}

	void _PrintEmptyMessage() {
		_SetColor(LIGHT_RED);
		std::cout << "\n" << std::setw(40) << ' ' << ">> No Transfer Records Found! <<" << std::endl;
		_ResetColor();
	}

	void _printRecords(const std::vector<TransferRecord>& records) {
		if (records.empty()) {
			_PrintEmptyMessage();
			return;
		}

		_PrintTableHeader();

		short rowNum = 1;
		for (const TransferRecord& record : records) {
			_PrintRow(record, rowNum++);
		}

		_PrintFooter(static_cast<short>(records.size()));
	}

public:
	TransferLogScreen(ClientManager& manager) : _manager(manager) {}

	void show() {
		showGlobalScreen("Transfer Log Screen");

		std::vector<TransferRecord> records{ _manager.loadAlllRecords() };

		_printRecords(records);
	}
};
