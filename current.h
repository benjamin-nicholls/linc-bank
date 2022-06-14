#pragma once
#include "account.h"

class Current: public Account {
public:
	Current(double InitialDeposit = 0.00);
	~Current();
	bool Deposit(double Amount, int Ref = 0);
	bool Withdraw(double Amount, int Ref = 0);
	std::string ToString() const;

protected:
	double const m_OverdraftLimit;
	double m_Overdraft;
	double GetBalance() const;
	std::string Truncate2dp(double Value) const;
};
