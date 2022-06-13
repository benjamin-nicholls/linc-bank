#pragma once
#include "account.h"
#include "interestearning.h"


class Savings: public Account, public InterestEarning {
public:
	Savings(double InitialDeposit = 0.00, bool Isa = false);
	~Savings();
	bool Deposit(double Amount);
	bool Withdraw(double Amount);
	std::string ToString();

protected:
	double m_InterestRate = 0.85;
	bool m_ISA;
	void AssignInterest();
	double ComputeInterest(double InitialBalance, int Years);
	double GetBalance();
	std::string Truncate2dp(double Value);
};
