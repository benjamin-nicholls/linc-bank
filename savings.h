#pragma once
#include "account.h"
#include "interestearning.h"


class Savings: public Account, public InterestEarning {
public:
	Savings(double InitialDeposit = 0.00, bool Isa = false);
	~Savings();
	bool Deposit(double Amount);
	bool Withdraw(double Amount);
	double ComputeInterest(int Years) const;
	std::string ToString() const;

protected:
	double m_InterestRate = 0.85;
	bool m_ISA;
	std::string Truncate2dp(double Value) const;
};
