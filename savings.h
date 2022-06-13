#pragma once
#include "account.h"
#include "interestearning.h"


class Savings: public Account, public InterestEarning {
public:
	Savings(double InitialDeposit = 0.00, bool Isa = false);
	~Savings();
	bool Deposit(double Amount);
	bool Withdraw(double Amount);
	double ComputeInterest(int Years);
	std::string ToString();

protected:
	double m_InterestRate = 0.85;
	bool m_ISA;
	double GetBalance();
	std::string Truncate2dp(double Value);
};
