#pragma once
#include "account.h"
#include "interestearning.h"

class Current: public Account, public InterestEarning {
public:
	Current(double InitialDeposit = 0.00);
	~Current();
	bool Deposit(double Amount);
	bool Withdraw(double Amount);
	std::string ToString();

protected:
	double m_OverdraftLimit = 500.00;
	double m_Overdraft;
	double GetBalance();
	std::string Truncate2dp(double Value);
};
