#pragma once
#include "account.h"
#include "interestearning.h"


class Savings: public Account, public InterestEarning {
public:
	Savings(double InitialDeposit = 0.00, bool Isa = false);
	~Savings();
	bool Deposit(double Amount, int Ref = 0);
	bool Withdraw(double Amount, int Ref = 0);
	double ComputeInterest(int Years) const;
	std::string ToString() const;

protected:
	double m_InterestRate;
	bool m_ISA;
	std::string Truncate2dp(double Value) const;
};
