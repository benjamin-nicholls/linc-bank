#pragma once
#include "account.h"


class Current : public Account {

public:
	Current();
	Current(double InitialDeposit);
	~Current();
	std::string ToString();

protected:
	double m_OverdraftLimit = 500.00;
	double m_Overdraft;
	bool Deposit(double Amount);
	bool Withdraw(double Amount);
	double GetBalance();
	std::string Truncate2dp(double Value);

};
