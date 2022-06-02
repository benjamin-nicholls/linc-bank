#pragma once
#include "account.h"
#include "interestearning.h"


class Savings: public Account, public InterestEarning {

public:
	Savings(double InitialDeposit = 0, bool Isa = false);
	~Savings();

protected:
	double m_InterestRate = 0.85;
	bool m_ISA;
	bool Deposit(double Amount);
	bool Withdraw(double Amount);
	void AssignInterest();
	double ComputeInterest(double InitialBalance, int Years);
	
};
