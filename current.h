#pragma once
#include "account.h"

class Current: public Account {
public:
	Current(double InitialDeposit = 0.00);
	~Current();
	bool Deposit(double Amount);
	bool Withdraw(double Amount);
	std::string ToString() const;

protected:
	double m_OverdraftLimit = 500.00;
	double m_Overdraft;
	double GetBalance() const;
	std::string Truncate2dp(double Value) const;
};
