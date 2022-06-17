#pragma once
#include "account.h"
#include "interestearning.h"


class Savings: public Account, public InterestEarning {
public:
	Savings(double InitialDeposit = 0.00, bool Isa = false);
	~Savings();
	bool deposit(double &Amount, int Ref = 0);
	bool withdraw(double &Amount, int Ref = 0);
	double computeInterest(int Years) const;
	std::string toString() const;

protected:
	double m_InterestRate;
	bool m_ISA;
	double m_IsaRequiredDeposit = 1000.00;
};
