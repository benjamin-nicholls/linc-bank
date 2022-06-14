#pragma once
#include "account.h"

class Current: public Account {
public:
	Current(double InitialDeposit = 0.00);
	~Current();
	bool deposit(double Amount, int Ref = 0);
	bool withdraw(double Amount, int Ref = 0);
	std::string toString() const;

protected:
	double const m_OverdraftLimit = 500.00;
	double m_Overdraft;
	double GetBalance() const;
	std::string Truncate2dp(double Value) const;
};
